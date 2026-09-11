#ifndef RAY_H
#define RAY_H

#include "color.h"
#include "vec.h"

typedef struct ray
{
    vec3 origin;
    vec3 dir;
} ray;

ray construct_ray(vec3 orig, vec3 direction);
vec3 at(ray ray, double t);

#endif