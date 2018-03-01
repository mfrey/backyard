

#include "content.h"

#include <stdio.h>
#include <string.h>

static const char *_default_content = "RIOT!";


int content_mk_content_object(struct ccnl_relay_s *relay, struct ccnl_face_s *from, struct ccnl_pkt_s *pkt)
{
	int result = -1;

	/*** The function \ref ccnl_mkContentObject calls ccnl_mk_SimpleContent and duplicates prefix */
	struct ccnl_content_s *content = ccnl_mkContentObject(pkt->pfx, _default_content, strnlen(_default_content, 5), NULL);

	if (content) {
		/** copy/paste from \ref ccnl_cs_dump */
		char s[CCNL_MAX_PREFIX_SIZE];
        printf("%s => %s, size of content %d\n", ccnl_prefix_to_str(content->pkt->pfx, s, CCNL_MAX_PREFIX_SIZE), content->pkt->content, content->pkt->contlen);

		/*** add our content to the store */
		ccnl_content_add2cache(relay, content);
		result = 0;
	} else {
		printf("could not add content to the cache\n");
	}

	return result;
}


int content_mk_simple_content(struct ccnl_relay_s *relay, struct ccnl_face_s *from, struct ccnl_pkt_s *pkt)
{
	int result = -1;
	int offset = -1;

	struct ccnl_buf_s *content = ccnl_mkSimpleContent(pkt->pfx, _default_content, strnlen(_default_content, 5), &offset, NULL);

	if (content) {
		/** copy/paste from \ref ccnl_cs_dump */
		char s[CCNL_MAX_PREFIX_SIZE];
		printf("length %d, offset %d\n", content->datalen, offset);
        printf("interest %s\n content: ", ccnl_prefix_to_str(pkt->pfx, s, CCNL_MAX_PREFIX_SIZE));

        for(uint8_t i = 0; i < content->datalen; i++) {
        	printf(" %d -> %c   ", i, content->data[i]);
        }
        printf("\n");
		
		result = 0;
	} else {
		printf("could not add content to the cache\n");
	}

	return result;
}
