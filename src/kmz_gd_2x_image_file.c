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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "kmz_config.h"
#include "libkempozer.h"

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

const KmzGd2xImageFileStatus kmz_read_gd_2x_image_file(FILE * const restrict f, KmzGd2xImageFile * const restrict o) {
    if (NULL == f) {
        return ERR_INVALID_FILE_PTR;
    } else if (NULL == o) {
        return ERR_INVALID_IMAGE_PTR;
    }
    
    if (0 != _kmz_read_short(f, &o->header.signature.type)) {
        return ERR_READ_SIGNATURE;
    }
    if (0 != _kmz_read_short(f, &o->header.signature.dimen.w)) {
        return ERR_READ_WIDTH;
    }
    if (0 != _kmz_read_short(f, &o->header.signature.dimen.h)) {
        return ERR_READ_HEIGHT;
    }
    if (0 != _kmz_read_byte(f, &o->header.color.is_truecolor)) {
        return ERR_READ_IS_TRUECOLOR;
    }
    
    switch (o->header.signature.type) {
        case KMZ_GD_2x_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_read_int(f, &o->header.color.value.truecolor.transparent)) {
                return ERR_READ_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2x_IMAGE_FILE_PALETTE:
            if (0 != _kmz_read_short(f, &o->header.color.value.palette.count)) {
                return ERR_READ_PALETTE_COUNT;
            }
            if (0 != _kmz_read_int(f, &o->header.color.value.palette.transparent)) {
                return ERR_READ_PALETTE_TRANSPARENT;
            }
            if (0 != _kmz_read_int_buffer(f, o->header.color.value.palette.colors, 256)) {
                return ERR_READ_PALETTE_COLORS;
            }
    }
    
    const size_t len = o->header.signature.dimen.w * o->header.signature.dimen.h;
    const uint8_t is_truecolor = o->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR;
    o->header.color.is_truecolor = is_truecolor;
    
    if (is_truecolor) {
        o->pixels.truecolor = calloc(len, sizeof(kmz_color_32));
        if (NULL == o->pixels.truecolor) {
            return ERR_OUT_OF_MEMORY;
        }
        if (0 != _kmz_read_int_buffer(f, o->pixels.truecolor, len)) {
            return ERR_READ_PIXELS;
        }
    } else {
        o->pixels.palette = calloc(len, sizeof(uint8_t));
        if (NULL == o->pixels.palette) {
            return ERR_OUT_OF_MEMORY;
        }
        if (0 != _kmz_read_byte_buffer(f, o->pixels.palette, len)) {
            return ERR_READ_PIXELS;
        }
    }
    
    return OK;
}


const KmzGd2xImageFileStatus kmz_write_gd_2x_image_file(FILE * const restrict f, const KmzGd2xImageFile * const restrict i) {
    if (NULL == f) {
        return ERR_INVALID_FILE_PTR;
    } else if (NULL == i) {
        return ERR_INVALID_IMAGE_PTR;
    }
    
    if (0 != _kmz_write_short(f, i->header.signature.type)) {
        return ERR_WRITE_SIGNATURE;
    }
    if (0 != _kmz_write_short(f, i->header.signature.dimen.w)) {
        return ERR_WRITE_WIDTH;
    }
    if (0 != _kmz_write_short(f, i->header.signature.dimen.h)) {
        return ERR_WRITE_HEIGHT;
    }
    if (0 != _kmz_write_byte(f, i->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR)) {
        return ERR_WRITE_IS_TRUECOLOR;
    }
    
    switch (i->header.signature.type) {
        case KMZ_GD_2x_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_write_int(f, i->header.color.value.truecolor.transparent)) {
                return ERR_WRITE_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2x_IMAGE_FILE_PALETTE:
            // TODO: Implement palette image writing
            return ERR_UNSUPPORTED_OPERATION;
    }
    
    const size_t len = i->header.signature.dimen.w * i->header.signature.dimen.h;
    const size_t is_truecolor = i->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR;
    
    if (is_truecolor) {
        if (0 != _kmz_write_int_buffer(f, i->pixels.truecolor, len)) {
            return ERR_WRITE_PIXELS;
        }
    } else {
        if (0 != _kmz_write_byte_buffer(f, i->pixels.palette, len)) {
            return ERR_WRITE_PIXELS;
        }
    }
    return OK;
}

const char * kmz_status_msg(const KmzGd2xImageFileStatus status) {
    switch (status) {
        case OK:
            return NULL;
        case ERR_INVALID_FILE_PTR:
            return "An invalid file pointer has been provided";
        case ERR_INVALID_IMAGE_PTR:
            return "An invalid image pointer has been provided";
        case ERR_READ_SIGNATURE:
            return "An error has occurred while reading the GD 2x header signature";
        case ERR_WRITE_SIGNATURE:
            return "An error has occurred while writing the GD 2x header signature";
        case ERR_READ_WIDTH:
            return "An error has occurred while reading the GD 2x header width";
        case ERR_READ_HEIGHT:
            return "An error has occurred while reading the GD 2x header height";
        case ERR_WRITE_WIDTH:
            return "An error has occurred while writing the GD 2x header width";
        case ERR_WRITE_HEIGHT:
            return "An error has occurred while writing the GD 2x header height";
        case ERR_READ_IS_TRUECOLOR:
            return "An error has occurred while reading the GD 2x header truecolor flag";
        case ERR_WRITE_IS_TRUECOLOR:
            return "An error has occurred while writing the GD 2x header truecolor flag";
        case ERR_READ_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header truecolor transparent color";
        case ERR_WRITE_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header truecolor transparent color";
        case ERR_READ_PALETTE_COUNT:
            return "An error has occurred while reading the GD 2x header palette count";
        case ERR_WRITE_PALETTE_COUNT:
            return "An error has occurred while writing the GD 2x header palette count";
        case ERR_READ_PALETTE_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header palette transparent color";
        case ERR_WRITE_PALETTE_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header palette transparent color";
        case ERR_READ_PALETTE_COLORS:
            return "An error has occurred while reading the GD 2x header palette colors";
        case ERR_WRITE_PALETTE_COLORS:
            return "An error has occurred while writing the GD 2x header palette colors";
        case ERR_READ_PIXELS:
            return "An error has occurred while reading the GD 2x pixels";
        case ERR_WRITE_PIXELS:
            return "An error has occurred while writing the GD 2x pixels";
        case ERR_UNSUPPORTED_OPERATION:
            return "An unsupported operation has been encountered";
        case ERR_OUT_OF_MEMORY:
            return "System is out of memory";
        case ERR_UNKNOWN:
            return "An unknown error has occurred";
    }
}

const char * kmz_status_msg_with_err_code(const KmzGd2xImageFileStatus status, const int error) {
    const char * msg = kmz_status_msg(status);
    char * o = calloc(strlen(msg) + 24, sizeof(char));
    sprintf(o, "%s: %d", msg, error);
    return o;
}
