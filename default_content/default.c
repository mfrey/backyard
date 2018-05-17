
#include "default.h"

static unsigned char _out[CCNL_MAX_PACKET_SIZE];

void _store_(struct ccnl_relay_s *ccnl, unsigned char* name, unsigned char *payload, int length){

    int suite = CCNL_SUITE_NDNTLV;
    int offset = CCNL_MAX_PACKET_SIZE;

    /***/
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

    /***/
    struct ccnl_content_s *content = NULL;
    struct ccnl_pkt_s *packet = ccnl_ndntlv_bytes2pkt(type, olddata, &data, &arg_len);
    content = ccnl_content_new(&packet);

    /** */
    struct ccnl_content_s *c = ccnl_content_add2cache(ccnl, content);
    /** replace the line above and the following with ccnl_cs_add  */
    if (c) {
        ccnl_content_serve_pending(ccnl, c);
    }

    //ccnl_cs_add(ccnl, content);
    content->flags |= CCNL_CONTENT_FLAGS_STALE;
}

