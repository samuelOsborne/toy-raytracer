#include <math.h>
#include "color.h"
#include "vec.h"
#include "interval.h"

double linear_to_gamma(double linear_component)
{
    if (linear_component > 0)
        return sqrt(linear_component);
    return 0;
}

void write_color_to_file(FILE *file, vec3 color)
{
    double r = linear_to_gamma(color.x);
    double g = linear_to_gamma(color.y);
    double b = linear_to_gamma(color.z);

    interval intensity = construct_interval(0.000, 0.999);
    int ir = (int)256 * clamp(intensity, r);
    int ig = (int)256 * clamp(intensity, g);
    int ib = (int)256 * clamp(intensity, b);

    fprintf(file, "%i %i %i\n", ir, ig, ib);
}
