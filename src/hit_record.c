#include <stdlib.h>
#include "hit_record.h"

hitRecord *construct_hit_record()
{
    hitRecord *record = malloc(sizeof(hitRecord));

    if (record == NULL)
    {
        return NULL;
    }
    return record;
}

void set_face_normal(hitRecord *hit, ray r, vec3 normal)
{
    hit->front_face = dot_prod_vec3(r.dir, normal) < 0;
    hit->normal = hit->front_face ? normal : mult_double_vec3(normal, -1);
}