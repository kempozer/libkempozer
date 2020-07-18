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

#ifndef kmz_image_h
#define kmz_image_h

#include <stdio.h>
#include "kmz_geometry.h"
#include "kmz_color.h"
#include "kmz_core.h"

// region Types:
/**
 * Defines the structure of an image object.
 */
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

/**
 * Defines the structure of an image-based matrix object.
 */
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

// endregion;

// region Helpers:

#define KmzImage__get_argb_at_x_y(me, x, y) KmzImage__get_argb_at(me, kmz_point(x, y))

#define KmzImage__set_argb_at_x_y(me, x, y, color) KmzImage__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__is_valid_x_y(me, x, y) KmzImage__is_valid(me, kmz_point(x, y))

#define KmzImageMatrix__get_argb_at_x_y(me, x, y) KmzImageMatrix__get_argb_at(me, kmz_point(x, y), c)

#define KmzImageMatrix__set_argb_at_x_y(me, x, y, color) KmzImageMatrix__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__get_matrix_at_x_y(me, x, y) KmzImage__get_matrix_at(me, kmz_point(x, y))

// endregion;

#endif /* kmz_image_h */
