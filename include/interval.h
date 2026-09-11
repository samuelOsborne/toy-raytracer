#ifndef INTERVAL_H
#define INTERVAL_H

#include <stdbool.h>

typedef struct interval
{
    double min;
    double max;
} interval;

interval construct_interval(double min, double max);
double size(interval interval);
bool contains(interval interval, double x);
bool surrounds(interval interval, double x);
double clamp(interval interval, double x);

#endif