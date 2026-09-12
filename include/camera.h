#include <stdlib.h>
#include "vec.h"
#include "hittable_list.h"

typedef struct camera
{
    double aspect_ratio;
    double viewport_height;
    double viewport_width;
    int image_width;
    int image_height;

    int max_depth;
    double vfov;
    vec3 lookFrom;
    vec3 lookAt;
    vec3 vup;
    vec3 u;
    vec3 v;
    vec3 w;

    double defocus_angle;
    double focus_dist;

    vec3 defocus_disk_u;
    vec3 defocus_disk_v;

    int samples_per_pixel;
    double pixel_samples_scale;

    double focal_length;
    vec3 center;

    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

} camera;

camera construct_camera(vec3 lookFrom, vec3 lookAt, vec3 vup, double vfov, double defocus_angle, double focus_dist);
vec3 ray_color(ray r, int depth, hittableList *world);
void render(camera camera, FILE *file, hittableList *world);
vec3 sample_square();
ray get_ray(camera camera, int i, int j);
vec3 defocus_disk_sample(camera camera);