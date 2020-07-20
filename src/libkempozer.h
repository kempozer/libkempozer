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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// region Numerics:
typedef float kmz_percent;
typedef uint8_t kmz_channel;

enum kmz_bool_e {
    KMZ_FALSE = 0,
    KMZ_TRUE = 1,
};
typedef enum kmz_bool_e KmzBool;

enum kmz_gd_2x_image_file_status_e {
    OK = 0,
    ERR_READ_SIGNATURE = -1,
    ERR_WRITE_SIGNATURE = -2,
    ERR_READ_WIDTH = -3,
    ERR_READ_HEIGHT = -4,
    ERR_WRITE_WIDTH = -5,
    ERR_WRITE_HEIGHT = -6,
    ERR_READ_IS_TRUECOLOR = -7,
    ERR_WRITE_IS_TRUECOLOR = -8,
    ERR_READ_TRUECOLOR_TRANSPARENT = -9,
    ERR_WRITE_TRUECOLOR_TRANSPARENT = -10,
    ERR_READ_PALETTE_COUNT = -11,
    ERR_WRITE_PALETTE_COUNT = -12,
    ERR_READ_PALETTE_TRANSPARENT = -13,
    ERR_WRITE_PALETTE_TRANSPARENT = -14,
    ERR_READ_PALETTE_COLORS = -15,
    ERR_WRITE_PALETTE_COLORS = -16,
    ERR_READ_PIXELS = -17,
    ERR_WRITE_PIXELS = -18,
    ERR_INVALID_FILE_PTR = -19,
    ERR_INVALID_IMAGE_PTR = -20,
    ERR_UNSUPPORTED_OPERATION = -63,
    ERR_OUT_OF_MEMORY = -64,
    ERR_UNKNOWN = -1000
    
};
typedef enum kmz_gd_2x_image_file_status_e KmzGd2xImageFileStatus;

/**
 * Defines the standard pixel operation status codes as returned by block pixel operations.
 */
enum kmz_pixel_operation_status_e {
    // Standard statuses
    PIXEL_OP_OK = 0,
    ERR_PIXEL_OP_READ_INVALID_POS = -1,
    ERR_PIXEL_OP_READ_INVALID_SIZE = -2,
    ERR_PIXEL_OP_READ_INVALID_PTR = -3,
    ERR_PIXEL_OP_WRITE_INVALID_POS = -4,
    ERR_PIXEL_OP_WRITE_INVALID_SIZE = -5,
    ERR_PIXEL_OP_WRITE_INVALID_PTR = -6,
    ERR_PIXEL_OP_OUT_OF_MEMORY = -7,
    // Custom operation statuses MUST have a value lower than ERR_PIXEL_OP_USER_ERR.
    ERR_PIXEL_OP_USER_ERR = -1024
};
typedef enum kmz_pixel_operation_status_e KmzPixelOperationStatus;
// endregion;

// region Geometry:
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
    size_t count;
    KmzPoint * points;
};
typedef struct kmz_polygon_t KmzPolygon;

struct kmz_polygon_f_t {
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
// endregion;

// region Colors:
typedef uint32_t kmz_color_32;

struct kmz_argb_color_t {
    kmz_channel a, r, g, b;
};
typedef struct kmz_argb_color_t KmzArgbColor;

struct kmz_ahsl_color_t {
    kmz_channel a;
    kmz_percent h, s, l;
};
typedef struct kmz_ahsl_color_t KmzAhslColor;

/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_color_32(const kmz_color_32 color);

/**
 * Creates a new ARGB color from the provided values.
 */
KmzArgbColor KmzArgbColor__from_channels(const kmz_channel a, const kmz_channel r, const kmz_channel g, const kmz_channel b);

/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_ahsl_color(const KmzAhslColor color);

/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_hex(const char * const restrict color);

/**
 * Determines if the provided ARGB colors are equal.
 */
const KmzBool KmzArgbColor__equal_to(const KmzArgbColor me, const KmzArgbColor other);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_color_32(const kmz_color_32 color);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_channels(const kmz_channel a, const kmz_percent h, const kmz_percent s, const kmz_percent l);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_argb_color(const KmzArgbColor color);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_hex(const char * const restrict color);

/**
 * Determines if the provided AHSL colors are equal.
 */
const KmzBool KmzAhslColor__equal_to(const KmzAhslColor me, const KmzAhslColor other);

/**
 * Creates a new color 32 color from the provided value.
 */
const kmz_color_32 kmz_color_32__from_argb_color(const KmzArgbColor color);

/**
 * Creates a new color 32 color from the provided value.
 */
const kmz_color_32 kmz_color_32__from_ahsl_color(const KmzAhslColor color);

/**
 * Creates a new color 32 color from the provided value.
 */
const kmz_color_32 kmz_color_32__from_hex(const char * const restrict color);

/**
 * Determines if the provided color 32 colors are equal.
 */
const KmzBool kmz_color_32__equal_to(const kmz_color_32 me, const kmz_color_32 other);
// endregion;

// region Core:
/**
 * Defines a constant pointer to a generic image.
 */
typedef void * const restrict kmz_image_ptr_const;

/**
 * Defines a pointer to a generic image.
 */
typedef void * restrict kmz_image_ptr;

/**
 * Defines a pointer to a generic argument.
 */
typedef const void * const restrict kmz_arg_ptr;

/**
 * Defines the structure of a type for image-like objects.
 */
struct kmz_image_type_t {
    // region Type:
    /**
     * Allocates an uninitialized image of this type.
     */
    void * const (* const _new)(void);
    /**
     * Initializes an uninitialized image of this type.
     */
    void (* const _ctor)(kmz_image_ptr_const, kmz_arg_ptr);
    /**
     * Destroys an initialized image of this type.
     */
    void (* const _dtor)(kmz_image_ptr_const);
    // endregion;
    
    // region Pure Virtuals:
    /**
     * Gets the dimensions of this image.
     */
    const KmzSize (* const dimen)(const kmz_image_ptr_const);
    /**
     * Gets an ARGB value at the given coordinates from this image.
     */
    const kmz_color_32 (* const argb_at)(const kmz_image_ptr_const, const KmzPoint);
    /**
     * Sets an ARGB value at the given coordinates in this image.
     */
    void (* const set_argb_at)(kmz_image_ptr_const, const KmzPoint, const kmz_color_32);
    /**
     * Gets whether or not the coordinates fall within this image.
     */
    const KmzBool (* const is_valid)(const kmz_image_ptr_const, const KmzPoint);
    // endregion;
    
    // region Virtuals:
    /**
     * Reads a block of ARGB values from this image.
     */
    const KmzPixelOperationStatus (* const read_argb_block)(const kmz_image_ptr_const, const KmzRectangle, kmz_color_32 * const);
    /**
     * Writes a block of ARGB values to this image.
     */
    const KmzPixelOperationStatus (* const write_argb_block)(kmz_image_ptr_const, const KmzRectangle, const kmz_color_32 * const);
    // endregion;
};
typedef struct kmz_image_type_t KmzImageType;

/**
 * Defines the structure of an image-like object reference, including its virtual table and me (this) pointer.
 */
struct kmz_image_t;
typedef struct kmz_image_t KmzImage, * const restrict KmzImagePtr;

/**
 * Defines the structure of an image-like-based matrix object.
 */
struct kmz_matrix_t;
typedef struct kmz_matrix_t KmzMatrix;

typedef const kmz_color_32 (*KmzFilter)(kmz_arg_ptr, KmzMatrix * const restrict);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * const KmzMatrix__new_from_buffer(kmz_color_32 * const restrict buffer, const KmzSize image_dimen, const KmzPoint pos, const size_t size);

/**
 * Gets the size of the matrix.
 */
const size_t KmzMatrix__size(const KmzMatrix * const restrict me);

/**
 * Gets the half size of the matrix.
 */
const size_t KmzMatrix__hsize(const KmzMatrix * const restrict me);

/**
 * Gets the position of the matrix.
 */
const KmzPoint KmzMatrix__pos(const KmzMatrix * const restrict me);

/**
 * Sets the position of the matrix.
 */
void KmzMatrix__set_pos(KmzMatrix * const restrict me, const KmzPoint pos);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
const kmz_color_32 KmzMatrix__argb_at(const KmzMatrix * const restrict me, const KmzPoint point);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color);

/**
 * Returns a new image of the given type.
 */
const KmzImagePtr KmzImage__new(const KmzImageType * const restrict type, const void * const restrict argv);

/**
 * Frees the image and all of its resources.
 */
void KmzImage__free(KmzImagePtr me);

/**
 * Returns the type pointed to by the image.
 */
const KmzImageType * const KmzImage__type(const KmzImagePtr me);

/**
 * Gets the dimensions of the image.
 */
const KmzSize KmzImage__dimen(const KmzImagePtr me);

/**
 * Gets a color from within the image.
 */
const kmz_color_32 KmzImage__argb_at(const KmzImagePtr me, const KmzPoint point);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(const KmzImagePtr me, const KmzPoint point, const kmz_color_32 color);

/**
 * Reads a block of colors within the image.
 */
const KmzPixelOperationStatus KmzImage__read_argb_block(const KmzImagePtr me, const KmzRectangle area, kmz_color_32 * const restrict buffer);

/**
 * Writes a block of colors to the image.
 */
const KmzPixelOperationStatus KmzImage__write_argb_block(const KmzImagePtr me, const KmzRectangle area, const kmz_color_32 * const restrict buffer);

/**
 * Determines if the point is a valid coordinate within the image.
 */
const KmzBool KmzImage__is_valid(const KmzImagePtr me, const KmzPoint point);

/**
 * Applies a matrix filter function to the image referenced.
 */
KmzPixelOperationStatus KmzImage__apply_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                               const size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
KmzPixelOperationStatus KmzImage__apply_buffered_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                                        const size_t m_size, const KmzImagePtr buffer);
// endregion;

// region GD 2x:
#define KMZ_GD_2x_IMAGE_FILE_TRUECOLOR 0xFFFE

#define KMZ_GD_2x_IMAGE_FILE_PALETTE 0xFFFF

#define KMZ_GD_2x_IMAGE_NO_TRANSPARENT 0xFFFFFFFF

/**
 * Represents the signature portion of a GD image.
 */
struct kmz_gd_2x_image_file_signature_header_t {
    uint16_t type;
    KmzSize dimen;
};
typedef struct kmz_gd_2x_image_file_signature_header_t KmzGd2xImageFileSignatureHeader;

/**
 * Represents the header of a truecolor image.
 */
struct kmz_gd_2x_image_file_truecolor_header_t {
    kmz_color_32 transparent;
};
typedef struct kmz_gd_2x_image_file_truecolor_header_t KmzGd2xImageFileTruecolorHeader;

/**
 * Represents the header of a palette image.
 */
struct kmz_gd_2x_image_file_palette_header_t {
    uint16_t count;
    kmz_color_32 transparent;
    kmz_color_32 colors[256];
};
typedef struct kmz_gd_2x_image_file_palette_header_t KmzGd2xImageFilePaletteHeader;

/**
 * Represents the chunk of the header that contains color information.
 */
struct kmz_gd_2x_image_file_color_header_t {
    uint8_t is_truecolor;
    union {
        KmzGd2xImageFileTruecolorHeader truecolor;
        KmzGd2xImageFilePaletteHeader palette;
    } value;
};
typedef struct kmz_gd_2x_image_file_color_header_t KmzGd2xImageFileColorHeader;

/**
 * Represents a fully composed header.
 */
struct kmz_gd_2x_image_file_header_t {
    KmzGd2xImageFileSignatureHeader signature;
    KmzGd2xImageFileColorHeader color;
};
typedef struct kmz_gd_2x_image_file_header_t KmzGd2xImageFileHeader;

/**
 * Represents a fully composed image file loaded into RAM.
 */
struct kmz_gd_2x_image_file_t {
    KmzGd2xImageFileHeader header;
    union {
        kmz_color_32 * restrict truecolor;
        uint8_t * restrict palette;
    } pixels;
};
typedef struct kmz_gd_2x_image_file_t KmzGd2xImageFile;

/**
 * Reads a GD file with a 2x header from the given file pointer.
 */
const KmzGd2xImageFileStatus kmz_read_gd_2x_image_file(FILE * const restrict f, KmzGd2xImageFile * const restrict o);

/**
 * Writes a GD file with a 2x header to the given file pointer.
 */
const KmzGd2xImageFileStatus kmz_write_gd_2x_image_file(FILE * const restrict f, const KmzGd2xImageFile * const restrict i);

/**
 * Returns a plain-english message for the given file status.
 */
const char * kmz_status_msg(const KmzGd2xImageFileStatus status);

/**
 * Returns a plain-english message for the given file status with the given file error appended to it.
 */
const char * kmz_status_msg_with_err_code(const KmzGd2xImageFileStatus status, const int error);

/**
 * Returns a new image from the given GD 2x file.
 */
KmzImagePtr KmzImage__new_from_gd_2x(const KmzGd2xImageFile * const restrict image);
// endregion;

// region Image:
/**
 * Returns a new image from the given buffer.
 */
KmzImagePtr KmzImage__new_from_buffer(const KmzSize dimen, kmz_color_32 * const restrict buffer, const KmzBool copy_source);

/**
 * Provides a general purpose ARGB-based image.
 */
extern const KmzImageType kmz_image;
// endregion;

// region Drawing:
/**
 * Defines the possible values returned by a drawing command.
 */
enum kmz_draw_status_e {
    KMZ_DRAW_OK = 0,
    KMZ_DRAW_ERR_OUT_OF_MEMORY = -1,
};
typedef enum kmz_draw_status_e KmzDrawStatus;

/**
 * Defines an object that can be used to fill in shapes.
 */
struct kmz_brush_t {
    kmz_color_32 color;
};
typedef struct kmz_brush_t KmzBrush;

/**
 * Defines an object that can be used to draw lines.
 */
struct kmz_pen_t {
    KmzBool antialias;
    KmzBrush fill;
    kmz_color_32 color;
    size_t width;
};
typedef struct kmz_pen_t KmzPen;

/**
 * Defines an object that can be used to draw lines with floating point coordinates.
 */
struct kmz_pen_f_t {
    KmzBool antialias;
    KmzBrush fill;
    kmz_color_32 color;
    float width;
};
typedef struct kmz_pen_f_t KmzPenF;

/**
 * Defines an opaque object that can be used to paint onto an internal buffer.
 */
struct kmz_painter_t;
typedef struct kmz_painter_t KmzPainter;

/**
 * Creates a new KmzPainter for use with painting.
 */
KmzPainter * const KmzPainter__new(void);

/**
 * Frees the KmzPainter and all of its internal contents.
 */
void KmzPainter__free(KmzPainter * const me);

/**
 * Sets the fill brush for this painter.
 */
void KmzPainter__set_brush(KmzPainter * const me, const KmzBrush brush);

/**
 * Sets the pen for this painter and marks it as non-floating point line drawing.
 */
void KmzPainter__set_pen(KmzPainter * const me, const KmzPen pen);

/**
 * Sets the pen for this painter and marks it as floating point line drawing.
 */
void KmzPainter__set_penf(KmzPainter * const me, const KmzPenF pen);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_line(KmzPainter * const restrict me, const KmzLine line);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_linef(KmzPainter * const restrict me, const KmzLineF line);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_point(KmzPainter * const restrict me, const KmzPoint point);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_pointf(KmzPainter * const restrict me, const KmzPointF point);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_polygon(KmzPainter * const restrict me, const KmzPolygon polygon);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_polygonf(KmzPainter * const restrict me, const KmzPolygonF polygon);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_rectangle(KmzPainter * const restrict me, const KmzRectangle rectangle);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_rectanglef(KmzPainter * const restrict me, const KmzRectangleF rectangle);

/**
 * Paints the painter back to the image-like. Anything that overflows out of the image will be discarded.
 */
const void KmzPainter__paint(KmzPainter * const restrict me, KmzPoint pos, KmzImagePtr target);

/**
 * Undoes the most recent draw operation if possible. KMZ_TRUE is returned if the undo is successful, otherwise KMZ_FALSE is returned.
 */
const KmzBool KmzPainter__undo(KmzPainter * const restrict me);

/**
 * Redoes the most recent draw operation if possible. KMZ_TRUE is returned if the redo is successful, otherwise KMZ_FALSE is returned.
 */
const KmzBool KmzPainter__redo(KmzPainter * const restrict me);
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
static const KmzPolygon KmzPolygon__ZERO = {.count=0, .points=NULL};
static const KmzPolygonF KmzPolygonF__ZERO = {.count=0, .points=NULL};
static const KmzArgbColor KmzArgbColor__ALICE_BLUE = {.a=0, .r=0xF0, .g=0xF8, .b=0xFF},
                          KmzArgbColor__ANTIQUE_WHITE = {.a=0, .r=0xFA, .g=0xEB, .b=0xD7},
                          KmzArgbColor__AQUA = {.a=0, .r=0x00, .g=0xFF, .b=0xFF},
                          KmzArgbColor__AQUAMARINE = {.a=0, .r=0x7F, .g=0xFF, .b=0xD4},
                          KmzArgbColor__AZURE = {.a=0, .r=0xF0, .g=0xFF, .b=0xFF},
                          KmzArgbColor__BEIGE = {.a=0, .r=0xF5, .g=0xF5, .b=0xDC},
                          KmzArgbColor__BISQUE = {.a=0, .r=0xFF, .g=0xE4, .b=0xC4},
                          KmzArgbColor__BLACK = {.a=0, .r=0x00, .g=0x00, .b=0x00},
                          KmzArgbColor__BLANCHED_ALMOND = {.a=0, .r=0xFF, .g=0xEB, .b=0xCD},
                          KmzArgbColor__BLUE = {.a=0, .r=0x00, .g=0x00, .b=0xFF},
                          KmzArgbColor__BLUE_VIOLET = {.a=0, .r=0x8A, .g=0x2B, .b=0xE2},
                          KmzArgbColor__BROWN = {.a=0, .r=0xA5, .g=0x2A, .b=0x2A},
                          KmzArgbColor__BURLY_WOOD = {.a=0, .r=0xDE, .g=0xB8, .b=0x87},
                          KmzArgbColor__CADET_BLUE = {.a=0, .r=0x5F, .g=0x9E, .b=0xA0},
                          KmzArgbColor__CHARTREUSE = {.a=0, .r=0x7F, .g=0xFF, .b=0x00},
                          KmzArgbColor__CHOCOLATE = {.a=0, .r=0xD2, .g=0x69, .b=0x1E},
                          KmzArgbColor__CORAL = {.a=0, .r=0xFF, .g=0x7F, .b=0x50},
                          KmzArgbColor__CORNFLOWER_BLUE = {.a=0, .r=0x64, .g=0x95, .b=0xED},
                          KmzArgbColor__CORNSILK = {.a=0, .r=0xFF, .g=0xF8, .b=0xDC},
                          KmzArgbColor__CRIMSON = {.a=0, .r=0xDC, .g=0x14, .b=0x3C},
                          KmzArgbColor__CYAN = {.a=0, .r=0x00, .g=0xFF, .b=0xFF},
                          KmzArgbColor__DAR_KBLUE = {.a=0, .r=0x00, .g=0x00, .b=0x8B},
                          KmzArgbColor__DARK_CYAN = {.a=0, .r=0x00, .g=0x8B, .b=0x8B},
                          KmzArgbColor__DARK_GOLDENROD = {.a=0, .r=0xB8, .g=0x86, .b=0x0B},
                          KmzArgbColor__DARK_GRAY = {.a=0, .r=0xA9, .g=0xA9, .b=0xA9},
                          KmzArgbColor__DARK_GREEN = {.a=0, .r=0x00, .g=0x64, .b=0x00},
                          KmzArgbColor__DARK_KHAKI = {.a=0, .r=0xBD, .g=0xB7, .b=0x6B},
                          KmzArgbColor__DARK_MAGENTA = {.a=0, .r=0x8B, .g=0x00, .b=0x8B},
                          KmzArgbColor__DARK_OLIVE_GREEN = {.a=0, .r=0x55, .g=0x6B, .b=0x2F},
                          KmzArgbColor__DARK_ORANGE = {.a=0, .r=0xFF, .g=0x8C, .b=0x00},
                          KmzArgbColor__DARK_ORCHID = {.a=0, .r=0x99, .g=0x32, .b=0xCC},
                          KmzArgbColor__DARK_RED = {.a=0, .r=0x8B, .g=0x00, .b=0x00},
                          KmzArgbColor__DARK_SALMON = {.a=0, .r=0xE9, .g=0x96, .b=0x7A},
                          KmzArgbColor__DARK_SEA_GREEN = {.a=0, .r=0x8F, .g=0xBC, .b=0x8B},
                          KmzArgbColor__DARK_SLATE_BLUE = {.a=0, .r=0x48, .g=0x3D, .b=0x8B},
                          KmzArgbColor__DARK_SLATE_GRAY = {.a=0, .r=0x2F, .g=0x4F, .b=0x4F},
                          KmzArgbColor__DARK_TURQUOISE = {.a=0, .r=0x00, .g=0xCE, .b=0xD1},
                          KmzArgbColor__DARK_VIOLET = {.a=0, .r=0x94, .g=0x00, .b=0xD3},
                          KmzArgbColor__DEEP_PINK = {.a=0, .r=0xFF, .g=0x14, .b=0x93},
                          KmzArgbColor__DEEP_SKY_BLUE = {.a=0, .r=0x00, .g=0xBF, .b=0xFF},
                          KmzArgbColor__DIM_GRAY = {.a=0, .r=0x69, .g=0x69, .b=0x69},
                          KmzArgbColor__DODGER_BLUE = {.a=0, .r=0x1E, .g=0x90, .b=0xFF},
                          KmzArgbColor__FIREBRICK = {.a=0, .r=0xB2, .g=0x22, .b=0x22},
                          KmzArgbColor__FLORAL_WHITE = {.a=0, .r=0xFF, .g=0xFA, .b=0xF0},
                          KmzArgbColor__FOREST_GREEN = {.a=0, .r=0x22, .g=0x8B, .b=0x22},
                          KmzArgbColor__FUCHSIA = {.a=0, .r=0xFF, .g=0x00, .b=0xFF},
                          KmzArgbColor__GAINSBORO = {.a=0, .r=0xDC, .g=0xDC, .b=0xDC},
                          KmzArgbColor__GHOST_WHITE = {.a=0, .r=0xF8, .g=0xF8, .b=0xFF},
                          KmzArgbColor__GOLD = {.a=0, .r=0xFF, .g=0xD7, .b=0x00},
                          KmzArgbColor__GOLDENROD = {.a=0, .r=0xDA, .g=0xA5, .b=0x20},
                          KmzArgbColor__GRAY = {.a=0, .r=0x80, .g=0x80, .b=0x80},
                          KmzArgbColor__GREEN = {.a=0, .r=0x00, .g=0x80, .b=0x00},
                          KmzArgbColor__GREEN_YELLOW = {.a=0, .r=0xAD, .g=0xFF, .b=0x2F},
                          KmzArgbColor__HONEYDEW = {.a=0, .r=0xF0, .g=0xFF, .b=0xF0},
                          KmzArgbColor__HOT_PINK = {.a=0, .r=0xFF, .g=0x69, .b=0xB4},
                          KmzArgbColor__INDIAN_RED = {.a=0, .r=0xCD, .g=0x5C, .b=0x5C},
                          KmzArgbColor__INDIGO = {.a=0, .r=0x4B, .g=0x00, .b=0x82},
                          KmzArgbColor__IVORY = {.a=0, .r=0xFF, .g=0xFF, .b=0xF0},
                          KmzArgbColor__KHAKI = {.a=0, .r=0xF0, .g=0xE6, .b=0x8C},
                          KmzArgbColor__LAVENDER = {.a=0, .r=0xE6, .g=0xE6, .b=0xFA},
                          KmzArgbColor__LAVENDER_BLUSH = {.a=0, .r=0xFF, .g=0xF0, .b=0xF5},
                          KmzArgbColor__LAWN_GREEN = {.a=0, .r=0x7C, .g=0xFC, .b=0x00},
                          KmzArgbColor__LEMON_CHIFFON = {.a=0, .r=0xFF, .g=0xFA, .b=0xCD},
                          KmzArgbColor__LIGHT_BLUE = {.a=0, .r=0xAD, .g=0xD8, .b=0xE6},
                          KmzArgbColor__LIGHT_CORAL = {.a=0, .r=0xF0, .g=0x80, .b=0x80},
                          KmzArgbColor__LIGHT_CYAN = {.a=0, .r=0xE0, .g=0xFF, .b=0xFF},
                          KmzArgbColor__LIGHT_GOLDENROD_YELLOW = {.a=0, .r=0xFA, .g=0xFA, .b=0xD2},
                          KmzArgbColor__LIGHT_GRAY = {.a=0, .r=0xD3, .g=0xD3, .b=0xD3},
                          KmzArgbColor__LIGHT_GREEN = {.a=0, .r=0x90, .g=0xEE, .b=0x90},
                          KmzArgbColor__LIGHT_PINK = {.a=0, .r=0xFF, .g=0xB6, .b=0xC1},
                          KmzArgbColor__LIGHT_SALMON = {.a=0, .r=0xFF, .g=0xA0, .b=0x7A},
                          KmzArgbColor__LIGHT_SEA_GREEN = {.a=0, .r=0x20, .g=0xB2, .b=0xAA},
                          KmzArgbColor__LIGHT_SKY_BLUE = {.a=0, .r=0x87, .g=0xCE, .b=0xFA},
                          KmzArgbColor__LIGHT_SLATE_GRAY = {.a=0, .r=0x77, .g=0x88, .b=0x99},
                          KmzArgbColor__LIGHT_STEEL_BLUE = {.a=0, .r=0xB0, .g=0xC4, .b=0xDE},
                          KmzArgbColor__LIGHT_YELLOW = {.a=0, .r=0xFF, .g=0xFF, .b=0xE0},
                          KmzArgbColor__LIME = {.a=0, .r=0x00, .g=0xFF, .b=0x00},
                          KmzArgbColor__LIME_GREEN = {.a=0, .r=0x32, .g=0xCD, .b=0x32},
                          KmzArgbColor__LINEN = {.a=0, .r=0xFA, .g=0xF0, .b=0xE6},
                          KmzArgbColor__MAGENTA = {.a=0, .r=0xFF, .g=0x00, .b=0xFF},
                          KmzArgbColor__MAROON = {.a=0, .r=0x80, .g=0x00, .b=0x00},
                          KmzArgbColor__MEDIUM_AQUAMARINE = {.a=0, .r=0x66, .g=0xCD, .b=0xAA},
                          KmzArgbColor__MEDIUM_BLUE = {.a=0, .r=0x00, .g=0x00, .b=0xCD},
                          KmzArgbColor__MEDIUM_ORCHID = {.a=0, .r=0xBA, .g=0x55, .b=0xD3},
                          KmzArgbColor__MEDIUM_PURPLE = {.a=0, .r=0x93, .g=0x70, .b=0xDB},
                          KmzArgbColor__MEDIUM_SEA_GREEN = {.a=0, .r=0x3C, .g=0xB3, .b=0x71},
                          KmzArgbColor__MEDIUM_SLATE_BLUE = {.a=0, .r=0x7B, .g=0x68, .b=0xEE},
                          KmzArgbColor__MEDIUM_SPRING_GREEN = {.a=0, .r=0x00, .g=0xFA, .b=0x9A},
                          KmzArgbColor__MEDIUM_TURQUOISE = {.a=0, .r=0x48, .g=0xD1, .b=0xCC},
                          KmzArgbColor__MEDIUM_VIOLET_RED = {.a=0, .r=0xC7, .g=0x15, .b=0x85},
                          KmzArgbColor__MIDNIGHT_BLUE = {.a=0, .r=0x19, .g=0x19, .b=0x70},
                          KmzArgbColor__MINT_CREAM = {.a=0, .r=0xF5, .g=0xFF, .b=0xFA},
                          KmzArgbColor__MISTY_ROSE = {.a=0, .r=0xFF, .g=0xE4, .b=0xE1},
                          KmzArgbColor__MOCCASIN = {.a=0, .r=0xFF, .g=0xE4, .b=0xB5},
                          KmzArgbColor__NAVAJO_WHITE = {.a=0, .r=0xFF, .g=0xDE, .b=0xAD},
                          KmzArgbColor__NAVY = {.a=0, .r=0x00, .g=0x00, .b=0x80},
                          KmzArgbColor__OLD_LACE = {.a=0, .r=0xFD, .g=0xF5, .b=0xE6},
                          KmzArgbColor__OLIVE = {.a=0, .r=0x80, .g=0x80, .b=0x00},
                          KmzArgbColor__OLIVE_DRAB = {.a=0, .r=0x6B, .g=0x8E, .b=0x23},
                          KmzArgbColor__ORANGE = {.a=0, .r=0xFF, .g=0xA5, .b=0x00},
                          KmzArgbColor__ORANGE_RED = {.a=0, .r=0xFF, .g=0x45, .b=0x00},
                          KmzArgbColor__ORCHID = {.a=0, .r=0xDA, .g=0x70, .b=0xD6},
                          KmzArgbColor__PALE_GOLDENROD = {.a=0, .r=0xEE, .g=0xE8, .b=0xAA},
                          KmzArgbColor__PALE_GREEN = {.a=0, .r=0x98, .g=0xFB, .b=0x98},
                          KmzArgbColor__PALE_TURQUOISE = {.a=0, .r=0xAF, .g=0xEE, .b=0xEE},
                          KmzArgbColor__PALE_VIOLET_RED = {.a=0, .r=0xDB, .g=0x70, .b=0x93},
                          KmzArgbColor__PAPAYA_WHIP = {.a=0, .r=0xFF, .g=0xEF, .b=0xD5},
                          KmzArgbColor__PEACH_PUFF = {.a=0, .r=0xFF, .g=0xDA, .b=0xB9},
                          KmzArgbColor__PERU = {.a=0, .r=0xCD, .g=0x85, .b=0x3F},
                          KmzArgbColor__PINK = {.a=0, .r=0xFF, .g=0xC0, .b=0xCB},
                          KmzArgbColor__PLUM = {.a=0, .r=0xDD, .g=0xA0, .b=0xDD},
                          KmzArgbColor__POWDER_BLUE = {.a=0, .r=0xB0, .g=0xE0, .b=0xE6},
                          KmzArgbColor__PURPLE = {.a=0, .r=0x80, .g=0x00, .b=0x80},
                          KmzArgbColor__RED = {.a=0, .r=0xFF, .g=0x00, .b=0x00},
                          KmzArgbColor__ROSY_BROWN = {.a=0, .r=0xBC, .g=0x8F, .b=0x8F},
                          KmzArgbColor__ROYAL_BLUE = {.a=0, .r=0x41, .g=0x69, .b=0xE1},
                          KmzArgbColor__SADDLE_BROWN = {.a=0, .r=0x8B, .g=0x45, .b=0x13},
                          KmzArgbColor__SALMON = {.a=0, .r=0xFA, .g=0x80, .b=0x72},
                          KmzArgbColor__SANDY_BROWN = {.a=0, .r=0xF4, .g=0xA4, .b=0x60},
                          KmzArgbColor__SEA_GREEN = {.a=0, .r=0x2E, .g=0x8B, .b=0x57},
                          KmzArgbColor__SEA_SHELL = {.a=0, .r=0xFF, .g=0xF5, .b=0xEE},
                          KmzArgbColor__SIENNA = {.a=0, .r=0xA0, .g=0x52, .b=0x2D},
                          KmzArgbColor__SILVER = {.a=0, .r=0xC0, .g=0xC0, .b=0xC0},
                          KmzArgbColor__SKY_BLUE = {.a=0, .r=0x87, .g=0xCE, .b=0xEB},
                          KmzArgbColor__SLATE_BLUE = {.a=0, .r=0x6A, .g=0x5A, .b=0xCD},
                          KmzArgbColor__SLATE_GRAY = {.a=0, .r=0x70, .g=0x80, .b=0x90},
                          KmzArgbColor__SNOW = {.a=0, .r=0xFF, .g=0xFA, .b=0xFA},
                          KmzArgbColor__SPRING_GREEN = {.a=0, .r=0x00, .g=0xFF, .b=0x7F},
                          KmzArgbColor__STEEL_BLUE = {.a=0, .r=0x46, .g=0x82, .b=0xB4},
                          KmzArgbColor__TAN = {.a=0, .r=0xD2, .g=0xB4, .b=0x8C},
                          KmzArgbColor__TEAL = {.a=0, .r=0x00, .g=0x80, .b=0x80},
                          KmzArgbColor__THISTLE = {.a=0, .r=0xD8, .g=0xBF, .b=0xD8},
                          KmzArgbColor__TOMATO = {.a=0, .r=0xFF, .g=0x63, .b=0x47},
                          KmzArgbColor__TURQUOISE = {.a=0, .r=0x40, .g=0xE0, .b=0xD0},
                          KmzArgbColor__VIOLET = {.a=0, .r=0xEE, .g=0x82, .b=0xEE},
                          KmzArgbColor__WHEAT = {.a=0, .r=0xF5, .g=0xDE, .b=0xB3},
                          KmzArgbColor__WHITE = {.a=0, .r=0xFF, .g=0xFF, .b=0xFF},
                          KmzArgbColor__WHITE_SMOKE = {.a=0, .r=0xF5, .g=0xF5, .b=0xF5},
                          KmzArgbColor__YELLOW = {.a=0, .r=0xFF, .g=0xFF, .b=0x00},
                          KmzArgbColor__YELLOW_GREEN = {.a=0, .r=0x9A, .g=0xCD, .b=0x32};
static const KmzBrush KmzBrush__TRANSPARENT = {.color=0x7F000000};
static const KmzPen KmzPen__TRANSPARENT = {.color=0x7F000000};
static const KmzPenF KmzPenF__TRANSPARENT = {.color=0x7F000000};
// endregion;

// region Helpers:
#define kmz_clamp(val, min, max) (val < min ? min : (val > max ? max : val))

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

#endif /* kmz_lib_h */
