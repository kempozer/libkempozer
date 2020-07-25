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

#ifndef libkempozer_io_h
#define libkempozer_io_h

#include <stdlib.h>
#include <stdint.h>
#include <libkempozer.h>
#include <libkempozer/geometry.h>
#include <libkempozer/color.h>

/**
 * Defines the methods of a type that can be used as an image file within kempozer.
 */
struct kmz_image_file_type_t {
    // region Version 1 methods:

    /**
     * @par Allocates an uninitialized image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * only initialize pointer fields to {@link NULL}
     * * return the appropriate pointer type for the image file type being returned instead of `void * const`.
     *
     * @return A pointer to a memory location that contains an uninitialized image file represented by this {@link KmzImageFileType}, or {@link NULL} if there isn't enough memory.
     */
    void * const (* const _new)(void);

    /**
     * @par Initializes an uninitialized image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the image file being initialized instead of `void * const`
     * * free `me` if initialization fails.
     *
     * @par This method MAY:
     * * accept an argument (or multiple arguments using a struct) in `argv`
     * * accept the appropriate pointer type for the argument structure being used for initialization if needed.
     *
     * @param me A pointer to an uninitialized image file represented by this {@link KmzImageFileType}.
     * @param argv A pointer to the arguments used to initialize the uninitialized image file, or {@link NULL} if no arguments are to be used.
     */
    void (* const _ctor)(void * const me, const void * const argv);

    /**
     * @par Deallocates an initialized image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * free all pointers held
     * * free `me` when all other pointers are freed
     * * accept the appropriate pointer type for the image file being deallocated instead of `void * const`.
     *
     * @param me A pointer to an initialized image file being represented by this {@link KmzImageFileType}.
     */
    void (* const _dtor)(void * const me);

    /**
     * @par Returns the dimensions of the image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * return {@link KmzSize__ZERO} if the image has not been loaded yet
     * * accept the appropriate pointer type for the image file being accessed.
     *
     * @param me The target of this invocation.
     * @return A {@link KmzSize} containing the dimensions of the target {@link KmzImageFile}.
     */
    const KmzSize (* const dimen)(const void * const me);

    /**
     * @par Returns the color type stored and supported by the image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * return {@link KMZ_IMAGE_FILE_UNKNOWN} if the image has not been loaded yet
     * * accept the appropriate pointer type for the image file being accessed.
     *
     * @par This method MAY:
     * * always return a single supported color type if no other color types are supported by the file.
     *
     * @param me The target of this invocation.
     * @return The appropriate {@link KmzImageFileColorType} for the target.
     */
    const KmzImageFileColorType (* const color_type)(const void * const me);

    /**
     * @par Returns the most recent status of the image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * return the MOST RECENT {@link KmzImageFileStatus} produced by the image file
     * * return {@link KMZ_IMAGE_FILE_ERR_NOT_LOADED} if the image has not been loaded yet.
     *
     * @param me The target of this invocation.
     * @return {@link KMZ_IMAGE_FILE_OK} if the status of the target is not errored, otherwise an appropriate {@link KmzImageFileStatus} specifying the error.
     */
    const KmzImageFileStatus (* const status)(const void * const me);

    /**
     * @par Returns a status message appropriate for the {@link KmzImageFileType} and {@link KmzImageFileStatus}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * return {@link NULL} if `status` is {@link KMZ_IMAGE_FILE_OK} or an unsupported value.
     *
     * @par This method MAY:
     * * return {@link NULL} if the default status message for `status` should be used.
     *
     * @param me The target of this invocation.
     * @param status The status to retrieve the message from.
     * @return A string representing the message of the given status, or {@link NULL} if the status isn't defined by the target.
     */
    const char * const (* const status_msg)(const void * const me, const KmzImageFileStatus status);

    /**
     * @par Attempts to save the image file represented by this {@link KmzImageFileType} to the given path.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}.
     *
     * @param me The target of this invocation.
     * @param path The path to save `me` to.
     * @return {@link KMZ_IMAGE_FILE_OK} if the image was saved sucessfully, otherwise an appropriate {@link KmzImageFileStatus} specifying the error.
     */
    const KmzImageFileStatus (* const save)(void * const me, const char * const path);

    /**
     * @par Attempts to load the image file represented by this {@link KmzImageFileType} from the given path.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}.
     *
     * @param me The target of this invocation.
     * @param path The path to load into `me`.
     * @return {@link KMZ_IMAGE_FILE_OK} if the image was saved sucessfully, otherwise an appropriate {@link KmzImageFileStatus} specifying the error.
     */
    const KmzImageFileStatus (* const load)(void * const me, const char * const path);

    /**
     * @par Gets the total number of colors available in the palette of the image file represented by this {@link KmzImageFileType}.
     *
     * @par This method MUST:
     * * be {@link NULL} if not implemented
     * * do nothing if `me` is {@link NULL}
     * * return 0 if the image file isn't palette-based or hasn't been loaded yet.
     *
     * @param me The target of this invocation.
     * @return The total number of colors within the target's palette.
     */
    const size_t (* const palette_color_count)(void * const me);

    /**
     * @par Attempts to read the palette colors of the image file represented by this {@link KmzImageFileType} into the given memory.
     *
     * @par This method MUST:
     * * be {@link NULL} if not implemented
     * * do nothing if `me` is {@link NULL}
     * * return the appropriate error if `buffer` is {@link NULL}.
     *
     * @param me The target of this invocation.
     * @param buffer The buffer to write the palette colors of the target to.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const read_palette_colors)(void * const me, kmz_color_32 * const buffer);

    /**
     * @par Attempts to read the pixels of the image file represented by this {@link KmzImageFileType} into the given memory.
     *
     * @par This method MUST:
     * * be {@link NULL} if not implemented
     * * do nothing if `me` is {@link NULL}
     * * return the appropriate error if `buffer` is {@link NULL}.
     *
     * @param me The target of this invocation.
     * @param buffer The buffer to write the palette pixels of the target to.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const read_palette_pixels)(void * const me, uint8_t * const buffer);

    /**
     *
     * @param me The target of this invocation.
     * @param buffer The buffer to write the truecolor pixels of the target to.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const read_truecolor_pixels)(void * const me, kmz_color_32 * const buffer);

    /**
     *
     * @param me The target of this invocation.
     * @param buffer The buffer to write the AHSL pixels of the target to.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const read_ahsl_pixels)(void * const me, KmzAhslColor * const buffer);

    /**
     *
     * @param me The target of this invocation.
     * @param color_count The total size of the palette of the palette image.
     * @param pad_count The total size of the palette when written to the disk. This must be equal to or greater than color_count.
     * @param palette The palette of the palette image.
     * @param dimen The dimensions of the palette image.
     * @param pixels The pixels of the palette image.
     * @param copy_source {@link KMZ_TRUE} if the pixel source and palette source should be copied, otherwise {@link KMZ_FALSE}.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const set_palette_image)(void * const me,
            const size_t color_count,
            const size_t pad_count,
            const kmz_color_32 * const palette,
            const KmzSize dimen,
            const uint8_t * const pixels,
            const KmzBool copy_source);

    /**
     *
     * @param me The target of this invocation.
     * @param dimen The dimensions of this truecolor image.
     * @param pixels The pixels of  this truecolor image.
     * @param copy_source {@link KMZ_TRUE} if the pixel source should be copied, otherwise {@link KMZ_FALSE}.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const set_truecolor_image)(void * const me,
            const KmzSize dimen,
            const kmz_color_32 * const pixels,
            const KmzBool copy_source);

    /**
     *
     * @param me The target of this invocation.
     * @param dimen The dimensions of this AHSL image.
     * @param pixels The pixels of  this AHSL image.
     * @param copy_source {@link KMZ_TRUE} if the pixel source should be copied, otherwise {@link KMZ_FALSE}.
     * @return The current status of `me`.
     */
    const KmzImageFileStatus (* const set_ahsl_image)(void * const me,
            const KmzSize dimen,
            const KmzAhslColor * const pixels,
            const KmzBool copy_source);

    /**
     * 
     * @param me The target of this invocation.
     * @return {@link KMZ_TRUE} if metadata is supported by the target, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const supports_metadata)(const void * const me);

    /**
     *
     * @param me The target of this invocation.
     * @param name The name of the metadata to check for support of.
     * @return {@link KMZ_TRUE} if the given name matches a supported metadata field, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const is_supported_metadata)(const void * const me, const char * const name);

    /**
     *
     * @param me The target of this invocation.
     * @param name The name of the metadata to return.
     * @return The value of the metadata, or {@link NULL} if no metadata exists or an image isn't currently loaded.
     */
    const char * const (* const metadata)(const void * const me, const char * const name);

    /**
     *
     * @param me The target of this invocation.
     * @param name The name of the metadata to return.
     * @return {@link KMZ_TRUE} if the metadata has been set on the target, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const has_metadata)(const void * const me, const char * const name);

    /**
     * 
     * @param me The target of this invocation.
     * @param name The name of the metadata to set.
     * @param value The new value of the metadata.
     * @return {@link KMZ_IMAGE_FILE_OK} if the operation is successful, otherwise an appropriate {@link KmzImageFileStatus} specifying the error.
     */
    const KmzImageFileStatus (* const set_metadata)(void * const me, const char * const name, const char * const value);

    /**
     *
     * @param me The target of this invocation.
     * @param name The name of the metadata to remove.
     * @return {@link KMZ_IMAGE_FILE_OK} if the operation is successful, otherwise an appropriate {@link KmzImageFileStatus} specifying the error.
     */
    const KmzImageFileStatus (* const remove_metadata)(void * const me, const char * const name);

    // endregion;
};
typedef struct kmz_image_file_type_t KmzImageFileType;

struct kmz_image_file_t;
typedef struct kmz_image_file_t KmzImageFile;

KmzImageFile * const KmzImageFile__new(const KmzImageFileType * const type, const void * const argv);

void KmzImageFile__free(KmzImageFile * const me);

const KmzImageFileType * const KmzImageFile__type(const KmzImageFile * const me);

const KmzSize KmzImageFile__dimen(const KmzImageFile * const me);

const KmzImageFileColorType KmzImageFile__color_type(const KmzImageFile * const me);

const KmzImageFileStatus KmzImageFile__status(const KmzImageFile * const me);

const char * const KmzImageFile__status_msg(const KmzImageFile * const me, const KmzImageFileStatus status);

const KmzImageFileStatus KmzImageFile__save(KmzImageFile * const me, const char * const path);

const KmzImageFileStatus KmzImageFile__load(KmzImageFile * const me, const char * const path);

const size_t KmzImageFile__palette_color_count(const KmzImageFile * const me);

const KmzImageFileStatus KmzImageFile__read_palette_colors(KmzImageFile * const me, kmz_color_32 * const buffer);

const KmzImageFileStatus KmzImageFile__read_palette_pixels(KmzImageFile * const me, uint8_t * const buffer);

const KmzImageFileStatus KmzImageFile__read_truecolor_pixels(KmzImageFile * const me, kmz_color_32 * const buffer);

const KmzImageFileStatus KmzImageFile__read_ahsl_pixels(KmzImageFile * const me, KmzAhslColor * const buffer);

const KmzImageFileStatus KmzImageFile__set_palette_image(KmzImageFile * const me,
        const size_t color_count,
        const size_t pad_count,
        const kmz_color_32 * const palette,
        const KmzSize dimen,
        const uint8_t * const pixels,
        const KmzBool copy_source);

const KmzImageFileStatus KmzImageFile__set_truecolor_image(KmzImageFile * const me,
        const KmzSize dimen,
        const kmz_color_32 * const pixels,
        const KmzBool copy_source);

const KmzImageFileStatus KmzImageFile__set_ahsl_image(KmzImageFile * const me,
        const KmzSize dimen,
        const KmzAhslColor * const pixels,
        const KmzBool copy_source);

const KmzBool KmzImageFile__supports_metadata(const KmzImageFile * const me);

const KmzBool KmzImageFile__is_supported_metadata(const KmzImageFile * const me, const char * const name);

const char * const KmzImageFile__metadata(const KmzImageFile * const me, const char * const name);

const KmzBool KmzImageFile__has_metadata(const KmzImageFile * const me, const char * const name);

const KmzImageFileStatus KmzImageFile__set_metadata(KmzImageFile * const me, const char * const name, const char * const value);

const KmzImageFileStatus KmzImageFile__remove_metadata(KmzImageFile * const me, const char * const name);

#endif /* libkempozer_io_h */
