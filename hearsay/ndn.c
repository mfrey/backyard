/*
 * Copyright (C) MSA Safety
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
 * @brief       Provides helper functions for using NDN in CCN-lite
 *
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */
#include "gossip.h"

#include "ccn-lite-riot.h"


void broadcast_interest(struct ccnl_relay_s *relay, struct ccnl_interest_s *interest)
{
    if (gossip(10000)) {
        ccnl_interest_broadcast(relay, interest);
    }
}
