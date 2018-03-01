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
#include "content.h"
#include "ccnl-producer.h"


#include "msg.h"
#include "shell.h"
#include "shell_commands.h"

#ifdef MODULE_TLSF
#include "tlsf-malloc.h"
#endif

#define TLSF_BUFFER     (10240 / sizeof(uint32_t))

#ifdef MODULE_TLSF
static uint32_t _tlsf_heap[TLSF_BUFFER];
#endif

/* main thread's message queue */
#define MAIN_QUEUE_SIZE     (2)
static msg_t _main_msg_queue[MAIN_QUEUE_SIZE];

const shell_command_t shell_commands[] = {
/*  {name, desc, cmd },                         */
    {"cs", "Print CCN-lite content store", print_content_store},
    {"stats", "Print statistics on the CCN-lite packet interface", print_stats},
    {NULL, NULL, NULL}
};

int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;
#ifdef MODULE_TLSF
    tlsf_create_with_pool(_tlsf_heap, sizeof(_tlsf_heap));
#endif
    msg_init_queue(_main_msg_queue, MAIN_QUEUE_SIZE);

    /**
     * Set the local producer to a function which generates content via CCN-lite's
     * \ref ccnl_mkContentObject function
     */
    //ccnl_set_local_producer(content_mk_content_object);

    /**
     * Set the local producer to a function which provides a buffer which contains
     * data which is passed to the \ref ccnl_mkContentObject function
     */
    ccnl_set_local_producer(content_mk_simple_content);

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(shell_commands, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

