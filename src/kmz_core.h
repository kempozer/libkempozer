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

#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"

// region Types:
typedef void * const restrict const_kmz_image_ptr;
typedef void * restrict kmz_image_ptr;
typedef const void * const restrict kmz_arg_ptr;

enum kmz_pixel_operation_status_e {
    PIXEL_OP_OK = 0,
    ERR_PIXEL_OP_READ_INVALID_POS = -1,
    ERR_PIXEL_OP_READ_INVALID_SIZE = -2,
    ERR_PIXEL_OP_READ_INVALID_PTR = -3,
    ERR_PIXEL_OP_WRITE_INVALID_POS = -4,
    ERR_PIXEL_OP_WRITE_INVALID_SIZE = -5,
    ERR_PIXEL_OP_WRITE_INVALID_PTR = -6,
    // Anything returned that is beyond ERR_PIXEL_OP_USER_ERR is implementation-specific errors.
    ERR_PIXEL_OP_USER_ERR = -1024
};
typedef enum kmz_pixel_operation_status_e KmzPixelOperationStatus;

struct kmz_matrix_t;

struct kmz_image_like_vtab_t {
    const KmzSize (* const get_dimen)(const const_kmz_image_ptr);
    const kmz_color_32 (* const get_argb_at)(const const_kmz_image_ptr, const KmzPoint);
    void (* const set_argb_at)(const_kmz_image_ptr, const KmzPoint, const kmz_color_32);
    const KmzPixelOperationStatus (* const read_argb_block)(const const_kmz_image_ptr, const KmzRectangle, kmz_color_32 * const);
    const KmzPixelOperationStatus (* const write_argb_block)(const_kmz_image_ptr, const KmzRectangle, const kmz_color_32 * const);
    const KmzBool (* const is_valid)(const const_kmz_image_ptr, const KmzPoint);
};
typedef struct kmz_image_like_vtab_t KmzImageLikeVTab;

struct kmz_image_like_t {
    const KmzImageLikeVTab * _vt;
    kmz_image_ptr _me;
};
typedef struct kmz_image_like_t KmzImageLike;

struct kmz_image_t {
    /**
     * @const
     */
    KmzSize dimen;
    /**
     * @const
     */
    size_t len;
    /**
     * @const
     */
    kmz_color_32 * pixels;
};
typedef struct kmz_image_t KmzImage;

struct kmz_image_matrix_t {
    /**
     * @const
     */
    size_t size;
    /**
     * @const
     */
    size_t hsize;
    KmzPoint pos;
    /**
     * @const
     */
    KmzImage * image;
};
typedef struct kmz_image_matrix_t KmzImageMatrix;

struct kmz_matrix_t {
    /**
     * @const
     */
    size_t size;
    /**
     * @const
     */
    size_t hsize;
    KmzPoint pos;
    /**
     * @const
     */
    KmzImageLike image;
    /**
     * @const
     */
    KmzSize image_dimen;
};
typedef struct kmz_matrix_t KmzMatrix;

typedef const kmz_color_32 (*KmzFilter)(kmz_arg_ptr, KmzMatrix * const restrict);

typedef const kmz_color_32 (*KmzImageFilter)(kmz_arg_ptr, KmzImageMatrix * const restrict);
// endregion;

// region Functions:

/**
 * Creates a new KmzImage using the given GD 2x image file.
 */
KmzImage * const KmzImage__new_from_gd_2x(const KmzGd2xImageFile * const restrict image);

/**
 * Creates a new KmzImage using the given color buffer.
 */
KmzImage * const KmzImage__new_from_buffer(const KmzSize dimen, const kmz_color_32 * const restrict pixels);

/**
 * Creates a new image-like for the given image.
 */
const KmzImageLike KmzImage__to_image_like(KmzImage * const restrict me);

/**
 * Gets a color from within the image.
 */
const kmz_color_32 KmzImage__get_argb_at(const KmzImage * const restrict me, const KmzPoint point);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(KmzImage * const restrict me, const KmzPoint point, const kmz_color_32 color);

/**
 * Reads a block of colors within the image.
 */
const KmzPixelOperationStatus KmzImage__read_argb_block(const KmzImage * const restrict me, const KmzRectangle area, kmz_color_32 * const restrict buffer);

/**
 * Writes a block of colors to the image.
 */
const KmzPixelOperationStatus KmzImage__write_argb_block(KmzImage * const restrict me, const KmzRectangle area, const kmz_color_32 * const restrict buffer);

/**
 * Determines if the point is a valid coordinate within the image.
 */
const KmzBool KmzImage__is_valid(const KmzImage * const restrict me, const KmzPoint point);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * const KmzMatrix__new_from_image_like(const KmzImageLike image, const KmzPoint point, const size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
const kmz_color_32 KmzMatrix__get_argb_at(const KmzMatrix * const restrict me, const KmzPoint point);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzImageMatrix * const KmzImageMatrix__new_from_image(KmzImage * const restrict image, const KmzPoint point, const size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
const kmz_color_32 KmzImageMatrix__get_argb_at(const KmzImageMatrix * const restrict me, const KmzPoint point);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzImageMatrix__set_argb_at(KmzImageMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color);

/**
 * Creates a new matrix of the given size.
 */
KmzImageMatrix * const KmzImage__get_matrix_at(KmzImage * const restrict me, const KmzPoint point, const size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter(KmzImage * const restrict me, const kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                            const size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter(KmzImage * const restrict me, const kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                                     const size_t m_size, KmzImage * const restrict buffer);

/**
 * Produces a new KmzImageLike wrapper for the given virtual table and image reference.
 */
const KmzImageLike KmzImageLike__wrap(const KmzImageLikeVTab * const vt_ref, const kmz_image_ptr ref);

/**
 * Gets the dimensions of the image..
 */
const KmzSize KmzImageLike__get_dimen(const KmzImageLike me);

/**
 * Gets a color from within the image.
 */
const kmz_color_32 KmzImageLike__get_argb_at(const KmzImageLike me, const KmzPoint point);

/**
 * Sets a color within the image.
 */
void KmzImageLike__set_argb_at(const KmzImageLike me, const KmzPoint point, const kmz_color_32 color);

/**
 * Reads a block of colors within the image.
 */
const KmzPixelOperationStatus KmzImageLike__read_argb_block(const KmzImageLike me, const KmzRectangle area, kmz_color_32 * const restrict buffer);

/**
 * Writes a block of colors to the image.
 */
const KmzPixelOperationStatus KmzImageLike__write_argb_block(const KmzImageLike me, const KmzRectangle area, const kmz_color_32 * const restrict buffer);

/**
 * Determines if the point is a valid coordinate within the image.
 */
const KmzBool KmzImageLike__is_valid(const KmzImageLike me, const KmzPoint point);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * const KmzImageLike__get_matrix_at(const KmzImageLike me, const KmzPoint point, const size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KKmzImageLike__apply_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area, const size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area, const size_t m_size,
                                         const KmzImageLike buffer);
// endregion;

// region Helpers:
#define KmzImage__get_argb_at_x_y(me, x, y) KmzImage__get_argb_at(me, kmz_point(x, y))

#define KmzImage__set_argb_at_x_y(me, x, y, color) KmzImage__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__is_valid_x_y(me, x, y) KmzImage__is_valid(me, kmz_point(x, y))

#define KmzMatrix__get_argb_at_x_y(me, x, y) KmzMatrix__get_argb_at(me, kmz_point(x, y), c)

#define KmzMatrix__set_argb_at_x_y(me, x, y, color) KmzMatrix__set_argb_at(me, kmz_point(x, y), c)

#define KmzImageMatrix__get_argb_at_x_y(me, x, y) KmzImageMatrix__get_argb_at(me, kmz_point(x, y), c)

#define KmzImageMatrix__set_argb_at_x_y(me, x, y, color) KmzImageMatrix__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__get_matrix_at_x_y(me, x, y) KmzImage__get_matrix_at(me, kmz_point(x, y))

#define KmzImageLike__get_argb_at_x_y(me, x, y) KmzImageLike__get_argb_at(me, kmz_point(x, y))

#define KmzImageLike__set_argb_at_x_y(me, x, y, color) KmzImageLike__set_argb_at(me, kmz_point(x, y), c)

#define KmzImageLike__is_valid_x_y(me, x, y) KmzImageLike__is_valid(me, kmz_point(x, y))

#define KmzImageLike__get_matrix_at_x_y(me, x, y, size) KmzImageLike__get_matrix_at(me, kmz_point(x, y), size)
// endregion;

#endif /* kmz_core_h */
