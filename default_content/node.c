

#include "node.h"
#include "default.h"

#include <stdio.h>

#include "net/gnrc/netif.h"
#include "net/gnrc/netapi.h"
#include "net/gnrc.h"

#define MAX_NAME_SIZE (32u)

static const char *nodes[] = {
   "2201",
   "2215",
   "2218",
   "2221",
   "2223",
   "2228",
   "3226",
   "4203",
   "4210",
   "4212",
   "4214",
   "4216",
   "4218",
   "4221",
   "4225",
   "TEST"
};
//d3:c1:6d:54:ab:6:13:36
static const char *mac_addresses[] = {
   "d3:c1:6d:71:ab:01:13:36",
   "d3:c1:6d:73:ab:5b:13:36",
   "d3:c1:6d:78:ab:04:13:36",
   "d3:c1:6d:7f:ab:07:13:36",
   "d3:c1:6d:7e:ab:01:13:36",
   "00:00:00:00:0d:0e:0a:0d", /** node is down, mac is unknown */
   "d3:c1:6d:72:ab:02:13:36",
   "d3:c1:6d:54:ab:06:13:36",
   "d3:c1:6d:5f:ab:66:13:36",
   "d3:c1:6d:6b:ab:42:13:36",
   "d3:c1:6d:6f:ab:66:13:36",
   "d3:c1:6d:56:ab:02:13:36",
   "d3:c1:6d:5d:ab:6b:13:36",
   "d3:c1:6d:52:ab:59:13:36",
   "d3:c1:6d:56:ab:03:13:36",
   "d3:c1:6d:52:ab:55:13:36" // TEST NODE
};

void _create_node_status(void){
    char name[MAX_NAME_SIZE] = { '\0' };
    char sensor_reading[64];

    /** get the network interface */
    gnrc_netif_t *netif = NULL;
    netif = gnrc_netif_iter(NULL);

    /** determine mac address of a device */
    eui64_t mac_address;
    gnrc_netapi_get(netif->pid, NETOPT_ADDRESS_LONG, 0, &mac_address, sizeof(mac_address));
    int sensor_reading_len = sprintf(sensor_reading, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x", 
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

    const char *node = get_host_by_mac(sensor_reading);

    if (node) {
        snprintf(name, MAX_NAME_SIZE, "/i3/%s/config/", node);
        printf("prefix: %s\n", name);

        _store_(&ccnl_relay, name, (unsigned char*)sensor_reading, sensor_reading_len);
    } else {
        printf("host is unknown\n");
    }
}

const char* get_host_by_mac(const char* mac){
    for(uint8_t i = 0; i < 16; i++) {
    //for(uint8_t i = 0; i < 15; i++) {
        if (strncmp(mac_addresses[i], mac, 23) == 0) {
            return nodes[i];
        }
    }

    return NULL;
}
