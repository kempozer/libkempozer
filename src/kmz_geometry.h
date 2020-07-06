#ifndef kmz_geometry_h
#define kmz_geometry_h

#include <stdio.h>
#include <stdint.h>

/**
 * Provides a geometric shape that represents a rectangle.
 */
struct kmz_rectangle_t {
    uint16_t w, h;
};
typedef struct kmz_rectangle_t kmz_rectangle;

/**
 * A zero value rectangle.
 */
static const kmz_rectangle kmz_rectangle__ZERO = {.w=0, .h=0};

/**
 * Provides a geometric shape that represents a point.
 */
struct kmz_point_t {
    ssize_t x, y;
};
typedef struct kmz_point_t kmz_point;

/**
 * A zero value point.
 */
static const kmz_point kmz_point__ZERO = {.x=0, .y=0};

// region Functions:
kmz_rectangle kmz_rectangle_from_dimen(size_t w, size_t h);

kmz_point kmz_point_from_coord(ssize_t x, ssize_t y);
// endregion;

#endif /* kmz_geometry_h */
