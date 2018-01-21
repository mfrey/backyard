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
 * @brief   FIXME
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef GOSSIP_H_
#define GOSSIP_H_

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Decides if an 'object' is forwarded or not
 *
 * @param[in] p The probability that is forwarded
 *
 * @return true  if the generated random number is smaller than the probablity 
 *    passed to the function
 * @return false otherwise
 */
bool gossip(const uint32_t p);

#ifdef __cplusplus
}
#endif

#endif /* GOSSIP_H_*/
/** @} */
