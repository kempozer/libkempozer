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

#ifndef libkempozer_geometry_h
#define libkempozer_geometry_h

#include <stdlib.h>
#include <stdint.h>
#include <libkempozer.h>

// region Integer Geometry:

/**
 * Defines the structure of an integer-based dimension.
 */
struct kmz_size_t {
    uint16_t w;
    uint16_t h;
};
typedef struct kmz_size_t KmzSize;

/**
 * Defines the structure of an integer-based coordinate position.
 */
struct kmz_point_t {
    ssize_t x;
    ssize_t y;
};
typedef struct kmz_point_t KmzPoint;

/**
 * Defines the structure of an integer-based positioned rectangle.
 */
struct kmz_rectangle_t {
    KmzPoint pos;
    KmzSize size;
};
typedef struct kmz_rectangle_t KmzRectangle;

/**
 * Defines the structure of an integer-based positioned line.
 */
struct kmz_line_t {
    KmzPoint start;
    KmzPoint end;
};
typedef struct kmz_line_t KmzLine;

/**
 * Defines the structure of an integer-based positioned polygon.
 */
struct kmz_polygon_t {
    KmzBool closed;
    size_t count;
    KmzPoint * points;
};
typedef struct kmz_polygon_t KmzPolygon;

/**
 * Defines the structure of an integer-based positioned circle.
 */
struct kmz_circle_t {
    KmzPoint center;
    size_t radius;
};
typedef struct kmz_circle_t KmzCircle;

// endregion;



// region Float Geometry:

/**
 * Defines the structure of a float-based dimension.
 */
struct kmz_size_f_t {
    float w;
    float h;
};
typedef struct kmz_size_f_t KmzSizeF;

/**
 * Defines the structure of a float-based coordinate position.
 */
struct kmz_point_f_t {
    float x;
    float y;
};
typedef struct kmz_point_f_t KmzPointF;

/**
 * Defines the structure of a float-based positioned rectangle.
 */
struct kmz_rectangle_f_t {
    KmzPointF pos;
    KmzSizeF size;
};
typedef struct kmz_rectangle_f_t KmzRectangleF;

/**
 * Defines the structure of a float-based positioned line.
 */
struct kmz_line_f_t {
    KmzPointF start;
    KmzPointF end;
};
typedef struct kmz_line_f_t KmzLineF;

/**
 * Defines the structure of a float-based positioned polygon.
 */
struct kmz_polygon_f_t {
    KmzBool closed;
    size_t count;
    KmzPointF * points;
};
typedef struct kmz_polygon_f_t KmzPolygonF;

/**
 * Defines the structure of a float-based positioned circle.
 */
struct kmz_circle_f_t {
    KmzPointF center;
    float radius;
};
typedef struct kmz_circle_f_t KmzCircleF;

// endregion;



// region Geometry Ctors:

#define kmz_size(w, h) ((KmzSize){w,h})

#define kmz_sizef(w, h) ((KmzSizeF){w,h})

#define kmz_point(x, y) ((KmzPoint){x,y})

#define kmz_pointf(x, y) ((KmzPointF){x,y})

#define kmz_rectangle(pos, size) ((KmzRectangle){pos,size})

#define kmz_rectanglef(pos, size) ((KmzRectangleF){pos,size})

#define kmz_line(start, end) ((KmzLine){start,end})

#define kmz_linef(start, end) ((KmzLineF){start,end})

#define kmz_polygon(count, points) ((KmzPolygon){KMZ_TRUE,count,points})

#define kmz_polygonf(count, points) ((KmzPolygonF){KMZ_TRUE,count,points})

#define kmz_polyline(count, points) ((KmzPolygon){KMZ_FALSE,count,points})

#define kmz_polylinef(count, points) ((KmzPolygonF){KMZ_FALSE,count,points})

#define kmz_circle(center, radius) ((KmzCircle){center,radius})

#define kmz_circlef(center, radius) ((KmzCircleF){center,radius})

// endregion;

#endif /* libkempozer_geometry_h */
