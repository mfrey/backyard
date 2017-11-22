/*
 * Copyright (C) FIXME
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief   Functions for debugging CCN-lite data structures
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef DEBUG_H_ 
#define DEBUG_H_

#include "ccn-lite-riot.h"

#ifdef __cplusplus
extern "C" {
#endif

void print_content_store(int argc, char **argv);

void print_faces(int argc, char **argv);

void print_face_statistics(struct ccnl_face_s *face);

void print_stats(int argc, char **argv);

int get_interface_number(void);

#ifdef __cplusplus
}
#endif


#endif /* DEBUG_H_ */
/** @} */
