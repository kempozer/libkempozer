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

#ifndef libkempozer_image_h
#define libkempozer_image_h

#include <stdlib.h>
#include <stdint.h>
#include <libkempozer.h>
#include <libkempozer/geometry.h>
#include <libkempozer/color.h>
#include <libkempozer/io.h>

/**
 * Defines the methods of a type that can be used as an image within kempozer.
 */
struct kmz_image_type_t {
    // region Version 1 methods:

    /**
     * @par Allocates an uninitialized image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * only iniitalize pointer fields to {@link NULL}
     * * return the appropriate pointer type for the image type being returned instead of `void * const`.
     *
     * @return A pointer to a memory location that contains an uninitialized image represented by this {@link KmzImageType}, or {@link NULL} if there isn't enough memory to allocate the image.
     */
    void * const (* const _new)(void);

    /**
     * @par Initializes an uninitialized image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the image being initialized instead of `void * const`
     * * free `me` if initialization fails.
     *
     * @par This method MAY:
     * * accept an argument (or multiple arguments using a struct) in `argv`
     * * accept the appropriate pointer type for the argument structure being used for initialization if needed.
     *
     * @param me A pointer to an uninitialized image represented by this {@link KmzImageType}.
     * @param argv A pointer to the arguments used to initialize the uninitialized image, or {@link NULL} if no arguments are to be used.
     */
    void (* const _ctor)(void * const me, const void * const argv);

    /**
     * @par Deallocates an initialized image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * free all pointers held
     * * free `me` when all other pointers are freed
     * * accept the appropriate pointer type for the image being deallocated instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     */
    void (* const _dtor)(void * const me);

    /**
     * @par Returns whether or not the given point is valid within the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the image being accessed instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @param point The point within the image to check.
     * @return {@link KMZ_TRUE} if the point exists in the image, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const is_valid)(const void * const me, const KmzPoint point);

    /**
     * @par Returns the dimensions of the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * return {@link KmzSize__ZERO} if `me` is {@link NULL}
     * * accept the appropriate pointer type for the image being accessed through `me` instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @return A {@link KmzSize} structure that represents the dimensions of the image represented by this {@link KmzImageType}.
     */
    const KmzSize (* const dimen)(const void * const me);

    /**
     * @par Returns a single ARGB value at the given coordinates from the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * return {@link kmz_color_32__ZERO} if `me` is {@link NULL} or `point` is invalid
     * * accept the appropriate pointer type for the image being accessed through `me` instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @param point A {@link KmzPoint} to read the color from.
     * @return A single {@link kmz_color_32} value that represents the color of the given position of the image represented by this {@link KmzImageType}.
     */
    const kmz_color_32 (* const argb_at)(const void * const me, const KmzPoint point);

    /**
     * @par Sets a single ARGB value at the given coordinates in the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL} or `point` is invalid
     * * accept the appropriate pointer type for the image being accessed through `me` instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @param point A {@link KmzPoint} to write the color to.
     * @param color A single {@link kmz_color_32} value that represents the color of the given position of the image represented by this {@link KmzImageType}.
     */
    void (* const set_argb_at)(void * const me, const KmzPoint point, const kmz_color_32 color);

    /**
     * @par Reads a block of ARGB values at the given coordinates and of the given dimensions in the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be {@link NULL} if not implemented
     * * do nothing if `me` is {@link NULL}
     * * return the appropriate {@link KmzPixelOperationStatus} if `area` or `buffer` is invalid
     * * accept the appropriate pointer type for the image being accessed through `me` instead of `void * const`.
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @param area A {@link KmzRectangle} that represents the area being read.
     * @param buffer A pointer to an initialized block of memory to read a block of ARGB values into.
     * @return {@link KMZ_PIXEL_OP_OK} if the block of ARGB values was successfully read, otherwise an appropriate value from {@link KmzPixelOperationStatus}.
     */
    const KmzPixelOperationStatus (* const read_argb_block)(const void * const me, const KmzRectangle area, kmz_color_32 * const buffer);

    /**
     * @par Writes a block of ARGB values at the given coordinates and of the given dimensions to the image represented by this {@link KmzImageType}.
     *
     * @par This method MUST:
     * * be {@link NULL} if not implemented
     * * do nothing if `me` is {@link NULL}
     * * return the appropraite {@link KmzPixelOperationStatus} if `area` or `buffer` is invalid
     * * accept the appropriate pointer type for the image being accessed through `me` instead of `void * const`
     *
     * @param me A pointer to an initialized image represented by this {@link KmzImageType}.
     * @param area A {@link KmzRectangle} that represents the area being written.
     * @param buffer A pointer to an initialized block of memory to write into `me`.
     * @return {@link KMZ_PIXEL_OP_OK} if the block of ARGB values was successfully written, otherwise an appropriate value from {@link KmzPixelOperationStatus}.
     */
    const KmzPixelOperationStatus (* const write_argb_block)(void * const me, const KmzRectangle area, const kmz_color_32 * const buffer);
    // endregion;
};
typedef struct kmz_image_type_t KmzImageType;

/**
 * Defines an abstract, opaque image within kempozer.
 */
struct kmz_image_t;
typedef struct kmz_image_t KmzImage;

/**
 * Defines an opaque matrix within kempozer.
 */
struct kmz_matrix_t;
typedef struct kmz_matrix_t KmzMatrix;

/**
 * Defines a function that is capable of applying a filter to an image using the given {@link KmzMatrix}.
 *
 * @param arg The argument to use along with the {@link KmzMatrix}.
 * @param matrix The matrix to read blocks of ARGB values from.
 * @return The color generated by the filter for the currently targeted pixel.
 */
typedef const kmz_color_32 (* KmzFilter)(const void * const arg, KmzMatrix * const matrix);



/**
 * Creates a new {@link KmzMatrix} instance that represents the provided buffer.
 *
 * @param buffer The block of memory being used as a buffer for this {@link KmzMatrix}.
 * @param image_dimen The dimensions of the buffer.
 * @param pos The starting position within the buffer of this {@link KmzMatrix}.
 * @param size The number of pixels across this {@link KmzMatrix} provides access to.
 * @return A pointer to the {@link KmzMatrix} represented by the given parameters, or {@link NULL} if there isn't enough memory to allocate the matrix.
 */
KmzMatrix * const KmzMatrix__new_from_buffer(kmz_color_32 * const buffer, const KmzSize image_dimen, const KmzPoint pos, const size_t size);

/**
 * Gets the size of the targeted {@link KmzMatrix}.
 *
 * @param me The target of this invocation.
 * @return The size of the targeted {@link KmzMatrix}.
 */
const size_t KmzMatrix__size(const KmzMatrix * const me);

/**
 * @par Gets the half size of the targeted {@link KmzMatrix}.
 *
 * @par This will always be the true number of pixels either side of point 0, 0 that may be accessed within this {@link KmzMatrix}.
 *
 * @param me The target of this invocation.
 * @return The half size of the targeted {@link KmzMatrix}.
 */
const size_t KmzMatrix__hsize(const KmzMatrix * const me);

/**
 * Gets the current position of the targeted {@link KmzMatrix}.
 *
 * @param me The target of this invocation.
 * @return The current position within the buffer of this {@link KmzMatrix}.
 */
const KmzPoint KmzMatrix__pos(const KmzMatrix * const me);

/**
 * Sets the current position of the targeted {@link KmzMatrix} to the value of `pos`.
 *
 * @param me The target of this invocation
 * @param pos The new position of the targeted {@link KmzMatrix}.
 */
void KmzMatrix__set_pos(KmzMatrix * const me, const KmzPoint pos);

/**
 * @par Gets a pixel color from the targeted {@link KmzMatrix} at the given offset from its current position.
 *
 * @par The value for `point` MAY be clamped between `KmzMatrix__hsize(me)` and `-KmzMatrix__hsize(me)`. Accessing an invalid offset is undefined in situations where clamping is not performed.
 *
 * @param me The target of this invocation.
 * @param point The offset from the current position to read the color from.
 * @return A single ARGB value representing the color of the pixel.
 */
const kmz_color_32 KmzMatrix__argb_at(const KmzMatrix * const me, const KmzPoint point);

/**
 * @par Sets a pixel color in the targeted {@link KmzMatrix} at the given offset from its current position.
 *
 * @par The value for `point` MAY be clamped between `KmzMatrix__hsize(me)` and `-KmzMatrix__hsize(me)`. Accessing an invalid offset is undefined in situations where clamping is not performed.
 *
 * @param me The target of this invocation.
 * @param point The offset from the current position to write the color to.
 * @param color A single ARGB value representing the new color of the pixel.
 */
void KmzMatrix__set_argb_at(KmzMatrix * const me, const KmzPoint point, const kmz_color_32 color);

/**
 * @par Attempts to allocate a new image of the given {@link KmzImageType} using the given `argv` pointer.
 *
 * @par If `type` is {@link NULL} or there is not enough memory to allocate the image, then {@link NULL} is returned. If no argument is needed for initialization, then {@link NULL} should be passed.
 *
 * @par First, the `_new` method of `type` is invoked to allocate the image proper. If the system is able to allocate the image, then `_ctor` of `type` is invoked with the reference to the image and the reference to `argv`.
 *
 * @param type The type of {@link KmzImage} to allocate.
 * @param argv The argument to initialize the {@link KmzImage} with.
 * @return A pointer to a {@link KmzImage} that represents the given {@link KmzImageType} initialized with the given `argv`.
 *
 * @see KmzImageType#_new
 * @see KmzImageType#_ctor
 */
KmzImage * const KmzImage__new(const KmzImageType * const type, const void * const argv);

/**
 * @par Deallocates the memory used by this {@link KmzImage}.
 *
 * @par If `me` is a valid image, then its type's `_dtor` method will be invoked with the allocated image's reference. The `_dtor` MUST free all resources consumed by the allocated image reference. Once `_dtor` has finished, `me` wil lbe automatically freed.
 *
 * @param me The target of this invocation.
 *
 * @see KmzImageType#_dtor
 */
void KmzImage__free(KmzImage * const me);

/**
 * Returns the appropriate {@link KmzImageType} for the target {@link KmzImage}.
 *
 * @param me The target of this invocation.
 * @return The appropriate {@link KmzImageType} represented by the targeted {@link KmzImage}.
 */
const KmzImageType * const KmzImage__type(const KmzImage * const me);

/**
 * Returns the dimensions of the targeted {@link KmzImage}.
 *
 * @param me The target of this invocation.
 * @return The dimensions of this {@link KmzImage} represented as a {@link KmzSize}.
 *
 * @see KmzImageType#dimen
 */
const KmzSize KmzImage__dimen(const KmzImage * const me);

/**
 * Returns a color from the targeted {@link KmzImage} at the given coordinate.
 *
 * @param me The target of this invocation.
 * @param point The position of the pixel to read the color of.
 * @return The color at the given position within the {@link KmzImage}.
 *
 * @see KmzImageType#argb_at
 */
const kmz_color_32 KmzImage__argb_at(const KmzImage * const me, const KmzPoint point);

/**
 * Sets a color in the targeted {@link KmzImage} at the given coordinate.
 *
 * @param me The target of this invocation.
 * @param point The position of the pixel to write the color of.
 * @param color The new color of the pixel.
 *
 * @see KmzImageType#set_argb_at
 */
void KmzImage__set_argb_at(KmzImage * const me, const KmzPoint point, const kmz_color_32 color);

/**
 * @par Reads a block of ARGB colors within the target {@link KmzImage} into the provided buffer.
 *
 * @par If the target {@link KmzImage} does not provide an implementation for this method, then a fallback implementation will be used. This fallback implementation will require individual reads to {@link KmzImage__argb_at} and will be substantially slower than a native implementation, so its encouraged that all inheritors implement this method.
 *
 * @param me The target of this invocation.
 * @param area The area of this image to read into the buffer.
 * @param buffer The buffer to read into.
 * @return {@link KMZ_PIXEL_OP_OK} if the read operation is successful, otherwise the appropriate {@link KmzPixelOperationStatus}.
 *
 * @see KmzImageType#read_argb_block
 */
const KmzPixelOperationStatus KmzImage__read_argb_block(const KmzImage * const me, const KmzRectangle area, kmz_color_32 * const buffer);

/**
 * @par Writes a block of ARGB colors to the target {@link KmzImage} from the provided buffer.
 *
 * @par If the target {@link KmzImage} does not provide an implementation for this method, then a fallback implementation will be used. This fallback implementation will require individual writes to {@link KmzImage__set_argb_at} and will be substantially slower than a native implementation, so its encouraged that all inheritors implement this method.
 *
 * @param me The target of this invocation.
 * @param area The area of this image to write the buffer to.
 * @param buffer The buffer to read from.
 * @return {@link KMZ_PIXEL_OP_OK} if the read operation is successful, otherwise the appropriate {@link KmzPixelOperationStatus}.
 *
 * @see KmzImageType#write_argb_block
 */
const KmzPixelOperationStatus KmzImage__write_argb_block(KmzImage * const me, const KmzRectangle area, const kmz_color_32 * const buffer);

/**
 * Determines if the provided {@link KmzPoint} is within the target {@link KmzImage}.
 *
 * @param me The target of this invocation.
 * @param point The position to check within the target image.
 * @return {@link KMZ_TRUE} if the position points to a valid pixel within the target image, otherwise {@link KMZ_FALSE}.
 *
 * @see KmzImageType#is_valid
 */
const KmzBool KmzImage__is_valid(const KmzImage * const me, const KmzPoint point);

/**
 * Applies a filter operation to the target {@link KmzImage} with the given `argv` and {@link KmzFilter} using a matrix the size of `m_size` at the area of `area`.
 *
 * @param me The target of this invocation.
 * @param argv The argument to pass to `filter`.
 * @param filter The filter to apply to the region of the target {@link KmzImage}.
 * @param area The area within the target {@link KmzImage} to apply the filter to.
 * @param m_size The size of matrix to use.
 * @return {@link KMZ_PIXEL_OP_OK} if `filter` is applied to the image, otherwise an appropriate {@link KmzPixelOperationStatus}.
 *
 * @see KmzImage__apply_buffered_filter()
 *
 * @deprecated This method is planned for removal in favor of using apply_buffered_filter.
 */
__attribute__((deprecated)) const KmzPixelOperationStatus KmzImage__apply_filter(KmzImage * const me,
        const void * const argv,
        const KmzFilter filter,
        const KmzRectangle area,
        const size_t m_size);

/**
 * Applies a filter operation to the target {@link KmzImage} with the given `argv` and {@link KmzFilter} using a matrix the size of `m_size` at the area of `area`.
 *
 * @param me The target of this invocation.
 * @param argv The argument to pass to `filter`.
 * @param filter The filter to apply to the region of the target {@link KmzImage}.
 * @param area The area within the target {@link KmzImage} to apply the filter to.
 * @param m_size The size of matrix to use.
 * @param buffer The buffer to write all changes to.
 * @return {@link KMZ_PIXEL_OP_OK} if `filter` is applied to the image, otherwise an appropriate {@link KmzPixelOperationStatus}.
 */
const KmzPixelOperationStatus KmzImage__apply_buffered_filter(const KmzImage * const me,
        const void * const argv,
        const KmzFilter filter,
        const KmzRectangle area,
        const size_t m_size,
        KmzImage * const buffer);

/**
 * Creates a new image using the provided file.
 *
 * @param dimen The dimensions of the image.
 * @param buffer The buffer to use as a source of pixels for the image.
 * @param copy_source {@link KMZ_TRUE} if `buffer` should be copied, otherwise {@link KMZ_FALSE}.
 */
KmzImage * const KmzImage__new_from_file(KmzImageFile * const file);

/**
 * Creates a new image using the provided buffer.
 *
 * @param dimen The dimensions of the image.
 * @param buffer The buffer to use as a source of pixels for the image.
 * @param copy_source {@link KMZ_TRUE} if `buffer` should be copied, otherwise {@link KMZ_FALSE}.
 */
KmzImage * const KmzImage__new_from_buffer(const KmzSize dimen, kmz_color_32 * const buffer, const KmzBool copy_source);

/**
 * @par The standard {@link KmzImageType} as implemented by kempozer.
 *
 * @par This implementation is a general purpose, ARGB buffer based image. The entire image is stored in memory and is directly manipulated in memory. It provides an implementation for every available {@link KmzImageType} method and should only be allocated using {@link KmzImage__new_from_gd_2x} and {@link KmzImage__new_from_buffer}.
 */
extern const KmzImageType kmz_image;

#endif /* libkempozer_image_h */
