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
 * @brief       Functions for gossiping NDOs in NDN
 *
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */
#include "gossip.h"

#include "random.h"


void gossip_init(const uint32_t seed)
{
    /** initialize random number generator */
    random_init(seed);
}

bool gossip(const uint32_t p)
{
    uint32_t n = random_uint32();
    return (n < p);
}
