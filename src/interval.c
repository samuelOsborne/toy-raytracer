#include <stdbool.h>
#include "interval.h"

interval construct_interval(double min, double max)
{
    interval interval;

    interval.max = max;
    interval.min = min;

    return interval;
}

double size(interval interval)
{
    return interval.max - interval.min;
}

bool contains(interval interval, double x)
{
    return interval.min <= x && x <= interval.max;
}

bool surrounds(interval interval, double x)
{
    return interval.min < x && x < interval.max;
}

double clamp(interval interval, double x)
{
    if (x < interval.min)
        return interval.min;
    if (x > interval.max)
        return interval.max;
    return x;
}