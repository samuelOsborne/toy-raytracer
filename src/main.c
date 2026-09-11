#include <stdlib.h>
#include <stdio.h>
#include "vec.h"
#include "ray.h"
#include "camera.h"
#include "hittable_list.h"
#include "hit_record.h"

int main(int ac, char **av)
{
    sphere *record_a = malloc(sizeof(sphere));
    record_a->center = construct_vec3(0, 0, -1);
    record_a->radius = 0.5;

    sphere *record_b = malloc(sizeof(sphere));
    record_b->center = construct_vec3(0, -100.5, -1);
    record_b->radius = 100;

    sphere *record_c = malloc(sizeof(sphere));
    record_c->center = construct_vec3(-1, 0, -1);
    record_c->radius = 0.5;

    sphere *record_d = malloc(sizeof(sphere));
    record_d->center = construct_vec3(1, 0, -1);
    record_d->radius = 0.5;

    hittableList *world = construct_list(record_b);
    add_sphere(world, record_a);
    add_sphere(world, record_c);
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