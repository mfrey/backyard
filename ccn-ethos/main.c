/*
 * Copyright (C) 2015 Inria
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
 * @brief       Basic ccn-lite relay example (produce and consumer via shell)
 *
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include <stdio.h>

#include "tlsf-malloc.h"
#include "msg.h"
#include "shell.h"
#include "ccn-lite-riot.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/pktdump.h"

/** defined in sys/shell/commands/sc_ccnl.c */
extern int _ccnl_interest(int argc, char **argv); 
/** again, defined in sys/shell/commands/sc_ccnl.c */
extern int _ccnl_content(int argc, char **argv);

/* main thread's message queue */
#define MAIN_QUEUE_SIZE     (2)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

/* 10kB buffer for the heap should be enough for everyone */
#define TLSF_BUFFER     (10240 / sizeof(uint32_t))
static uint32_t _tlsf_heap[TLSF_BUFFER];

/** event timer for generating interests */
evtimer_t ccn_timer;

void _generate_interest(evtimer_event_t *event) 
{
    printf("timer was called\n");

    char *arr[3] = { "ccnl_cs", "/some/content", "yeah" };

    /** replace static prefix with a generated prefix + counter */
    _ccnl_content(3, arr);
    

    event->offset = 10000;

    /** enqueue event */
    evtimer_add(&ccn_timer, event);
}

int main(void)
{
    tlsf_add_global_pool(_tlsf_heap, sizeof(_tlsf_heap));
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    puts("Basic CCN-Lite example");

    /** initialize ccn-lite */
    ccnl_core_init();
    /** start ccn-lite */
    ccnl_start();

    /** define timer event */
    evtimer_event_t new_event;
    new_event.offset = 10000;

    /** initialize event timer */
    evtimer_init(&ccn_timer, &_generate_interest);
    /** enqueue event */
    evtimer_add(&ccn_timer, &new_event);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);
    return 0;
}
