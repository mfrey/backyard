/*
 * Copyright (C) 2018 MSA Safety
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief   Functions for adding content on-the-fly
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef CONTENT_H_ 
#define CONTENT_H_

#include "ccn-lite-riot.h"

#ifdef __cplusplus
extern "C" {
#endif


int content_mk_content_object(struct ccnl_relay_s *relay, struct ccnl_face_s *from, struct ccnl_pkt_s *pkt);

int content_mk_simple_content(struct ccnl_relay_s *relay, struct ccnl_face_s *from, struct ccnl_pkt_s *pkt);


#ifdef __cplusplus
}
#endif


#endif /* CONTENT_H_ */
/** @} */
