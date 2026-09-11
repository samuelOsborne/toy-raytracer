#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "vec.h"

vec3 construct_vec3(double x, double y, double z)
{
    vec3 result;

    result.x = x;
    result.y = y;
    result.z = z;

    return result;
}

vec3 add_vec3(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x + b.x;
    result.y = a.y + b.y;
    result.z = a.z + b.z;

    return result;
}

vec3 add_double_vec3(vec3 a, double b)
{
    vec3 result;

    result.x = a.x + b;
    result.y = a.y + b;
    result.z = a.z + b;

    return result;
}

vec3 sub_vec3(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x - b.x;
    result.y = a.y - b.y;
    result.z = a.z - b.z;

    return result;
}

vec3 sub_double_vec3(vec3 a, double b)
{
    vec3 result;

    result.x = a.x - b;
    result.y = a.y - b;
    result.z = a.z - b;

    return result;
}

vec3 mult_vec3(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x * b.x;
    result.y = a.y * b.y;
    result.z = a.z * b.z;

    return result;
}

vec3 mult_double_vec3(vec3 a, double b)
{
    vec3 result;

    result.x = a.x * b;
    result.y = a.y * b;
    result.z = a.z * b;

    return result;
}

vec3 div_vec3(vec3 a, vec3 b)
{
    vec3 result;

    result.x = a.x / b.x;
    result.y = a.y / b.y;
    result.z = a.z / b.z;

    return result;
}

vec3 div_double_vec3(vec3 a, double b)
{
    return mult_double_vec3(a, (1 / b));
}

double dot_prod_vec3(vec3 a, vec3 b)
{
    return ((a.x * b.x) + (a.y * b.y) + (a.z * b.z));
}

vec3 cross_vec3(vec3 a, vec3 b)
{
    return construct_vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - b.y * a.x);
}

double length_squared(vec3 a)
{
    return a.x * a.x + a.y * a.y + a.z * a.z;
}

double length(vec3 a)
{
    return sqrt(length_squared(a));
}

vec3 unit_vec3(vec3 a)
{
    return div_double_vec3(a, length(a));
}

vec3 random_vec3()
{
    return construct_vec3(random_double(), random_double(), random_double());
}

vec3 random_clamped_vec3(double min, double max)
{
    return construct_vec3(random_double_capped(min, max), random_double_capped(min, max), random_double_capped(min, max));
}

vec3 random_unit_vector()
{
    while (true)
    {
        vec3 p = random_clamped_vec3(-1, 1);
        double lensq = length_squared(p);
        if (1e-160 < lensq && lensq <= 1)
            return div_double_vec3(p, sqrt(lensq));
    }
}

vec3 random_on_hemisphere(vec3 normal)
{
    vec3 on_unit_sphere = random_unit_vector();
    if (dot_prod_vec3(on_unit_sphere, normal) > 0.0)
    {
        return on_unit_sphere;
    }
    else
    {
        return mult_double_vec3(on_unit_sphere, -1.0);
    }
}

bool near_zero(vec3 vec)
{
    double s = 1e-8;

    return (fabs(vec.x) < s && fabs(vec.y) < s && fabs(vec.z) < s);
}

vec3 reflect(vec3 v, vec3 n)
{
    vec3 tmp_dot = mult_double_vec3(n, dot_prod_vec3(v, n) * 2);

    // vec3 tmp_dot = mult_double_vec3(n, dot_prod_vec3(v, n));
    // tmp_dot = mult_double_vec3(tmp_dot, 2);

    return sub_vec3(v,tmp_dot);
}