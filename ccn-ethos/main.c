/*
 * Copyright (C) 2018 MSA Safety 
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
 * @brief       ccn-lite over ethos example (work in progress)
 *
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */

#include "msg.h"
#include "shell.h"
#include "shell_commands.h"
#include "net/gnrc/netif.h"
#include "net/gnrc/pktdump.h"

#include "ccn-lite-riot.h"
#include "ccnl-pkt-builder.h"
#include "tlsf-malloc.h"

#define TLSF_BUFFER     (4096 / sizeof(uint32_t))
static uint32_t _tlsf_heap[TLSF_BUFFER];

/** defined in sys/shell/commands/sc_ccnl.c */
extern int _ccnl_interest(int argc, char **argv); 
/** again, defined in sys/shell/commands/sc_ccnl.c */
extern int _ccnl_content(int argc, char **argv);

/* main thread's message queue */
#define MAIN_QUEUE_SIZE (4)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];


int main(void)
{
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);
    tlsf_create_with_pool(_tlsf_heap, sizeof(_tlsf_heap));
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    /** initialize ccn-lite */
    ccnl_core_init();
    /** run it */
    ccnl_start();

    _ccnl_interest(10, (char **)"/test/data");

    /** run shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}
