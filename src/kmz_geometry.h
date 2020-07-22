/*-
  BSD 3-Clause License

  Copyright (c) 2020, Kempozer
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

#ifndef kmz_geometry_h
#define kmz_geometry_h

#include <stdint.h>

#include "kmz_config.h"
#include "kmz_shared.h"

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

struct kmz_polygon_t {
    KmzBool closed;
    size_t count;
    KmzPoint * points;
};
typedef struct kmz_polygon_t KmzPolygon;

struct kmz_polygon_f_t {
    KmzBool closed;
    size_t count;
    KmzPointF * points;
};
typedef struct kmz_polygon_f_t KmzPolygonF;

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzLineF__equal_to(const KmzLineF me, const KmzLineF other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzRectangleF__equal_to(const KmzRectangleF me, const KmzRectangleF other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzRectangle__equal_to(const KmzRectangle me, const KmzRectangle other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzSize__equal_to(const KmzSize me, const KmzSize other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzSizeF__equal_to(const KmzSizeF me, const KmzSizeF other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzPoint__equal_to(const KmzPoint me, const KmzPoint other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzPointF__equal_to(const KmzPointF me, const KmzPointF other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzLine__equal_to(const KmzLine me, const KmzLine other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzPolygonF__equal_to(const KmzPolygonF me, const KmzPolygonF other);

/**
 * Determines if the provided shapes are equal.
 */
const KmzBool KmzPolygon__equal_to(const KmzPolygon me, const KmzPolygon other);

extern const KmzSize KmzSize__ZERO;
extern const KmzSizeF KmzSizeF__ZERO;
extern const KmzPoint KmzPoint__ZERO;
extern const KmzPointF KmzPointF__ZERO;
extern const KmzRectangle KmzRectangle__ZERO;
extern const KmzRectangleF KmzRectangleF__ZERO;
extern const KmzLine KmzLine__ZERO;
extern const KmzLineF KmzLineF__ZERO;
extern const KmzPolygon KmzPolygon__ZERO;
extern const KmzPolygonF KmzPolygonF__ZERO;

#endif /* kmz_geometry_h */
