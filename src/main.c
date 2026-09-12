#include <stdlib.h>
#include <stdio.h>
#include "vec.h"
#include "ray.h"
#include "camera.h"
#include "hittable_list.h"
#include "hit_record.h"
#include "material.h"
#include "utils.h"

sphere *make_sphere(vec3 center, double radius, material *mat)
{
    sphere *s = malloc(sizeof(sphere));
    *s = construct_sphere(center, radius, mat);
    return s;
}

int main(int ac, char **av)
{
    material *ground_material = construct_material(0, construct_vec3(0.5, 0.5, 0.5), 0.0, 0);
    hittableList *world = construct_list(make_sphere(construct_vec3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double choose_mat = random_double();
            vec3 center = construct_vec3(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());

            if (length(sub_vec3(center, construct_vec3(4, 0.2, 0))) > 0.9)
            {
                material *sphere_material;

                if (choose_mat < 0.8)
                {
                    // diffuse
                    vec3 albedo = mult_vec3(random_vec3(), random_vec3());
                    sphere_material = construct_material(0, albedo, 0.0, 0);
                    add_sphere(world, make_sphere(center, 0.2, sphere_material));
                }
                else if (choose_mat < 0.95)
                {
                    // metal
                    vec3 albedo = random_clamped_vec3(0.5, 1);
                    double fuzz = random_double_capped(0, 0.5);
                    sphere_material = construct_material(1, albedo, fuzz, 0);
                    add_sphere(world, make_sphere(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = construct_material(2, construct_vec3(1, 1, 1), 0.0, 1.5);
                    add_sphere(world, make_sphere(center, 0.2, sphere_material));
                }
            }
        }
    }

    material *material1 = construct_material(2, construct_vec3(1, 1, 1), 0.0, 1.5);
    add_sphere(world, make_sphere(construct_vec3(0, 1, 0), 1.0, material1));

    material *material2 = construct_material(0, construct_vec3(0.4, 0.2, 0.1), 0.0, 0);
    add_sphere(world, make_sphere(construct_vec3(-4, 1, 0), 1.0, material2));

    material *material3 = construct_material(1, construct_vec3(0.7, 0.6, 0.5), 0.0, 0);
    add_sphere(world, make_sphere(construct_vec3(4, 1, 0), 1.0, material3));

    FILE *output_file = fopen("./output/13_final_scene.ppm", "w");

    if (output_file == NULL)
    {
        return 1;
    }

    camera camera = construct_camera(construct_vec3(13, 2, 3), construct_vec3(0, 0, 0), construct_vec3(0, 1, 0), 20, 0.6, 10.0);

    fprintf(output_file, "P3\n%i %i\n255\n", camera.image_width, camera.image_height);

    render(camera, output_file, world);

    fclose(output_file);
}
