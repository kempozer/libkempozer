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
 * Defines the possible results from a draw operation.
 */
enum kmz_draw_status_e {
    KMZ_DRAW_OK = 0,
    KMZ_DRAW_ERR_OUT_OF_MEMORY = -64,
    KMZ_DRAW_ERR_UNKNOWN = -1000,
    KMZ_DRAW_ERR_USER = -1024,
};
typedef enum kmz_draw_status_e KmzDrawStatus;

/**
 * Defines the potential return values of an image read/write operation within kempozer.
 */
enum kmz_image_file_status_e {
    KMZ_IMAGE_FILE_OK = 0,
    KMZ_IMAGE_FILE_ERR_NOT_LOADED = -1,
    KMZ_IMAGE_FILE_ERR_READ_FAILED = -2,
    KMZ_IMAGE_FILE_ERR_WRITE_FAILED = -3,
    KMZ_IMAGE_FILE_ERR_UNSUPPORTED_OPERATION = -63,
    KMZ_IMAGE_FILE_ERR_OUT_OF_MEMORY = -64,
    /**
     * All implementors of custom KmzImageFile MUST provide their own status enum with error codes beginning at -1024.
     */
    KMZ_IMAGE_FILE_ERR_USER_ERROR = -1024,
};
typedef enum kmz_image_file_status_e KmzImageFileStatus;

/**
 * Defines the types of colors supported by this image file.
 */
enum kmz_image_file_color_type_e {
    KMZ_IMAGE_FILE_TRUECOLOR = 0,
    KMZ_IMAGE_FILE_PALETTE = 1,    
    KMZ_IMAGE_FILE_AHSL = 2,
    KMZ_IMAGE_FILE_UNKNOWN = -63,
    /**
     * All implementors of custom KmzImageFile MAY provide their own color type enum with type codes beginning at -1024.
     */
    KMZ_IMAGE_FILE_USER_TYPE = -1024,
};
typedef enum kmz_image_file_color_type_e KmzImageFileColorType;

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
    KMZ_PIXEL_OP_ERR_OUT_OF_MEMORY = -64,
    KMZ_PIXEL_OP_ERR_UNKNOWN = -1000,
    KMZ_PIXEL_OP_ERR_USER_ERR = -1024,
};
typedef enum kmz_pixel_operation_status_e KmzPixelOperationStatus;

// endregion;

#endif /* libkempozer_h */
