/*
 * Copyright (C) 2017 MSA Safety
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @{
 *
 * @file
 * @brief   Functions for managing ccn-lite
 *
 * @author  Michael Frey <michael.frey@msasafety.com>
 */

#ifndef MANAGEMENT_H_
#define MANAGEMENT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "ccnl-face.h"
#include "ccnl-relay.h"


/**
 * @brief Creates an NDO out of a face
 *
 * TODO: come up with a better name scheme
 */
void face_to_content(struct ccnl_prefix_s *prefix, const struct ccnl_face_s* face);

/**
 * @brief Returns a list of available faces
 */
void _management_list_faces(const struct ccnl_relay_s *relay);

/**
 * @brief Deletes a given face
 */
void _management_remove_face(void);

/**
 * @brief Creates a new face
 */
void _management_add_face(void);

/**
 * @brief Returns statistics on a face
 */
void _management_get_face(void);

/**
 * @brief Prints data about the interface to the command line
 *
 * The face id does not map to RIOTs interface id.
 * 
 * @param[in] face The face to print statistical data about
 */
void _management_face_to_string(const struct ccnl_face_s* face);

#ifdef __cplusplus
}
#endif

#endif /* MANAGEMENT_H_*/
/** @} */
