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
 * @brief   Functions for creating ICN content
 *
 * @author  Oliver Hahm <oliver.hahm@inria.fr>
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef CONTENT_H_
#define CONTENT_H_

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The default network interface
 */
#ifndef CCNLRIOT_NETIF
#define CCNLRIOT_NETIF      (3)
#endif 

/**
 * @brief The (internal) buffer size
 */
#ifndef CCNLRIOT_BUF_SIZE
#define CCNLRIOT_BUF_SIZE (128)
#endif 

/**
 * @brief The maximum prefix (name) length
 */
#ifndef CCNLRIOT_PFX_LEN   
#define CCNLRIOT_PFX_LEN   (50)
#endif 

/** how often broadcasts of unsolicited are repeated */
#ifdef CPU_NATIVE
#define DOW_BC_COUNT                (1)
#else
#define DOW_BC_COUNT                (3)
#endif


#ifdef BOARD_NATIVE
#   define ADDRESS_LENGTH     (6)
#else
#  if USE_LONG
#    define ADDRESS_LENGTH     (8)
#  else
#    define ADDRESS_LENGTH     (2)
#  endif
#endif

#define CONTENT_LENGTH            (8)


#include "ccn-lite-riot.h"

/**
 * @brief
 */
typedef struct __attribute__((packed)) {
    char value[CONTENT_LENGTH + 1];
    int num;
} content_t;


/**
 * @brief Creates an Interest for a given name
 *
 * @param[in] prefix The name of the Interest
 *
 * @return An Interest upon success, otherwise NULL
 */
struct ccnl_interest_s *create_interest(struct ccnl_prefix_s *prefix);

/**
 * @brief Adds content to the local cache 
 *
 * @param[in] content The content to add to the cache
 *
 */
void cache_content(struct ccnl_content_s *content);

/**
 * @brief Creates a content struct 
 *
 * @param[in] prefix    name of the content
 * @param[in] value     content itself (will get filled into a
 *                      @ref dow_content_t struct
 * @param[in] cache     if true, sends data via loopback to self for caching
 *
 * @returns pointer to new content chunk
 */
struct ccnl_content_s *create_content(struct ccnl_prefix_s *prefix, unsigned char *value, 
    ssize_t len, bool cache, bool send); 

#ifdef __cplusplus
}
#endif


#endif /* CONTENT_H_ */
/** @} */
