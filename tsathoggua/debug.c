/*
 * Copyright (C) FIXME
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
#include "ccn-lite-riot.h"

void print_content_store(int argc, char **argv)
{
    (void) argc; 
    (void) argv;
    ccnl_cs_dump(&ccnl_relay);
}
