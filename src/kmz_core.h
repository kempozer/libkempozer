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

#include <stdlib.h>

#include "kmz_config.h"
#include "kmz_shared.h"
#include "kmz_geometry.h"
#include "kmz_color.h"

/**
 * Defines the standard pixel operation status codes as returned by block pixel operations.
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
    KMZ_PIXEL_OP_ERR_USER_ERR = -1024
};
typedef enum kmz_pixel_operation_status_e KmzPixelOperationStatus;

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
    const KmzPixelOperationStatus (* const read_argb_block)(const kmz_image_ptr_const, const KmzRectangle, kmz_color_32 * const restrict);
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
const KmzPixelOperationStatus KmzImage__apply_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
        const size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
const KmzPixelOperationStatus KmzImage__apply_buffered_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
        const size_t m_size, const KmzImagePtr buffer);

#endif /* kmz_core_h */
