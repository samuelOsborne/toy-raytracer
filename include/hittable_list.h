#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "sphere.h"
#include "hit_record.h"
#include "ray.h"

typedef struct hittableList
{
    struct sphere *sphere;
    struct hittableList *next;
} hittableList;

// vec3 ray_color(ray r, hittableList *world);
hittableList *construct_list(sphere *start);
void add_sphere(hittableList *head, sphere *sphere);
void print_records(hittableList *head);
bool list_hit(hittableList *head, ray r, interval interval, hitRecord *record);
#endif