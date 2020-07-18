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

struct kmz_matrix_t;

/**
 * Defines the structure of a virtual table for image-like objects.
 */
struct kmz_image_like_vtab_t {
    // region Fully Virtual Methods:
    const KmzSize (* const get_dimen)(const kmz_image_ptr_const);
    const kmz_color_32 (* const get_argb_at)(const kmz_image_ptr_const, const KmzPoint);
    void (* const set_argb_at)(kmz_image_ptr_const, const KmzPoint, const kmz_color_32);
    const KmzBool (* const is_valid)(const kmz_image_ptr_const, const KmzPoint);
    // endregion;
    // region Virtual Methods:
    const KmzPixelOperationStatus (* const read_argb_block)(const kmz_image_ptr_const, const KmzRectangle, kmz_color_32 * const);
    const KmzPixelOperationStatus (* const write_argb_block)(kmz_image_ptr_const, const KmzRectangle, const kmz_color_32 * const);
    // endregion;
    
};
typedef struct kmz_image_like_vtab_t KmzImageLikeVTab;

/**
 * Defines the structure of an image-like object reference, including its virtual table and me (this) pointer.
 */
struct kmz_image_like_t {
    const KmzImageLikeVTab * _vt;
    kmz_image_ptr _me;
};
typedef struct kmz_image_like_t KmzImageLike;

/**
 * Defines the structure of an image-like-based matrix object.
 */
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
    KmzSize image_dimen;
    /**
     * @const
     */
    kmz_color_32 * pixels;
};
typedef struct kmz_matrix_t KmzMatrix;

typedef const kmz_color_32 (*KmzFilter)(kmz_arg_ptr, KmzMatrix * const restrict);
// endregion;

// region Functions:

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * const KmzMatrix__new_from_buffer(kmz_color_32 * const restrict buffer, const KmzSize image_dimen, const KmzPoint pos, const size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
const kmz_color_32 KmzMatrix__get_argb_at(const KmzMatrix * const restrict me, const KmzPoint point);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color);

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
 * Applies a matrix filter function to the image referenced.
 */
KmzPixelOperationStatus KmzImageLike__apply_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                                   const size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
KmzPixelOperationStatus KmzImageLike__apply_buffered_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                                            const size_t m_size, const KmzImageLike buffer);
// endregion;

// region Helpers:

#define KmzMatrix__get_argb_at_x_y(me, x, y) KmzMatrix__get_argb_at(me, kmz_point(x, y), c)

#define KmzMatrix__set_argb_at_x_y(me, x, y, color) KmzMatrix__set_argb_at(me, kmz_point(x, y), c)

#define KmzImageLike__get_argb_at_x_y(me, x, y) KmzImageLike__get_argb_at(me, kmz_point(x, y))

#define KmzImageLike__set_argb_at_x_y(me, x, y, color) KmzImageLike__set_argb_at(me, kmz_point(x, y), c)

#define KmzImageLike__is_valid_x_y(me, x, y) KmzImageLike__is_valid(me, kmz_point(x, y))

#define KmzImageLike__get_matrix_at_x_y(me, x, y, size) KmzImageLike__get_matrix_at(me, kmz_point(x, y), size)
// endregion;

#endif /* kmz_core_h */
