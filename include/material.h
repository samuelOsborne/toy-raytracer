#ifndef material_H
#define material_H

#include "vec.h"
#include "hit_record.h"
#include "ray.h"

struct hitRecord;

typedef struct material
{
    int code;
    double fuzz;
    vec3 albedo;
    double refraction_index;
} material;

material *construct_material(int code, vec3 albedo, double fuzz, double refraction);
bool scatter(material lam, ray r_in, struct hitRecord *rc, vec3 *attenuation, ray *scattered);
double reflectance(double cosine, double refraction_index);

#endif