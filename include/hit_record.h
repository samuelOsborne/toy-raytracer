#ifndef HIT_RECORD_H
#define HIT_RECORD_H

#include <stdbool.h>
#include "vec.h"
#include "ray.h"
#include "material.h"

struct material;

typedef struct hitRecord
{
    vec3 p;
    vec3 normal;
    struct material *mat;
    double t;
    bool front_face;
} hitRecord;

hitRecord *construct_hit_record();
void set_face_normal(hitRecord *hit, ray r, vec3 normal);

#endif