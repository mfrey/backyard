/*
 * Copyright (C) FIXME
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     examples
 * @{
 *
 * @file
 * @brief       TODO
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */
#include "content.h"


#include "log.h"
#include "msg.h"
#include "sched.h"
#include "xtimer.h"
#include "random.h"
#include "net/gnrc/netreg.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc/pktbuf.h"

#include "ccnl-defs.h"
#include "ccnl-pkt-ndntlv.h"

/* buffers for interests and content */
static unsigned char _int_buf[CCNLRIOT_BUF_SIZE];
static unsigned char _cont_buf[CCNLRIOT_BUF_SIZE];
static unsigned char _out[CCNL_MAX_PACKET_SIZE];
static char _prefix_str[CCNLRIOT_PFX_LEN];

/* prototypes from CCN-lite */
void free_packet(struct ccnl_pkt_s *pkt);
struct ccnl_prefix_s *ccnl_prefix_dup(struct ccnl_prefix_s *prefix);

struct ccnl_interest_s *create_interest(struct ccnl_prefix_s *prefix)
{
    /** generate nonce for the interest  */
    int nonce = random_uint32();
    // LOG_DEBUG("ccnl_helper: nonce: %X\n", nonce);

    extern int ndntlv_mkInterest(struct ccnl_prefix_s *name, int *nonce, unsigned char *out, int outlen);

    /** create interest based on prefix and nonce */
    int length = ndntlv_mkInterest(prefix, &nonce, _int_buf, CCNLRIOT_BUF_SIZE);

    /** */
    unsigned char *start = _int_buf;
    /** */
    unsigned char *data = _int_buf;

    int type;
    int interest_length;

    /** */
    if (ccnl_ndntlv_dehead(&data, &length, (int*) &type, &interest_length) || (int) interest_length > length) {
        LOG_WARNING("create_interest: invalid packet format\n");
        return NULL;
    }

    /** */
    struct ccnl_pkt_s *packet;
    /** */
    packet = ccnl_ndntlv_bytes2pkt(NDN_TLV_Interest, start, &data, &length);
    /** */
    struct ccnl_face_s *loopback_face = ccnl_get_face_or_create(&ccnl_relay, -1, NULL, 0);
    /** */
    return ccnl_interest_new(&ccnl_relay, loopback_face, &packet);
}

struct ccnl_content_s *create_content(struct ccnl_prefix_s *prefix,
                                               unsigned char *value, ssize_t
                                               len, bool cache, bool send)
{
    if (len > (CONTENT_LENGTH + 1)) {
        LOG_ERROR("ccnl_helper: Too long content. This is not acceptable!!!\n");
        return NULL;
    }
    int offs = CCNL_MAX_PACKET_SIZE;

    content_t my_cont;
    memset(&my_cont.value, 0, CONTENT_LENGTH + 1);
    memcpy(my_cont.value, value, len);
    my_cont.num = -1;
    len = sizeof(content_t);

    ssize_t arg_len = ccnl_ndntlv_prependContent(prefix, (unsigned char*) &my_cont, len, NULL, NULL, &offs, _out);

    unsigned char *olddata;
    unsigned char *data = olddata = _out + offs;
    unsigned typ;

    if (ccnl_ndntlv_dehead(&data, &arg_len, (int*) &typ, &len) ||
        typ != NDN_TLV_Data) {
        return NULL;
    }

    struct ccnl_content_s *c = 0;
    struct ccnl_pkt_s *pk = ccnl_ndntlv_bytes2pkt(typ, olddata, &data, &arg_len);

    if (pk == NULL) {
        LOG_ERROR("ccnl_helper: something went terribly wrong!\n");
        extern void ccnl_count_faces(struct ccnl_relay_s *ccnl);
        ccnl_count_faces(&ccnl_relay);
        extern void ccnl_pit_size(struct ccnl_relay_s *ccnl);
        ccnl_pit_size(&ccnl_relay);
        return NULL;
    }

    c = ccnl_content_new(&ccnl_relay, &pk);

    if (send) {
        for (int i = 0; i < DOW_BC_COUNT; i++) {
            ccnl_broadcast(&ccnl_relay, c->pkt);
#if (DOW_BC_COUNT > 1)
            xtimer_usleep(20000);
#endif
        }
    }

    if (cache) {
        cache_content(c);
    }

    return c;
}

void cache_content(struct ccnl_content_s *content)
{
    uint8_t address[ADDRESS_LENGTH];
#if (ADDRESS_LENGTH == 8)
        gnrc_netapi_get(CCNLRIOT_NETIF, NETOPT_ADDRESS_LONG, 0, address, sizeof(address));
#else
        gnrc_netapi_get(CCNLRIOT_NETIF, NETOPT_ADDRESS, 0, address, sizeof(address));
#endif

    sockunion destination;
    destination.sa.sa_family = AF_PACKET;
    destination.linklayer.sll_halen = ADDRESS_LENGTH;
    destination.linklayer.sll_protocol = htons(ETHERTYPE_NDN);
    memcpy(destination.linklayer.sll_addr, address, ADDRESS_LENGTH);

    extern void ccnl_ll_TX(struct ccnl_relay_s *ccnl, struct ccnl_if_s *ifc, sockunion *dest, struct ccnl_buf_s *buf);
    ccnl_ll_TX(&ccnl_relay, &ccnl_relay.ifs[0], &destination, content->pkt->buf);
    free_packet(content->pkt);
}
