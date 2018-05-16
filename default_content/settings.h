

#ifndef SETTINGS_H_ 
#define SETTINGS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "net/gnrc/netif.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc.h"

/**
 *
 */
int set_radio_settings(uint16_t channel, uint16_t tx_power, uint16_t src_len, netopt_enable_t cca);

#ifdef __cplusplus
}
#endif


#endif /* CONTENT_H_ */
/** @} */
