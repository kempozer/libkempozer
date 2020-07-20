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
#include <string.h>
#include "kmz_config.h"
#include "libkempozer.h"

#define _KmzImage__get_index(me, point) ((me->dimen.w * point.y) + point.x)
#define _KmzImage__get_offset(p, s) ((size_t)((p.y * s.w) + p.x))
#define _KmzImage__get_len(p, s) ((size_t)((s.h - p.y) * s.w))

struct _kmz_image_t {
    KmzSize dimen;
    size_t len;
    KmzBool owns_buffer;
    kmz_color_32 * pixels;
};

struct _kmz_image_argv_t {
    KmzSize dimen;
    kmz_color_32 * pixels;
    KmzBool copy_source;
};

KmzImagePtr KmzImage__new_from_gd_2x(const KmzGd2xImageFile * const restrict image) {
    if (image->header.color.is_truecolor) {
        struct _kmz_image_argv_t argv = {image->header.signature.dimen, image->pixels.truecolor, KMZ_TRUE};
        return KmzImage__new(&kmz_image, &argv);
    }
    return NULL;
}

KmzImagePtr KmzImage__new_from_buffer(const KmzSize dimen, kmz_color_32 * const restrict buffer, const KmzBool copy_source) {
    struct _kmz_image_argv_t argv = {dimen, buffer, copy_source};
    return KmzImage__new(&kmz_image, &argv);
}

static struct _kmz_image_t * const _KmzImage__new(void) {
    struct _kmz_image_t * const restrict me = malloc(sizeof(struct _kmz_image_t));
    
    if (NULL != me) {
        me->dimen = KmzSize__ZERO;
        me->len = 0;
        me->pixels = NULL;
    }
    
    return me;
}

static void _KmzImage__ctor(struct _kmz_image_t * const restrict me, const struct _kmz_image_argv_t * const restrict args) {
    me->dimen = args->dimen;
    me->len = args->dimen.h * args->dimen.w;
    if (args->copy_source) {
        me->owns_buffer = KMZ_TRUE;
        me->pixels = calloc(me->len, sizeof(kmz_color_32));
        if (NULL == me->pixels) {
            // TODO: Add error state
            return;
        }
        memcpy(me->pixels, args->pixels, me->len * sizeof(kmz_color_32));
    } else {
        me->owns_buffer = KMZ_FALSE;
        me->pixels = args->pixels;
    }
}

static void _KmzImage__dtor(struct _kmz_image_t * const restrict me) {
    if (me->owns_buffer) {
        free(me->pixels);
    }
    free(me);
}

static const KmzSize _KmzImage__dimen(const struct _kmz_image_t * const restrict me) {
    return me->dimen;
}

static const kmz_color_32 _KmzImage__argb_at(const struct _kmz_image_t * const restrict me, const KmzPoint point) {
    return me->pixels[_KmzImage__get_index(me, point)];
}

static void _KmzImage__set_argb_at(struct _kmz_image_t * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    me->pixels[_KmzImage__get_index(me, point)] = color;
}

static const KmzPixelOperationStatus _KmzImage__read_argb_block(const struct _kmz_image_t * const restrict me, const KmzRectangle src_area,
                                                                kmz_color_32 * const restrict dst) {
    if (src_area.pos.x < 0 || src_area.pos.x >= me->dimen.w || src_area.pos.y < 0 || src_area.pos.y >= me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_POS;
    } else if ((src_area.size.w + src_area.pos.x) > me->dimen.w || (src_area.size.h + src_area.pos.y) > me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_SIZE;
    } else if (NULL == dst) {
        return ERR_PIXEL_OP_READ_INVALID_PTR;
    }
    
    if (0 == src_area.pos.x && 0 == src_area.pos.y && src_area.size.w == me->dimen.w && src_area.size.h == me->dimen.h) {
        memcpy(dst, me->pixels, me->len * sizeof(kmz_color_32));
    } else {
        size_t src_len = src_area.size.w * sizeof(kmz_color_32),
               src_offset = _KmzImage__get_offset(src_area.pos, me->dimen);
            
        size_t src_line = (size_t)src_area.pos.y, src_end = (size_t)src_area.pos.y + src_area.size.h, dst_offset = 0;
        while (src_line < src_end) {
            memcpy(dst + dst_offset, me->pixels + src_offset, src_len);
            src_offset += me->dimen.w;
            dst_offset += src_area.size.w;
            ++src_line;
        }
    }
    
    return PIXEL_OP_OK;
}

static const KmzPixelOperationStatus _KmzImage__write_argb_block(struct _kmz_image_t * const restrict me, const KmzRectangle dst_area,
                                                                const kmz_color_32 * const restrict src) {
    if (dst_area.pos.x < 0 || dst_area.pos.x >= me->dimen.w || dst_area.pos.y < 0 || dst_area.pos.y >= me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_POS;
    } else if ((dst_area.size.w + dst_area.pos.x) > me->dimen.w || (dst_area.size.h + dst_area.pos.y) > me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_SIZE;
    } else if (NULL == src) {
        return ERR_PIXEL_OP_READ_INVALID_PTR;
    }
    
    if (0 == dst_area.pos.x && 0 == dst_area.pos.y && dst_area.size.w == me->dimen.w && dst_area.size.h == me->dimen.h) {
        memcpy(me->pixels, src, me->len * sizeof(kmz_color_32));
    } else {
        size_t dst_len = dst_area.size.w * sizeof(kmz_color_32),
               dst_offset = _KmzImage__get_offset(dst_area.pos, me->dimen);
            
        size_t dst_line = (size_t)dst_area.pos.y, dst_end = (size_t)dst_area.pos.y + dst_area.size.h, src_offset = 0;
        while (dst_line < dst_end) {
            memcpy(me->pixels + dst_offset, src + src_offset, dst_len);
            dst_offset += me->dimen.w;
            src_offset += dst_area.size.w;
            ++dst_line;
        }
    }
    
    return PIXEL_OP_OK;
}

static const KmzBool _KmzImage__is_valid(const struct _kmz_image_t * const restrict me, const KmzPoint point) {
    return (me->dimen.w > point.x && point.x > -1 && me->dimen.h > point.y && point.y > -1);
}

const KmzImageType kmz_image = {
    ._new=(void * const (*)(void))&_KmzImage__new,
    ._ctor=(void (*)(void * const restrict, const void * const restrict))&_KmzImage__ctor,
    ._dtor=(void (*)(void * const restrict))&_KmzImage__dtor,
    .dimen=(const KmzSize (*)(const kmz_image_ptr))&_KmzImage__dimen,
    .argb_at=(const kmz_color_32 (*)(const kmz_image_ptr, const KmzPoint))&_KmzImage__argb_at,
    .set_argb_at=(void (*)(kmz_image_ptr, const KmzPoint, const kmz_color_32))&_KmzImage__set_argb_at,
    .is_valid=(const KmzBool (*)(const kmz_image_ptr, const KmzPoint))&_KmzImage__is_valid,
    .read_argb_block=(const KmzPixelOperationStatus (*)(const kmz_image_ptr, const KmzRectangle, kmz_color_32 * const restrict))&_KmzImage__read_argb_block,
    .write_argb_block=(const KmzPixelOperationStatus (*)(kmz_image_ptr, const KmzRectangle, const kmz_color_32 * const restrict))&_KmzImage__write_argb_block
};
