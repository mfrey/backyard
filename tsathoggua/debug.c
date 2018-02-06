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
 *
 * @}
 */

#include "debug.h"
#include "management.h"

#include <stdio.h>

int print_content_store(int argc, char **argv)
{
    (void) argc; 
    (void) argv;
    ccnl_cs_dump(&ccnl_relay);

    return 0;
}

int print_face_statistics(struct ccnl_face_s *face)
{
    if (face) {
        printf("face id: %d, flags: %d, last used: %d\n", face->faceid, face->flags, face->last_used);
    }

    return 0;
}

int print_faces(int argc, char **argv)
{
    (void) argc; 
    (void) argv;

    _management_list_faces(&ccnl_relay);

    return 0;
}

int get_interface_number(void)
{
    int result = 0;
    struct ccnl_face_s *face = (struct ccnl_face_s*) ccnl_relay.faces;
    
    while (face) {
        result++;
        face = face->next;
    } 

    return result;
}

int print_stats(int argc, char **argv) 
{
    (void) argc; (void) argv;
#ifdef USE_STATS
    printf("RX: %04" PRIu32 ", TX: %04" PRIu32 "\n", ccnl_relay.ifs[0].rx_cnt, ccnl_relay.ifs[0].tx_cnt);
#endif 
    return 0;
}

