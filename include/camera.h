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
    int samples_per_pixel;
    double pixel_samples_scale;

    double focal_length;
    vec3 center;

    vec3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;

} camera;

camera construct_camera();
vec3 ray_color(ray r, int depth, hittableList *world);
void render(camera camera, FILE *file, hittableList *world);
vec3 sample_square();
ray get_ray(camera camera, int i, int j);
