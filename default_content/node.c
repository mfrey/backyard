

#include "node.h"
#include "default.h"

#include <stdio.h>

#include "net/gnrc/netif.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc.h"

#define MAX_NAME_SIZE (32u)

void _create_node_status(void){
    char name[MAX_NAME_SIZE] = { '\0' };
    char sensor_reading[64];

    snprintf(name, MAX_NAME_SIZE, "/i3/%s/config/", "1");
    printf("prefix: %s\n", name);

    /** get the MAC address */
    gnrc_netif_t *netif = NULL;
    netif = gnrc_netif_iter(NULL);

    eui64_t mac_address;
    gnrc_netapi_get(netif->pid, NETOPT_ADDRESS_LONG, 0, &mac_address, sizeof(mac_address));
    int sensor_reading_len = sprintf(sensor_reading, "%x:%x:%x:%x:%x:%x:%x:%x", 
                    mac_address.uint8[0],
                    mac_address.uint8[1],
                    mac_address.uint8[2],
                    mac_address.uint8[3],
                    mac_address.uint8[4],
                    mac_address.uint8[5],
                    mac_address.uint8[6],
                    mac_address.uint8[7]);
    sensor_reading[sensor_reading_len]='\0';
    
    printf("mac: %s\n", sensor_reading);
    
    _store_(&ccnl_relay, name, sensor_reading, sensor_reading_len);
}

