#ifndef material_H
#define material_H

#include "vec.h"
#include "hit_record.h"
#include "ray.h"

struct hitRecord;

typedef struct material
{
    int code;
    vec3 albedo;
} material;

material *construct_material(int code, vec3 albedo);
bool scatter(material lam, ray r_in, struct hitRecord *rc, vec3 *attenuation, ray *scattered);

#endif