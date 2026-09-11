#ifndef SPHERE_H
#define SPHERE_H

#include <stdbool.h>
#include "vec.h"
#include "hit_record.h"
#include "interval.h"

typedef struct sphere
{
    vec3 center;
    double radius;
} sphere;

bool sphere_hit(sphere sphere, ray r, interval interval, hitRecord *record);
sphere construct_sphere(vec3 center, double radius);

#endif