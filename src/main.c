#include <stdlib.h>
#include <stdio.h>
#include "vec.h"
#include "ray.h"
#include "camera.h"
#include "hittable_list.h"
#include "hit_record.h"
#include "material.h"

int main(int ac, char **av)
{
    material *ground = construct_material(0, construct_vec3(0.8, 0.8, 0.0), 0.0, 0);
    material *center = construct_material(0, construct_vec3(0.1, 0.2, 0.5), 0.0, 0);

    material *left = construct_material(2, construct_vec3(0.8, 0.8, 0.8), 0.3, 1.50);
    material *bubble_mat = construct_material(2, construct_vec3(0.8, 0.8, 0.8), 0.3, 1.00 / 1.50);
    material *right = construct_material(1, construct_vec3(0.8, 0.6, 0.2), 1.0, 0);

    sphere *record_a = malloc(sizeof(sphere));
    record_a->center = construct_vec3(0, 0, -1);
    record_a->radius = 0.5;
    record_a->mat = center;

    sphere *record_b = malloc(sizeof(sphere));
    record_b->center = construct_vec3(0, -100.5, -1);
    record_b->radius = 100;
    record_b->mat = ground;

    sphere *record_c = malloc(sizeof(sphere));
    record_c->center = construct_vec3(-1, 0, -1);
    record_c->radius = 0.5;
    record_c->mat = left;

    sphere *bubble = malloc(sizeof(sphere));
    bubble->center = construct_vec3(-1.0, 0.0, -1.0);
    bubble->radius = 0.4;
    bubble->mat = bubble_mat;

    sphere *record_d = malloc(sizeof(sphere));
    record_d->center = construct_vec3(1, 0, -1);
    record_d->radius = 0.5;
    record_d->mat = right;

    hittableList *world = construct_list(record_b);
    add_sphere(world, record_a);
    add_sphere(world, record_c);
    add_sphere(world, bubble);
    add_sphere(world, record_d);

    print_records(world);

    FILE *output_file = fopen("./output/output.ppm", "w");

    camera camera;

    if (output_file == NULL)
    {
        return 1;
    }

    camera = construct_camera();

    fprintf(output_file, "P3\n%i %i\n255\n", camera.image_width, camera.image_height);

    render(camera, output_file, world);

    fclose(output_file);
}