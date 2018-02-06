
#include "management.h"

#include <stdio.h>

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

