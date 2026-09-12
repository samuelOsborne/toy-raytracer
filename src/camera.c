#include "camera.h"
#include "utils.h"

camera construct_camera(vec3 lookFrom, vec3 lookAt, vec3 vup, double vfov, double defocus_angle, double focus_dist)
{
    camera camera;

    camera.aspect_ratio = 16.0 / 9.0;
    camera.image_width = 1200;
    camera.max_depth = 50;
    camera.samples_per_pixel = 500;
    camera.defocus_angle = defocus_angle;
    camera.focus_dist = focus_dist;

    camera.image_height = (int)camera.image_width / camera.aspect_ratio;
    camera.image_height = (camera.image_height < 1) ? 1 : camera.image_height;

    camera.vfov = vfov;
    camera.lookFrom = lookFrom;
    camera.lookAt = lookAt;
    camera.vup = vup;

    double theta = degrees_to_radians(camera.vfov);
    double h = tan(theta / 2);
    double viewport_height = 2.0 * h * camera.focus_dist;
    double viewport_width = viewport_height * ((double)camera.image_width / camera.image_height);

    camera.w = unit_vec3(sub_vec3(camera.lookFrom, camera.lookAt));
    camera.u = unit_vec3(cross_vec3(camera.vup, camera.w));
    camera.v = cross_vec3(camera.w, camera.u);
    vec3 viewport_u = mult_double_vec3(camera.u, viewport_width);
    vec3 viewport_v = mult_double_vec3(mult_double_vec3(camera.v, viewport_height), -1);

    camera.pixel_samples_scale = 1.0 / camera.samples_per_pixel;

    camera.center = camera.lookFrom;

    camera.pixel_delta_u = div_double_vec3(viewport_u, camera.image_width);
    camera.pixel_delta_v = div_double_vec3(viewport_v, camera.image_height);

    vec3 halfViewport = add_vec3(viewport_u, viewport_v);
    halfViewport = mult_double_vec3(halfViewport, -0.5);

    vec3 viewport_upper_left = sub_vec3(camera.center, mult_double_vec3(camera.w, camera.focus_dist));
    viewport_upper_left = add_vec3(viewport_upper_left, halfViewport);

    vec3 half_pixel = mult_double_vec3(add_vec3(camera.pixel_delta_u, camera.pixel_delta_v), 0.5);

    camera.pixel00_loc = add_vec3(viewport_upper_left, half_pixel);
    double defocus_radius = camera.focus_dist * tan(degrees_to_radians(camera.defocus_angle / 2));
    camera.defocus_disk_u = mult_double_vec3(camera.u, defocus_radius);
    camera.defocus_disk_v = mult_double_vec3(camera.v, defocus_radius);

    return camera;
}

ray get_ray(camera camera, int i, int j)
{
    vec3 offset = sample_square();
    vec3 offset_tmp_x = mult_double_vec3(camera.pixel_delta_u, (offset.x + i));
    vec3 offset_tmp_y = mult_double_vec3(camera.pixel_delta_v, (offset.y + j));
    vec3 offset_sum = add_vec3(offset_tmp_x, offset_tmp_y);

    vec3 pixel_sample = add_vec3(camera.pixel00_loc, offset_sum);
    vec3 ray_origin = (camera.defocus_angle <= 0) ? camera.center : defocus_disk_sample(camera);
    vec3 ray_direction = sub_vec3(pixel_sample, ray_origin);

    return construct_ray(ray_origin, ray_direction);
}

vec3 defocus_disk_sample(camera camera)
{
    vec3 p = random_in_unit_disk();
    vec3 u = mult_double_vec3(camera.defocus_disk_u, p.x);
    vec3 v = mult_double_vec3(camera.defocus_disk_v, p.y);
    vec3 res = add_vec3(camera.center, u);

    return add_vec3(res, v);
}

vec3 sample_square()
{
    return construct_vec3(random_double() - 0.5, random_double() - 0.5, 0);
}

vec3 ray_color(ray r, int depth, hittableList *world)
{
    if (depth <= 0)
        return construct_vec3(0, 0, 0);

    hitRecord rec;

    if (list_hit(world, r, construct_interval(0.001, INFINITY), &rec))
    {
        ray scattered;
        vec3 attenuation;

        if (scatter(*rec.mat, r, &rec, &attenuation, &scattered))
            return mult_vec3(ray_color(scattered, depth - 1, world), attenuation);
        return construct_vec3(0, 0, 0);
    }

    vec3 unit_dir = unit_vec3(r.dir);
    double a = 0.5 * (unit_dir.y + 1.0);

    vec3 white = construct_vec3(1.0, 1.0, 1.0);
    vec3 blue = construct_vec3(0.5, 0.7, 1.0);

    blue = mult_double_vec3(blue, a);
    white = mult_double_vec3(white, (1.0 - a));
    return add_vec3(white, blue);
}

void render(camera camera, FILE *output_file, hittableList *world)
{
    for (int j = 0; j < camera.image_height; j++)
    {
        printf("Rendered line : %i\n", j);
        for (int i = 0; i < camera.image_width; i++)
        {
            vec3 pixel_color = construct_vec3(0, 0, 0);
            for (int sample = 0; sample < camera.samples_per_pixel; sample++)
            {
                ray r = get_ray(camera, i, j);
                pixel_color = add_vec3(pixel_color, ray_color(r, camera.max_depth, world));
            }
            pixel_color = mult_double_vec3(pixel_color, camera.pixel_samples_scale);
            write_color_to_file(output_file, pixel_color);
        }
    }
}