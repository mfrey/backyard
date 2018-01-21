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
#include "story.h"

/**
 * Message queue for the process
 */
static char _story_stack[STORY_STACK_SIZE];

/**
 * PID for the story process
 */
kernel_pid_t story_event_loop_pid = KERNEL_PID_UNDEF;

/**
 * Event handler for NDO creation
 *
 * @param[in] args Parameter(s) to the event loop (unused)
 */
static void *story_event_loop(void *args);



kernel_pid_t story_init(char thread_priority)
{
    if (story_event_loop_pid == KERNEL_PID_UNDEF) { 
        story_event_loop_pid = thread_create(_story_stack, sizeof(_story_stack), thread_priority, THREAD_CREATE_STACKTEST, story_event_loop, NULL, "story");
    }

    return story_event_loop_pid;
}

static void *story_event_loop(void *args)
{
   /** resolve warning about unused parameter */
   (void)args;

   msg_t message;
   msg_t message_queue[STORY_MESSAGE_QUEUE_SIZE];
   msg_init_queue(message_queue, STORY_MESSAGE_QUEUE_SIZE);

   while(1) {
       msg_receive(&message);
   };
}
