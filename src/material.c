#include <stdlib.h>
#include "material.h"

material *construct_material(int code, vec3 albedo)
{
    material *mat = malloc(sizeof(material));

    if (mat == NULL)
        return NULL;
    mat->code = code;
    mat->albedo = albedo;

    return mat;
}

bool scatter(material mat, ray r_in, hitRecord *rc, vec3 *attenuation, ray *scattered)
{
    // code 0 - lambertian
    if (mat.code == 0)
    {
        vec3 scatter_direction = add_vec3(rc->normal, random_unit_vector());

        if (near_zero(scatter_direction))
            scatter_direction = rc->normal;

        *scattered = construct_ray(rc->p, scatter_direction);
        *attenuation = mat.albedo;
        return true;
    }

    // code 1 - metal
    if (mat.code == 1)
    {
        vec3 reflected = reflect(r_in.dir, rc->normal);
        *scattered = construct_ray(rc->p, reflected);
        *attenuation = mat.albedo;
        return true;
    }

    return false;
}