
#include "content.h"
#include "management.h"

#include <stdio.h>

/**
 * @brief Defines the size of a face as a content object in bytes
 * 
 * We consider for a face NDO just the faceid, ifndx, flags, and
 * the timestamp when a face was last accessed (member last_used).
 *
 */
#ifndef SINGLE_FACE_SIZE
#define SINGLE_FACE_SIZE (4u)
#endif

void face_to_content(struct ccnl_prefix_s *prefix, const struct ccnl_face_s* face)
{
    /** */
    unsigned char buffer[SINGLE_FACE_SIZE] = { 0 };
    
    /** set face values to the buffer */
    buffer[0] = face->faceid;
    buffer[1] = face->ifndx;
    buffer[2] = face->flags;
    buffer[3] = face->last_used;
    
    ssize_t size = sizeof(buffer)/sizeof(buffer[0]);
    /** make content object */
    create_content(prefix, buffer, size, false, false);
}

void _management_list_faces(const struct ccnl_relay_s *relay)
{
    struct ccnl_face_s *face = relay->faces;

    while (face != NULL) {
        /** print details on face */
        _management_face_to_string(face);

        /** get the next entry in the faces list */
        face = face->next;
    }
}

void _management_face_to_string(const struct ccnl_face_s* face)
{
    if (face) {
         printf("face\n");
         printf("id: %d, index: %d, flags: %d\n", face->faceid, face->ifndx, face->flags);
         printf("last used: %d\n", face->last_used);
    }
}

