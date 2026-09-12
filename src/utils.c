#include <stdlib.h>
#include <math.h>
#include "utils.h"

const double pi = 3.1415926535897932385;
// const double infinity = INFINITY;

double degrees_to_radians(double degrees)
{
    return degrees * pi / 180.0;
}

double random_double()
{
    return rand() / (RAND_MAX + 1.0);
}

double random_double_capped(double min, double max)
{
    return min + (max - min) * random_double();
}
