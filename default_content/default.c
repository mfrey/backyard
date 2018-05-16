
#include "default.h"

static unsigned char _out[CCNL_MAX_PACKET_SIZE];


void _store_(struct ccnl_relay_s *ccnl, unsigned char *payload, int length){

    int suite = CCNL_SUITE_NDNTLV;
    int offset = CCNL_MAX_PACKET_SIZE;
    char name[32];


    struct ccnl_prefix_s *prefix = ccnl_URItoPrefix(name, suite, NULL);
    int arg_len = ccnl_ndntlv_prependContent(prefix, payload,
        length, NULL, NULL, &offset, _out);
    ccnl_prefix_free(prefix);

    int len;
    unsigned type;
    unsigned char *olddata;
    unsigned char *data = olddata = _out + offset;

    if (ccnl_ndntlv_dehead(&data, &arg_len, (int*) &type, &len) || type != NDN_TLV_Data) {
        printf("ERROR in _pub\n");
        return;
    }

    struct ccnl_content_s *content = NULL;
    struct ccnl_pkt_s *packet = ccnl_ndntlv_bytes2pkt(type, olddata, &data, &arg_len);
    content = ccnl_content_new(&packet);
    ccnl_content_add2cache(ccnl, content); // CHANGE -> NEW API
    content->flags |= CCNL_CONTENT_FLAGS_STALE;

    // send operation?
}

