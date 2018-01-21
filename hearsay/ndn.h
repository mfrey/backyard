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
 * @brief   Provides helper functions for using NDN in CCN-lite
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef NDN_H_
#define NDN_H_

#include "ccnl-relay.h"

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

void broadcast_interest(struct ccnl_relay_s *ccnl, struct ccnl_interest_s *interest);

#ifdef __cplusplus
}
#endif

#endif /* NDN_H_*/
/** @} */
