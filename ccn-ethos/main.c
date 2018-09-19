/*
 * Copyright (C) 2018 MSA Safety 
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
 * @brief       ccn-lite over ethos example (work in progress)
 *
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */

#include "msg.h"
#include "shell.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/pktdump.h"

#include "ccn-lite-riot.h"
#include "tlsf-malloc.h"

#define TLSF_BUFFER     (10240 / sizeof(uint32_t))
static uint32_t _tlsf_heap[TLSF_BUFFER];

/* main thread's message queue */
#define MAIN_QUEUE_SIZE (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

#define BUFFER_SIZE     (128u)
/** */
static unsigned char _int_buf[BUFFER_SIZE];
/** */
static unsigned char _out[CCNL_MAX_PACKET_SIZE];


static struct ccnl_interest_s *create_interest(struct ccnl_relay_s *ccnl, unsigned char* name){
    int suite = CCNL_SUITE_NDNTLV;
    int nonce = random_uint32();

    /** create prefix */
    struct ccnl_prefix_s *prefix = ccnl_URItoPrefix(name, suite, NULL);
    /** */
    int len = ccnl_mkInterest(prefix, NULL, _int_buf, BUFFER_SIZE);
    ccnl_prefix_free(prefix);

    unsigned char *start = _int_buf;
    unsigned char *data = _int_buf;

    int type;
    int int_len;

    if (ccnl_ndntlv_dehead(&data, &len, (int*) &type, &int_len) || (int) int_len > len) {
        printf("ccnl_helper: invalid packet format\n");
        return NULL;
    }

    struct ccnl_pkt_s *pkt = ccnl_ndntlv_bytes2pkt(NDN_TLV_Interest, start, &data, &len);
    struct ccnl_face_s *loopback_face = ccnl_get_face_or_create(&ccnl_relay, -1, NULL, 0);

    return ccnl_interest_new(&ccnl_relay, loopback_face, &pkt);
}

/**
 * Creates a content object with the given \p name and \p payload and adds it to the content
 * store. The content is marked as 'static'
 *
 * @param[in] ccnl The global \ref ccnl_relay_s struct
 * @param[in] name The prefix of the content to add to the content store
 * @param[in] payload The data to add to the content store
 * @param[in] length The size of the \p payload
 *
 */
static void create_content(struct ccnl_relay_s *ccnl, unsigned char* name, unsigned char *payload, int length){

    int suite = CCNL_SUITE_NDNTLV;
    int offset = CCNL_MAX_PACKET_SIZE;

    /** create prefix */
    struct ccnl_prefix_s *prefix = ccnl_URItoPrefix(name, suite, NULL);
    int arg_len = ccnl_ndntlv_prependContent(prefix, payload,
        length, NULL, NULL, &offset, _out);
    ccnl_prefix_free(prefix);

    int len;
    unsigned type;
    unsigned char *olddata;
    unsigned char *data = olddata = _out + offset;

    /***/
    if (ccnl_ndntlv_dehead(&data, &arg_len, (int*) &type, &len) || type != NDN_TLV_Data) {
        printf("ERROR in _store_\n");
        return;
    }

    /** create content */
    struct ccnl_content_s *content = NULL;
    struct ccnl_pkt_s *packet = ccnl_ndntlv_bytes2pkt(type, olddata, &data, &arg_len);
    content = ccnl_content_new(&packet);

    /** mark content as static and add it to the cache */
    content->flags |= CCNL_CONTENT_FLAGS_STATIC;
    ccnl_cs_add(ccnl, content);
}


int main(void)
{
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    tlsf_create_with_pool(_tlsf_heap, sizeof(_tlsf_heap));
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    /** initialize ccn-lite */
    ccnl_core_init();
    /** run it */
    ccnl_start();

//    create_interest(&ccnl_relay, "/test/data");

    /** run shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
