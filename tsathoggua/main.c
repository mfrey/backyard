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
#include "shell.h"
#include "tsathoggua.h"
#include "shell_commands.h"

#ifdef MODULE_TLSF
#include "tlsf-malloc.h"
#endif

#ifdef MODULE_TLSF
static uint32_t _tlsf_heap[TLSF_BUFFER];
#endif

int main(int argc, char **argv)
{
#ifdef MODULE_TLSF
    tlsf_create_with_pool(_tlsf_heap, sizeof(_tlsf_heap));
#endif

    char line_buf[SHELL_DEFAULT_BUFSIZE];
    shell_run(NULL, line_buf, SHELL_DEFAULT_BUFSIZE);

    return 0;
}

