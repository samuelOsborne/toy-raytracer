#include <math.h>
#include "sphere.h"
#include "interval.h"

sphere construct_sphere(vec3 center, double radius, material *mat)
{
    sphere sphere;

    sphere.center = center;
    sphere.radius = fmax(0, radius);
    sphere.mat = mat;

    return sphere;
}

bool sphere_hit(sphere sphere, ray r, interval ray_t, hitRecord *record)
{
    vec3 oc = sub_vec3(sphere.center, r.origin);
    double a = length_squared(r.dir);
    double h = dot_prod_vec3(r.dir, oc);
    double c = length_squared(oc) - sphere.radius * sphere.radius;
    double discriminant = (h * h) - (a * c);

    if (discriminant < 0)
        return false;

    double sqrtd = sqrt(discriminant);
    double root = (h - sqrtd) / a;
    if (!surrounds(ray_t, root))
    {
        root = (h + sqrtd) / a;
        if (!surrounds(ray_t, root))
            return false;
    }
    record->t = root;
    record->p = at(r, record->t);

    vec3 outward_normal = (sub_vec3(record->p, sphere.center));
    outward_normal = div_double_vec3(outward_normal, sphere.radius);
    set_face_normal(record, r, outward_normal);
    record->mat = sphere.mat;

    record->normal = sub_vec3(record->p, sphere.center);
    record->normal = div_double_vec3(record->normal, sphere.radius);
    return true;
}