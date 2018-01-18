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
 * @brief   FIXME
 *
 * @author  Oliver Hahm <oliver.hahm@inria.fr>
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef HEARSAY_H_
#define HEARSAY_H_

#ifdef __cplusplus
extern "C" {
#endif



#ifdef CPU_NATIVE
#define TLSF_BUFFER     (409600 / sizeof(uint32_t))
#elif defined(CPU_MODEL_KW21D256)
#define TLSF_BUFFER     (10240 / sizeof(uint32_t))
#else
#define TLSF_BUFFER     (45960 / sizeof(uint32_t))
#endif



#ifdef __cplusplus
}
#endif

#endif /* HEARSAY_H_*/
/** @} */
