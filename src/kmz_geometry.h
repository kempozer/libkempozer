#ifndef kmz_geometry_h
#define kmz_geometry_h

#include <stdio.h>
#include <stdint.h>
#include "kmz_numerics.h"

// region Types:
struct kmz_size_t {
    uint16_t w, h;
};
typedef struct kmz_size_t KmzSize;

struct kmz_size_f_t {
    float w, h;
};
typedef struct kmz_size_f_t KmzSizeF;

struct kmz_point_t {
    ssize_t x, y;
};
typedef struct kmz_point_t KmzPoint;

struct kmz_point_f_t {
    float x, y;
};
typedef struct kmz_point_f_t KmzPointF;

struct kmz_rectangle_t {
    KmzPoint pos;
    KmzSize size;
};
typedef struct kmz_rectangle_t KmzRectangle;

struct kmz_rectangle_f_t {
    KmzPointF pos;
    KmzSizeF size;
};
typedef struct kmz_rectangle_f_t KmzRectangleF;

struct kmz_line_t {
    KmzPoint start;
    KmzPoint end;
};
typedef struct kmz_line_t KmzLine;

struct kmz_line_f_t {
    KmzPointF start;
    KmzPointF end;
};
typedef struct kmz_line_f_t KmzLineF;
// endregion;

// region Functions:
/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzLineF__equal_to(KmzLineF me, KmzLineF other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzRectangleF__equal_to(KmzRectangleF me, KmzRectangleF other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzRectangle__equal_to(KmzRectangle me, KmzRectangle other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzSize__equal_to(KmzSize me, KmzSize other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzSizeF__equal_to(KmzSizeF me, KmzSizeF other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzPoint__equal_to(KmzPoint me, KmzPoint other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzPointF__equal_to(KmzPointF me, KmzPointF other);

/**
 * Determines if the provided shapes are equal.
 */
KmzBool KmzLine__equal_to(KmzLine me, KmzLine other);
// endregion;

// region Constants:
static const KmzSize KmzSize__ZERO = {.w=0, .h=0};
static const KmzSizeF KmzSizeF__ZERO = {.w=0., .h=0.};
static const KmzPoint KmzPoint__ZERO = {.x=0, .y=0};
static const KmzPointF KmzPointF__ZERO = {.x=0., .y=0.};
static const KmzRectangle KmzRectangle__ZERO = {.pos={.x=0, .y=0}, .size={.w=0, .h=0}};
static const KmzRectangleF KmzRectangleF__ZERO = {.pos={.x=0., .y=0.}, .size={.w=0., .h=0.}};
static const KmzLine KmzLine__ZERO = {.start={.x=0, .y=0}, .end={.x=0, .y=0}};
static const KmzLineF KmzLineF__ZERO = {.start={.x=0., .y=0.}, .end={.x=0., .y=0.}};
// endregion;

// region Helpers:
#define kmz_size(w, h) (KmzSize) {w,h}

#define kmz_sizef(w, h) (KmzSizeF) {w,h}

#define kmz_point(x, y) (KmzPoint) {x,y}

#define kmz_pointf(x, y) (KmzPoint) {x,y}

#define kmz_rectangle(pos, size) (KmzRectangle) {pos,size}

#define kmz_rectanglef(pos, size) (KmzRectangleF) {pos,size}

#define kmz_line(start, end) (KmzLine) {start,end}

#define kmz_linef(start, end) (KmzLineF) {start,end}
// endregion;

#endif /* kmz_geometry_h */
