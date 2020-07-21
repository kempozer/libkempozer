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

#ifndef libkempozer_h
#define libkempozer_h

#include <stdint.h>

// region Numeric:

/**
 * Defines the potential truthy/falsey values available within kempozer.
 */
enum kmz_bool_e {
    KMZ_FALSE = 0,
    KMZ_TRUE = 1,
};
typedef enum kmz_bool_e KmzBool;

/**
 * Defines the potential return values of a drawing operation within kempozer.
 */
enum kmz_draw_status_e {
    KMZ_DRAW_OK = 0,
    KMZ_DRAW_ERR_OUT_OF_MEMORY = -1,
};
typedef enum kmz_draw_status_e KmzDrawStatus;

/**
 * Defines the potential return values of a GD image read/write operation within kempozer.
 */
enum kmz_gd_2x_image_file_status_e {
    KMZ_GD_OK = 0,
    KMZ_GD_ERR_READ_SIGNATURE = -1,
    KMZ_GD_ERR_WRITE_SIGNATURE = -2,
    KMZ_GD_ERR_READ_WIDTH = -3,
    KMZ_GD_ERR_READ_HEIGHT = -4,
    KMZ_GD_ERR_WRITE_WIDTH = -5,
    KMZ_GD_ERR_WRITE_HEIGHT = -6,
    KMZ_GD_ERR_READ_IS_TRUECOLOR = -7,
    KMZ_GD_ERR_WRITE_IS_TRUECOLOR = -8,
    KMZ_GD_ERR_READ_TRUECOLOR_TRANSPARENT = -9,
    KMZ_GD_ERR_WRITE_TRUECOLOR_TRANSPARENT = -10,
    KMZ_GD_ERR_READ_PALETTE_COUNT = -11,
    KMZ_GD_ERR_WRITE_PALETTE_COUNT = -12,
    KMZ_GD_ERR_READ_PALETTE_TRANSPARENT = -13,
    KMZ_GD_ERR_WRITE_PALETTE_TRANSPARENT = -14,
    KMZ_GD_ERR_READ_PALETTE_COLORS = -15,
    KMZ_GD_ERR_WRITE_PALETTE_COLORS = -16,
    KMZ_GD_ERR_READ_PIXELS = -17,
    KMZ_GD_ERR_WRITE_PIXELS = -18,
    KMZ_GD_ERR_INVALID_FILE_PTR = -19,
    KMZ_GD_ERR_INVALID_IMAGE_PTR = -20,
    KMZ_GD_ERR_UNSUPPORTED_OPERATION = -63,
    KMZ_GD_ERR_OUT_OF_MEMORY = -64,
    KMZ_GD_ERR_UNKNOWN = -1000,
};
typedef enum kmz_gd_2x_image_file_status_e KmzGd2xImageFileStatus;

/**
 * Defines the potentia return values of a bulk pixel operation within kempozer.
 */
enum kmz_pixel_operation_status_e {
    KMZ_PIXEL_OP_OK = 0,
    KMZ_PIXEL_OP_ERR_READ_INVALID_POS = -1,
    KMZ_PIXEL_OP_ERR_READ_INVALID_SIZE = -2,
    KMZ_PIXEL_OP_ERR_READ_INVALID_PTR = -3,
    KMZ_PIXEL_OP_ERR_WRITE_INVALID_POS = -4,
    KMZ_PIXEL_OP_ERR_WRITE_INVALID_SIZE = -5,
    KMZ_PIXEL_OP_ERR_WRITE_INVALID_PTR = -6,
    KMZ_PIXEL_OP_ERR_OUT_OF_MEMORY = -7,
    // Custom operation statuses MUST have a value lower than ERR_PIXEL_OP_USER_ERR.
    KMZ_PIXEL_OP_ERR_USER_ERR = -1024
};
typedef enum kmz_pixel_operation_status_e KmzPixelOperationStatus;

// endregion;

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

#define kmz_size(w, h) ((KmzSize){w,h})

#define kmz_sizef(w, h) ((KmzSizeF){w,h})

#define kmz_point(x, y) ((KmzPoint){x,y})

#define kmz_pointf(x, y) ((KmzPointF){x,y})

#define kmz_rectangle(pos, size) ((KmzRectangle){pos,size})

#define kmz_rectanglef(pos, size) ((KmzRectangleF){pos,size})

#define kmz_line(start, end) ((KmzLine){start,end})

#define kmz_linef(start, end) ((KmzLineF){start,end})

#define kmz_polygon(count, points) ((KmzPolygon){count,points})

#define kmz_polygonf(count, points) ((KmzPolygonF){count,points})

// endregion;

#endif /* libkempozer_h */
