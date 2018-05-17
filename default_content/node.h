


#ifndef NODE_H_
#define NODE_H_ 

#ifdef __cplusplus
extern "C" {
#endif

#include "ccn-lite-riot.h"

void _create_node_status(void);
const char* get_host_by_mac(const char* mac);

#ifdef __cplusplus

}
#endif


#endif /* NODE_H_ */
/** @} */
