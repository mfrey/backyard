/*
 * Copyright (C) 2017 MSA Safety 
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
 * @brief       TODO
 *
 * @author      Michael Frey <michael.frey@msasafety.com>
 *
 * @}
 */
#include "debug.h"
#include "settings.h"

#include "msg.h"
#include "shell.h"
#include "shell_commands.h"

#ifdef MODULE_TLSF
#include "tlsf-malloc.h"
#endif

#ifdef MODULE_TLSF
#define TLSF_BUFFER     (10240 / sizeof(uint32_t))
static uint32_t _tlsf_heap[TLSF_BUFFER];
#endif

/* main thread's message queue */
#define MAIN_QUEUE_SIZE     (8)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
#ifdef MODULE_TLSF
    tlsf_create_with_pool(_tlsf_heap, sizeof(_tlsf_heap));
#endif
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    /** initialze ccn-lite */
    ccnl_core_init();
    /** run it */
    ccnl_start();

    /** radio settings */
    uint16_t channel = 15;
    uint16_t tx_power = 8;
    uint16_t src_len = 8;
    netopt_enable_t cca = NETOPT_DISABLE;

    /** update radio settings */
    set_radio_settings(channel, tx_power, src_len, cca);

    /** run shell */
    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

