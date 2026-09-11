#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include "utils.h"
#include "material.h"

material *construct_material(int code, vec3 albedo, double fuzz, double refraction)
{
    material *mat = malloc(sizeof(material));

    if (mat == NULL)
        return NULL;
    mat->code = code;
    mat->albedo = albedo;
    mat->fuzz = fuzz < 1 ? fuzz : 1;
    mat->refraction_index = refraction;

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
        vec3 fuzzed_vec = mult_double_vec3(random_unit_vector(), mat.fuzz);
        reflected = add_vec3(unit_vec3(reflected), fuzzed_vec);

        *scattered = construct_ray(rc->p, reflected);
        *attenuation = mat.albedo;
        return dot_prod_vec3(scattered->dir, rc->normal) > 0;
    }

    // code 2 - dielectric
    if (mat.code == 2)
    {
        *attenuation = construct_vec3(1.0, 1.0, 1.0);
        double ri = rc->front_face ? (1.0 / mat.refraction_index) : mat.refraction_index;
        vec3 unit_direction = unit_vec3(r_in.dir);

        double cos_theta = fmin(dot_prod_vec3(mult_double_vec3(unit_direction, -1), rc->normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        bool cannot_refract = ri * sin_theta > 1.0;
        vec3 direction;

        if (cannot_refract || reflectance(cos_theta, ri) > random_double())
            direction = reflect(unit_direction, rc->normal);
        else
            direction = refract(unit_direction, rc->normal, ri);

        *scattered = construct_ray(rc->p, direction);
        return true;
    }

    return false;
}

double reflectance(double cosine, double refraction_index)
{
    double r0 = (1 - refraction_index) / (1 + refraction_index);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow(1 - cosine, 5);
}