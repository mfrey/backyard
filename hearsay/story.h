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
 * @brief   Functions for creating NDOs
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef STORY_H_
#define STORY_H_

#include "debug.h"
#include "thread.h"

/**
 * Size of the message queue of the event loop
 */
#ifndef STORY_MESSAGE_QUEUE_SIZE
#define STORY_MESSAGE_QUEUE_SIZE              (8U)         
#endif 

/**
 * @brief Size of the stack of the event loop
 */
#ifndef STORY_STACK_SIZE
#define STORY_STACK_SIZE (THREAD_STACKSIZE_DEFAULT + DEBUG_EXTRA_STACKSIZE) 
#endif

#ifdef __cplusplus
extern "C" {
#endif

kernel_pid_t story_init(char thread_priority);

#ifdef __cplusplus
}
#endif

#endif /* STORY_H_*/
/** @} */
