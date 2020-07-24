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

#ifndef libkempozer_gdfile_h
#define libkempozer_gdfile_h

#include <stdio.h>
#include <libkempozer.h>
#include <libkempozer/geometry.h>
#include <libkempozer/color.h>

/**
 * Defines the structure of the header of a GD image as parsed by kempozer.
 */
struct kmz_gd_2x_image_file_signature_header_t {
    uint16_t type;
    KmzSize dimen;
};
typedef struct kmz_gd_2x_image_file_signature_header_t KmzGd2xImageFileSignatureHeader;

/**
 * Defines the structure of the truecolor header of a GD image as parsed by kempozer.
 */
struct kmz_gd_2x_image_file_truecolor_header_t {
    kmz_color_32 transparent;
};
typedef struct kmz_gd_2x_image_file_truecolor_header_t KmzGd2xImageFileTruecolorHeader;

/**
 * Defines the structure of the palette header of a GD image as parsed by kempozer.
 */
struct kmz_gd_2x_image_file_palette_header_t {
    uint16_t count;
    kmz_color_32 transparent;
    kmz_color_32 colors[32];
};
typedef struct kmz_gd_2x_image_file_palette_header_t KmzGd2xImageFilePaletteHeader;

/**
 * Defines the structure of the color header of a GD image as parsed by kempozer.
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
 * Defines the structure of the file header of a GD image as parsed by kempozer.
 */
struct kmz_gd_2x_image_file_header_t {
    KmzGd2xImageFileSignatureHeader signature;
    KmzGd2xImageFileColorHeader color;
};
typedef struct kmz_gd_2x_image_file_header_t KmzGd2xImageFileHeader;

/**
 * Defines the structure of the file of a GD image as parsed by kempozer.
 */
struct kmz_gd_2x_image_file_t {
    KmzGd2xImageFileHeader header;
    union {
        kmz_color_32 * truecolor;
        uint8_t * palette;
    } pixels;
};
typedef struct kmz_gd_2x_image_file_t KmzGd2xImageFile;

const KmzGd2xImageFileStatus kmz_read_gd_2x_image_file(FILE * const restrict f,
        KmzGd2xImageFile * const restrict o);

const KmzGd2xImageFileStatus kmz_write_gd_2x_image_file(FILE * const restrict f,
        const KmzGd2xImageFile * const restrict i);

const char * const kmz_status_msg(const KmzGd2xImageFileStatus status);

const char * const kmz_status_msg_with_err_code(const KmzGd2xImageFileStatus status,
        const int error);


#endif /* libkempozer_gdfile_h */
