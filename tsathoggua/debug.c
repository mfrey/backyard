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
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */

#include "debug.h"

#include <stdio.h>

void print_content_store(int argc, char **argv)
{
    (void) argc; 
    (void) argv;
    ccnl_cs_dump(&ccnl_relay);
}

void print_face_statistics(struct ccnl_face_s *face)
{
    if (face) {
        printf("face id: %d, flags: %d, last used: %d\n", face->faceid, face->flags, face->last_used);
    }
}

void print_faces(int argc, char **argv)
{
    (void) argc; 
    (void) argv;

    struct ccnl_face_s *face = (struct ccnl_face_s*) ccnl_relay.faces;

    while (face) {
        print_face_statistics(face);
        face = face->next;
    } 
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

void print_stats(int argc, char **argv) 
{
    (void) argc; (void) argv;
#ifdef USE_STATS
    printf("RX: %04" PRIu32 ", TX: %04" PRIu32 "\n", ccnl_relay.ifs[0].rx_cnt, ccnl_relay.ifs[0].tx_cnt);
#endif 
}
