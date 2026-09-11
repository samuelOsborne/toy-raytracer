#include <math.h>
#include <stdbool.h>
#include "ray.h"
#include "hittable_list.h"

ray construct_ray(vec3 orig, vec3 direction)
{
    ray new_ray;

    new_ray.origin = orig;
    new_ray.dir = direction;

    return new_ray;
}

double hit_sphere(vec3 center, double radius, ray r)
{
    vec3 oc = sub_vec3(center, r.origin);
    double a = length_squared(r.dir);
    double h = dot_prod_vec3(r.dir, oc);
    double c = length_squared(oc) - radius * radius;
    double discriminant = (h * h) - (a * c);

    if (discriminant < 0)
    {
        return -1;
    }
    else
    {
        return (h - sqrt(discriminant)) / a;
    }
}

vec3 at(ray ray, double t)
{
    return add_vec3(ray.origin, mult_double_vec3(ray.dir, t));
}