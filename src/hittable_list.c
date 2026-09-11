#include <stdlib.h>
#include <stdio.h>
#include "hittable_list.h"
#include "interval.h"

hittableList *construct_list(sphere *start)
{
    hittableList *list = malloc(sizeof(hittableList));
    list->next = NULL;
    list->sphere = start;
    return list;
}

bool list_hit(hittableList *head, ray r, interval ray_t, hitRecord *record)
{
    hittableList *tmp = head;
    hitRecord tmp_record;

    bool hit_anything = false;
    double closes_so_far = ray_t.max;

    while (tmp != NULL)
    {
        if (sphere_hit(*tmp->sphere, r, construct_interval(ray_t.min, closes_so_far), &tmp_record))
        {
            hit_anything = true;
            closes_so_far = tmp_record.t;
            *record = tmp_record;
        }
        tmp = tmp->next;
    }

    return hit_anything;
}

void add_sphere(hittableList *head, sphere *sphere)
{
    hittableList *tmp = head;
    hittableList *new_node = malloc(sizeof(hittableList));

    if (new_node == NULL)
    {
        printf("Error allocating new record node.");
        return;
    }
    new_node->sphere = sphere;

    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    tmp->next = new_node;
}

// vec3 ray_color(ray r, hittableList *world)
// {
//     hitRecord rec;

//     if (list_hit(world, r, construct_interval(0, infinity), &rec))
//     {
//         return add_vec3(mult_double_vec3(rec.normal, 0.5), mult_double_vec3(construct_vec3(1, 1, 1), 0.5));
//     }

//     vec3 unit_dir = unit_vec3(r.dir);
//     double a = 0.5 * (unit_dir.y + 1.0);

//     vec3 white = construct_vec3(1.0, 1.0, 1.0);
//     vec3 blue = construct_vec3(0.5, 0.7, 1.0);

//     blue = mult_double_vec3(blue, a);
//     white = mult_double_vec3(white, (1.0 - a));
//     return add_vec3(white, blue);
// }

void print_records(hittableList *head)
{
    hittableList *tmp = head;

    while (tmp != NULL)
    {
        if (tmp->sphere != NULL)
            printf("sphere radius: %f\n", tmp->sphere->radius);
        else
            printf("Null \n");
        tmp = tmp->next;
    }
}