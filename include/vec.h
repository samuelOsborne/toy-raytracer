#ifndef VEC_H
#define VEC_H

#include <stdbool.h>

typedef struct vec3
{
    double x;
    double y;
    double z;
} vec3;

vec3 construct_vec3(double x, double y, double z);
vec3 add_vec3(vec3 a, vec3 b);
vec3 add_double_vec3(vec3 a, double b);
vec3 sub_vec3(vec3 a, vec3 b);
vec3 sub_double_vec3(vec3 a, double b);
vec3 mult_vec3(vec3 a, vec3 b);
vec3 mult_double_vec3(vec3 a, double b);
vec3 div_vec3(vec3 a, vec3 b);
vec3 div_double_vec3(vec3 a, double b);
vec3 unit_vec3(vec3 a);
vec3 cross_vec3(vec3 a, vec3 b);
double dot_prod_vec3(vec3 a, vec3 b);
double length_squared(vec3 a);
double length(vec3 a);
vec3 random_vec3();
vec3 random_clamped_vec3(double min, double max);
vec3 random_unit_vector();
vec3 random_on_hemisphere(vec3 normal);
vec3 reflect(vec3 v, vec3 n);
vec3 refract(vec3 uv, vec3 n, double etai_over_etat);
bool near_zero(vec3 vec);
vec3 random_in_unit_disk();

#endif