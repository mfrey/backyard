
#include "settings.h"

#include <stdio.h>

#include "ccn-lite-riot.h"

int set_radio_settings(uint16_t channel, uint16_t tx_power, uint16_t src_len, netopt_enable_t cca){
    /* get the default interface */
    gnrc_netif_t *netif;

    /* set the relay's PID, configure the interface to use CCN nettype */
    if (((netif = gnrc_netif_iter(NULL)) == NULL) ||
            (ccnl_open_netif(netif->pid, GNRC_NETTYPE_CCN) < 0)) {
        puts("Error registering at network interface!");
        return -1;
    }

    /** set the channel */
    gnrc_netapi_set(netif->pid, NETOPT_CHANNEL, 0, &channel, sizeof(channel));
    /** set the transmit power */
    gnrc_netapi_set(netif->pid, NETOPT_TX_POWER, 0, &tx_power, sizeof(tx_power));
    /** enable/disable auto cca */
    gnrc_netapi_set(netif->pid, NETOPT_AUTOCCA, 0, &cca, sizeof(netopt_enable_t));
    /** set the size of the short addresses */
    gnrc_netapi_set(netif->pid, NETOPT_SRC_LEN, 0, &src_len, sizeof(src_len));

    return 0;
}
