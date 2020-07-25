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

#include "kmz_gd_2x_image_file.h"

static const int _kmz_read_byte(FILE * const restrict f, uint8_t * const restrict r) {
    if (1 == fread(r, sizeof(uint8_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

static const int _kmz_read_byte_buffer(FILE * const restrict f, uint8_t * const restrict r, const size_t s) {
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fread(r + total, sizeof(uint8_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fread(r + total, sizeof(uint8_t), remainder, f);
    }
    if (s == total) {
        return 0;
    }
    return ferror(f);
}

static const int _kmz_write_byte(FILE * const restrict f, const uint8_t v) {
    if (1 == fwrite(&v, sizeof(uint8_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

static const int _kmz_write_byte_buffer(FILE * const restrict f, const uint8_t * const restrict r, const size_t s) {
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fwrite(r + total, sizeof(uint8_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fwrite(r + total, sizeof(uint8_t), remainder, f);
    }
    return s == total ? 0 : ferror(f);
}

static const int _kmz_read_short(FILE * const restrict f, uint16_t * const restrict r) {
    if (1 == fread(r, sizeof(uint16_t), 1, f)) {
        *r = ntohs(*r);
        return 0;
    }
    return ferror(f);
}

static const int _kmz_write_short(FILE * const restrict f, uint16_t v) {
    v = htons(v);
    if (1 == fwrite(&v, sizeof(uint16_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

static const int _kmz_read_int_buffer(FILE * const restrict f, uint32_t * const restrict r, const size_t s) {
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fread(r + total, sizeof(uint32_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fread(r + total, sizeof(uint32_t), remainder, f);
    }
    if (s == total) {
        for (size_t i = 0; i < s; ++i) {
            r[i] = ntohl(r[i]);
        }
        return 0;
    }
    return ferror(f);
}

static const int _kmz_write_int_buffer(FILE * const restrict f, uint32_t * const restrict r, const size_t s) {
    for (size_t i = 0; i < s; ++i) {
        r[i] = htonl(r[i]);
    }
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fwrite(r + total, sizeof(uint32_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fwrite(r + total, sizeof(uint32_t), remainder, f);
    }
    return s == total ? 0 : ferror(f);
}

static const int _kmz_read_int(FILE * const restrict f, uint32_t * const restrict r) {
    if (1 == fread(r, sizeof(uint32_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

static const int _kmz_write_int(FILE * const restrict f, uint32_t v) {
    if (1 == fwrite(&v, sizeof(uint32_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

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
    KmzGd2xImageFileStatus status;
    KmzBool owns_pixels;
    KmzGd2xImageFileHeader header;
    union {
        kmz_color_32 * truecolor;
        uint8_t * palette;
    } pixels;
};
typedef struct kmz_gd_2x_image_file_t KmzGd2xImageFile;

static KmzGd2xImageFile * const _KmzGd2xImageFile__new(void) {
    return malloc(sizeof(KmzGd2xImageFile));
}

static void _KmzGd2xImageFile__ctor(KmzGd2xImageFile * const restrict me, const void * const restrict argv) {
    if (me != NULL) {
        me->status = (KmzGd2xImageFileStatus)KMZ_IMAGE_FILE_ERR_NOT_LOADED;
        me->pixels.palette = NULL;
    }
}

static void _KmzGd2xImageFile__dtor(KmzGd2xImageFile * const restrict me) {
    if (KMZ_TRUE == me->owns_pixels) {
        switch (me->header.signature.type) {
            case KMZ_GD_2X_IMAGE_FILE_PALETTE:
                if (me->pixels.palette != NULL) {
                    free(me->pixels.palette);
                }
                break;
            case KMZ_GD_2X_IMAGE_FILE_TRUECOLOR:
                if (me->pixels.truecolor != NULL) {
                    free(me->pixels.truecolor);
                }
                break;
        }
    }
    free(me);
}

static const KmzSize _KmzGd2xImageFile__dimen(const KmzGd2xImageFile * const restrict me) {
    if (KMZ_GD_OK == me->status) {
        return me->header.signature.dimen;
    }
    return KmzSize__ZERO;
}

static const KmzImageFileColorType _KmzGd2xImageFile__color_type(const KmzGd2xImageFile * const restrict me) {
    if (KMZ_GD_OK == me->status) {
        return me->header.color.is_truecolor == 1 ? KMZ_IMAGE_FILE_TRUECOLOR : KMZ_IMAGE_FILE_PALETTE;
    }
    return KMZ_IMAGE_FILE_UNKNOWN;
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__status(const KmzGd2xImageFile * const restrict me) {
    return me->status;
}

static void _KmzGd2xImageFile__clear_status(KmzGd2xImageFile * const restrict me) {
    if (me->status != KMZ_IMAGE_FILE_ERR_NOT_LOADED) {
        me->status = KMZ_GD_OK;
    }
}

static const char * const _KmzGd2xImageFile__status_msg(const KmzGd2xImageFile * const restrict me, const KmzGd2xImageFileStatus status) {
    switch (status) {
        case KMZ_GD_ERR_INVALID_FILE_PTR:
            return "An invalid file pointer has been provided";
        case KMZ_GD_ERR_INVALID_IMAGE_PTR:
            return "An invalid image pointer has been provided";
        case KMZ_GD_ERR_READ_SIGNATURE:
            return "An error has occurred while reading the GD 2x header signature";
        case KMZ_GD_ERR_WRITE_SIGNATURE:
            return "An error has occurred while writing the GD 2x header signature";
        case KMZ_GD_ERR_READ_WIDTH:
            return "An error has occurred while reading the GD 2x header width";
        case KMZ_GD_ERR_READ_HEIGHT:
            return "An error has occurred while reading the GD 2x header height";
        case KMZ_GD_ERR_WRITE_WIDTH:
            return "An error has occurred while writing the GD 2x header width";
        case KMZ_GD_ERR_WRITE_HEIGHT:
            return "An error has occurred while writing the GD 2x header height";
        case KMZ_GD_ERR_READ_IS_TRUECOLOR:
            return "An error has occurred while reading the GD 2x header truecolor flag";
        case KMZ_GD_ERR_WRITE_IS_TRUECOLOR:
            return "An error has occurred while writing the GD 2x header truecolor flag";
        case KMZ_GD_ERR_READ_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header truecolor transparent color";
        case KMZ_GD_ERR_WRITE_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header truecolor transparent color";
        case KMZ_GD_ERR_READ_PALETTE_COUNT:
            return "An error has occurred while reading the GD 2x header palette count";
        case KMZ_GD_ERR_WRITE_PALETTE_COUNT:
            return "An error has occurred while writing the GD 2x header palette count";
        case KMZ_GD_ERR_READ_PALETTE_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header palette transparent color";
        case KMZ_GD_ERR_WRITE_PALETTE_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header palette transparent color";
        case KMZ_GD_ERR_READ_PALETTE_COLORS:
            return "An error has occurred while reading the GD 2x header palette colors";
        case KMZ_GD_ERR_WRITE_PALETTE_COLORS:
            return "An error has occurred while writing the GD 2x header palette colors";
        case KMZ_GD_ERR_READ_PIXELS:
            return "An error has occurred while reading the GD 2x pixels";
        case KMZ_GD_ERR_WRITE_PIXELS:
            return "An error has occurred while writing the GD 2x pixels";
        case KMZ_GD_ERR_UNSUPPORTED_OPERATION:
            return "An unsupported operation has been encountered";
        case KMZ_GD_ERR_OUT_OF_MEMORY:
            return "System is out of memory";
        case KMZ_GD_ERR_UNKNOWN:
            return "An unknown error has occurred";
        default:
            return NULL;
    }
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__save(KmzGd2xImageFile * const restrict me, const char * const path) {
    FILE * const restrict f = fopen(path, "wb+");
    if (NULL == f) {
        free(f);
        return me->status = KMZ_GD_ERR_INVALID_FILE_PTR;
    }

    if (0 != _kmz_write_short(f, me->header.signature.type)) {
        free(f);
        return me->status = KMZ_GD_ERR_WRITE_SIGNATURE;
    }
    if (0 != _kmz_write_short(f, me->header.signature.dimen.w)) {
        free(f);
        return me->status = KMZ_GD_ERR_WRITE_WIDTH;
    }
    if (0 != _kmz_write_short(f, me->header.signature.dimen.h)) {
        free(f);
        return me->status = KMZ_GD_ERR_WRITE_HEIGHT;
    }
    if (0 != _kmz_write_byte(f, me->header.signature.type == KMZ_GD_2X_IMAGE_FILE_TRUECOLOR)) {
        free(f);
        return me->status = KMZ_GD_ERR_WRITE_IS_TRUECOLOR;
    }

    switch (me->header.signature.type) {
        case KMZ_GD_2X_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_write_int(f, me->header.color.value.truecolor.transparent)) {
                free(f);
                return me->status = KMZ_GD_ERR_WRITE_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2X_IMAGE_FILE_PALETTE:
            // TODO: Implement palette image writing
            free(f);
            return me->status = KMZ_GD_ERR_UNSUPPORTED_OPERATION;
    }

    const size_t len = me->header.signature.dimen.w * me->header.signature.dimen.h;
    const size_t is_truecolor = me->header.signature.type == KMZ_GD_2X_IMAGE_FILE_TRUECOLOR;

    if (is_truecolor) {
        if (0 != _kmz_write_int_buffer(f, me->pixels.truecolor, len)) {
            free(f);
            return me->status = KMZ_GD_ERR_WRITE_PIXELS;
        }
    } else {
        if (0 != _kmz_write_byte_buffer(f, me->pixels.palette, len)) {
            free(f);
            return me->status = KMZ_GD_ERR_WRITE_PIXELS;
        }
    }
    free(f);
    return me->status = KMZ_GD_OK;
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__load(KmzGd2xImageFile * const restrict me, const char * const path) {
    FILE * const restrict f = fopen(path, "rb+");
    if (NULL == f) {
        free(f);
        return me->status = KMZ_GD_ERR_INVALID_FILE_PTR;
    }
    if (0 != _kmz_read_short(f, &me->header.signature.type)) {
        free(f);
        return me->status = KMZ_GD_ERR_READ_SIGNATURE;
    }
    if (0 != _kmz_read_short(f, &me->header.signature.dimen.w)) {
        free(f);
        return me->status = KMZ_GD_ERR_READ_WIDTH;
    }
    if (0 != _kmz_read_short(f, &me->header.signature.dimen.h)) {
        free(f);
        return me->status = KMZ_GD_ERR_READ_HEIGHT;
    }
    if (0 != _kmz_read_byte(f, &me->header.color.is_truecolor)) {
        free(f);
        return me->status = KMZ_GD_ERR_READ_IS_TRUECOLOR;
    }

    switch (me->header.signature.type) {
        case KMZ_GD_2X_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_read_int(f, &me->header.color.value.truecolor.transparent)) {
                free(f);
                return me->status = KMZ_GD_ERR_READ_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2X_IMAGE_FILE_PALETTE:
            if (0 != _kmz_read_short(f, &me->header.color.value.palette.count)) {
                free(f);
                return me->status = KMZ_GD_ERR_READ_PALETTE_COUNT;
            }
            if (0 != _kmz_read_int(f, &me->header.color.value.palette.transparent)) {
                free(f);
                return me->status = KMZ_GD_ERR_READ_PALETTE_TRANSPARENT;
            }
            if (0 != _kmz_read_int_buffer(f, me->header.color.value.palette.colors, 256)) {
                free(f);
                return me->status = KMZ_GD_ERR_READ_PALETTE_COLORS;
            }
    }

    const size_t len = me->header.signature.dimen.w * me->header.signature.dimen.h;
    const uint8_t is_truecolor = me->header.signature.type == KMZ_GD_2X_IMAGE_FILE_TRUECOLOR;
    me->header.color.is_truecolor = is_truecolor;

    if (is_truecolor) {
        me->pixels.truecolor = calloc(len, sizeof(kmz_color_32));
        if (NULL == me->pixels.truecolor) {
            free(f);
            return me->status = KMZ_GD_ERR_OUT_OF_MEMORY;
        }
        if (0 != _kmz_read_int_buffer(f, me->pixels.truecolor, len)) {
            free(f);
            return me->status = KMZ_GD_ERR_READ_PIXELS;
        }
    } else {
        me->pixels.palette = calloc(len, sizeof(uint8_t));
        if (NULL == me->pixels.palette) {
            free(f);
            return me->status = KMZ_GD_ERR_OUT_OF_MEMORY;
        }
        if (0 != _kmz_read_byte_buffer(f, me->pixels.palette, len)) {
            free(f);
            return me->status = KMZ_GD_ERR_READ_PIXELS;
        }
    }

    free(f);
    return me->status = KMZ_GD_OK;
}

static const size_t _KmzGd2xImageFile__palette_color_count(const KmzGd2xImageFile * const restrict me) {
    if (KMZ_GD_OK == me->status && KMZ_GD_2X_IMAGE_FILE_PALETTE == me->header.signature.type) {
        return me->header.color.value.palette.count;
    }
    return 0;
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__read_palette_colors(KmzGd2xImageFile * const restrict me, kmz_color_32 * const buffer) {
    if (KMZ_GD_OK == me->status) {
        if (me->header.signature.type != KMZ_GD_2X_IMAGE_FILE_PALETTE) {
            return me->status = (KmzGd2xImageFileStatus)KMZ_IMAGE_FILE_ERR_NOT_PALETTE_IMAGE;
        }
        memcpy(buffer, me->header.color.value.palette.colors, me->header.color.value.palette.count * sizeof(kmz_color_32));
    }
    return me->status;
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__read_palette_pixels(KmzGd2xImageFile * const restrict me, uint8_t * const restrict buffer) {
    if (KMZ_GD_OK == me->status) {
        if (me->header.signature.type != KMZ_GD_2X_IMAGE_FILE_PALETTE) {
            return me->status = (KmzGd2xImageFileStatus)KMZ_IMAGE_FILE_ERR_NOT_PALETTE_IMAGE;
        }
        memcpy(buffer, me->pixels.palette, me->header.signature.dimen.h * me->header.signature.dimen.w * sizeof(uint8_t));
    }
    return me->status;
}

static const KmzGd2xImageFileStatus _KmzGd2xImageFile__read_truecolor_pixels(KmzGd2xImageFile * const restrict me, kmz_color_32 * const restrict buffer) {
    if (KMZ_GD_OK == me->status) {
        if (me->header.signature.type != KMZ_GD_2X_IMAGE_FILE_TRUECOLOR) {
            return me->status = (KmzGd2xImageFileStatus)KMZ_IMAGE_FILE_ERR_NOT_TRUECOLOR_IMAGE;
        }
        memcpy(buffer, me->pixels.truecolor, me->header.signature.dimen.h * me->header.signature.dimen.w * sizeof(kmz_color_32));
    }
    return me->status;
}

const KmzGd2xImageFileStatus _KmzGd2xImageFile__set_palette_image(KmzGd2xImageFile * const restrict me, const size_t color_count,
        kmz_color_32 * const palette, const KmzSize dimen, uint8_t * const pixels, const KmzBool copy_source) {
    if (KMZ_GD_OK == me->status) {
        if (KMZ_TRUE == me->owns_pixels) {
            free(me->pixels.palette);
        }

        me->header.signature.dimen = dimen;
        me->header.signature.type = KMZ_GD_2X_IMAGE_FILE_PALETTE;
        me->header.color.is_truecolor = 0;
        me->header.color.value.palette.count = color_count;
        memcpy(me->header.color.value.palette.colors, palette, color_count * sizeof(kmz_color_32));

        me->owns_pixels = copy_source;
        if (KMZ_TRUE == me->owns_pixels) {
            me->pixels.palette = calloc(dimen.h * dimen.w, sizeof(uint8_t));
            memcpy(me->pixels.palette, pixels, dimen.h * dimen.w * sizeof(uint8_t));
        } else {
            me->pixels.palette = pixels;
        }
    }
    return me->status;
}

const KmzGd2xImageFileStatus _KmzGd2xImageFile__set_truecolor_image(KmzGd2xImageFile * const restrict me, const KmzSize dimen,
        kmz_color_32 * const restrict pixels, const KmzBool copy_source) {
    if (KMZ_GD_OK == me->status) {
        if (KMZ_TRUE == me->owns_pixels) {
            free(me->pixels.palette);
        }

        me->header.signature.dimen = dimen;
        me->header.signature.type = KMZ_GD_2X_IMAGE_FILE_TRUECOLOR;
        me->header.color.is_truecolor = 1;

        me->owns_pixels = copy_source;
        if (KMZ_TRUE == me->owns_pixels) {
            me->pixels.truecolor = calloc(dimen.h * dimen.w , sizeof(kmz_color_32));
            memcpy(me->pixels.truecolor, pixels, dimen.h * dimen.w * sizeof(kmz_color_32));
        } else {
            me->pixels.truecolor = pixels;
        }
    }
    return me->status;
}

const KmzImageFileType kmz_gd_2x_image_file = {
    ._new=(void * const (*)(void))&_KmzGd2xImageFile__new,
    ._ctor=(void (*)(void * const, const void * const))&_KmzGd2xImageFile__ctor,
    ._dtor=(void (*)(void * const))&_KmzGd2xImageFile__dtor,
    .dimen=(const KmzSize (*)(const void * const))&_KmzGd2xImageFile__dimen,
    .color_type=(const KmzImageFileColorType (*)(const void * const))&_KmzGd2xImageFile__color_type,
    .status=(const KmzImageFileStatus (*)(const void * const))&_KmzGd2xImageFile__status,
    .clear_status=(void (*)(void * const))&_KmzGd2xImageFile__clear_status,
    .status_msg=(const char * const (*)(const void * const, const KmzImageFileStatus))&_KmzGd2xImageFile__status_msg,
    .save=(const KmzImageFileStatus (*)(void * const, const char * const))&_KmzGd2xImageFile__save,
    .load=(const KmzImageFileStatus (*)(void * const, const char * const))&_KmzGd2xImageFile__load,
    .palette_color_count=(const size_t (*)(const void * const))&_KmzGd2xImageFile__palette_color_count,
    .read_palette_colors=(const KmzImageFileStatus (*)(void * const, kmz_color_32 * const))&_KmzGd2xImageFile__read_palette_colors,
    .read_palette_pixels=(const KmzImageFileStatus (*)(void * const, uint8_t * const))&_KmzGd2xImageFile__read_palette_pixels,
    .read_truecolor_pixels=(const KmzImageFileStatus (*)(void * const, kmz_color_32 * const))&_KmzGd2xImageFile__read_truecolor_pixels,
    .read_ahsl_pixels=NULL,
    .set_palette_image=(const KmzImageFileStatus (*)(void * const, const size_t, const kmz_color_32 * const, const KmzSize, uint8_t * const, const KmzBool))&_KmzGd2xImageFile__set_palette_image,
    .set_truecolor_image=(const KmzImageFileStatus (*)(void * const, const KmzSize, kmz_color_32 * const, const KmzBool))&_KmzGd2xImageFile__set_truecolor_image,
    .set_ahsl_image=NULL,
    .supports_metadata=NULL,
    .is_supported_metadata=NULL,
    .metadata=NULL,
    .has_metadata=NULL,
    .set_metadata=NULL,
    .remove_metadata=NULL,
};
