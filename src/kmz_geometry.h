#ifndef kmz_geometry_h
#define kmz_geometry_h

#include <stdio.h>
#include <stdint.h>

struct kmz_size_t {
    uint16_t w, h;
};
typedef struct kmz_size_t KmzSize;

static const KmzSize KmzSize__ZERO = {.w=0, .h=0};

struct kmz_size_f_t {
    float w, h;
};
typedef struct kmz_size_f_t KmzSizeF;

static const KmzSizeF KmzSizeF__ZERO = {.w=0., .h=0.};

struct kmz_point_t {
    ssize_t x, y;
};
typedef struct kmz_point_t KmzPoint;

static const KmzPoint KmzPoint__ZERO = {.x=0, .y=0};

struct kmz_point_f_t {
    float x, y;
};
typedef struct kmz_point_f_t KmzPointF;

static const KmzPointF KmzPointF__ZERO = {.x=0., .y=0.};

struct kmz_rectangle_t {
    KmzPoint pos;
    KmzSize size;
};
typedef struct kmz_rectangle_t KmzRectangle;

static const KmzRectangle KmzRectangle__ZERO = {.pos={.x=0, .y=0}, .size={.w=0, .h=0}};

struct kmz_rectangle_f_t {
    KmzPointF pos;
    KmzSizeF size;
};
typedef struct kmz_rectangle_f_t KmzRectangleF;

static const KmzRectangleF KmzRectangleF__ZERO = {.pos={.x=0., .y=0.}, .size={.w=0., .h=0.}};

struct kmz_line_t {
    KmzPoint start;
    KmzPoint end;
};
typedef struct kmz_line_t KmzLine;

static const KmzLine KmzLine__ZERO = {.start={.x=0, .y=0}, .end={.x=0, .y=0}};

struct kmz_line_f_t {
    KmzPointF start;
    KmzPointF end;
};
typedef struct kmz_line_f_t KmzLineF;

static const KmzLineF KmzLineF__ZERO = {.start={.x=0., .y=0.}, .end={.x=0., .y=0.}};

#endif /* kmz_geometry_h */
