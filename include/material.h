#ifndef MATERIAL_H
#define MATERIAL_H

#include "ray.h"
#include "vec3.h"

typedef struct material
{
    bool scatter(ray r, hit_record *rec, vec3 attenuation, ray scattered);
} material;

#endif