#ifndef kmz_geometry_h
#define kmz_geometry_h

#include <stdio.h>
#include <stdint.h>

struct kmz_rectangle_t {
    uint16_t w, h;
};
typedef struct kmz_rectangle_t KmzRectangle;

static const KmzRectangle KmzRectangle__ZERO = {.w=0, .h=0};

struct kmz_point_t {
    ssize_t x, y;
};
typedef struct kmz_point_t KmzPoint;

static const KmzPoint KmzPoint__ZERO = {.x=0, .y=0};

#endif /* kmz_geometry_h */
