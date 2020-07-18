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

#include "kmz_image.h"

// region Image:
#define _KmzImage__get_index(me, point) ((me->dimen.w * point.y) + point.x)

#define _KmzMatrix__clamp_point(me, point, dimen) \
(kmz_point(kmz__clamp(me->pos.x + (point.x - (ssize_t)me->hsize), 0, dimen.w - 1), \
           kmz__clamp(me->pos.y + (point.y - (ssize_t)me->hsize), 0, dimen.h - 1)))

extern inline const KmzSize _KmzImage__get_dimen(const KmzImage * const restrict me) {
    return me->dimen;
}

const KmzImageLike KmzImage__to_image_like(KmzImage * const restrict me) {
    static const KmzImageLikeVTab vt = {
        .get_dimen=(const KmzSize (*)(const kmz_image_ptr))&_KmzImage__get_dimen,
        .get_argb_at=(const kmz_color_32 (*)(const kmz_image_ptr, const KmzPoint))&KmzImage__get_argb_at,
        .set_argb_at=(void (*)(kmz_image_ptr, const KmzPoint, const kmz_color_32))&KmzImage__set_argb_at,
        .is_valid=(const KmzBool (*)(const kmz_image_ptr, const KmzPoint))&KmzImage__is_valid,
        .read_argb_block=(const KmzPixelOperationStatus (*)(const kmz_image_ptr, const KmzRectangle, kmz_color_32 * const restrict))&KmzImage__read_argb_block,
        .write_argb_block=(const KmzPixelOperationStatus (*)(kmz_image_ptr, const KmzRectangle, const kmz_color_32 * const restrict))&KmzImage__write_argb_block
    };
    return KmzImageLike__wrap(&vt, me);
}

extern inline const kmz_color_32 KmzImage__get_argb_at(const KmzImage * const restrict me, const KmzPoint point) {
    return me->pixels[_KmzImage__get_index(me, point)];
}

extern inline void KmzImage__set_argb_at(KmzImage * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    me->pixels[_KmzImage__get_index(me, point)] = color;
}

#define _KmzImage__get_offset(p, s) ((size_t)((p.y * s.w) + p.x))
#define _KmzImage__get_len(p, s) ((size_t)((s.h - p.y) * s.w))

const KmzPixelOperationStatus KmzImage__read_argb_block(const KmzImage * const restrict me, const KmzRectangle src_area, kmz_color_32 * const restrict dst) {
    if (src_area.pos.x < 0 || src_area.pos.x >= me->dimen.w || src_area.pos.y < 0 || src_area.pos.y >= me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_POS;
    } else if ((src_area.size.w + src_area.pos.x) > me->dimen.w || (src_area.size.h + src_area.pos.y) > me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_SIZE;
    } else if (NULL == dst) {
        return ERR_PIXEL_OP_READ_INVALID_PTR;
    }
    
    size_t src_len = 0, src_offset = 0;
    if (0 == src_area.pos.x) {
        if (0 == src_area.pos.y && src_area.size.h == me->dimen.h && src_area.size.w == me->dimen.w) {
            src_len = me->len;
        } else if (src_area.size.w == me->dimen.w) {
            src_len = _KmzImage__get_len(src_area.pos, src_area.size);
            src_offset = _KmzImage__get_offset(src_area.pos, src_area.size);
        }
    }
    
    if (src_len) {
        memcpy(dst, me->pixels + src_offset, src_len * sizeof(kmz_color_32));
    } else {
        src_len = src_area.size.w * sizeof(kmz_color_32);
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

const KmzPixelOperationStatus KmzImage__write_argb_block(KmzImage * const restrict me, const KmzRectangle dst_area,
                                                         const kmz_color_32 * const restrict src) {
    if (dst_area.pos.x < 0 || dst_area.pos.x >= me->dimen.w || dst_area.pos.y < 0 || dst_area.pos.y >= me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_POS;
    } else if ((dst_area.size.w + dst_area.pos.x) > me->dimen.w || (dst_area.size.h + dst_area.pos.y) > me->dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_SIZE;
    } else if (NULL == src) {
        return ERR_PIXEL_OP_READ_INVALID_PTR;
    }
    
    size_t dst_len = 0, dst_offset = 0;
    if (0 == dst_area.pos.x) {
        if (0 == dst_area.pos.y && dst_area.size.h == me->dimen.h && dst_area.size.w == me->dimen.w) {
            dst_len = me->len;
        } else if (dst_area.size.w == me->dimen.w) {
            dst_len = _KmzImage__get_len(dst_area.pos, dst_area.size);
            dst_offset = _KmzImage__get_offset(dst_area.pos, dst_area.size);
        }
    }
    
    if (dst_len) {
        memcpy(me->pixels + dst_offset, src, dst_len * sizeof(kmz_color_32));
    } else {
        dst_len = dst_area.size.w * sizeof(kmz_color_32);
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

extern inline KmzImageMatrix * const KmzImage__get_matrix_at(KmzImage * const restrict me, const KmzPoint point, const size_t size) {
    return KmzImageMatrix__new_from_image(me, point, size);
}

extern inline const KmzBool KmzImage__is_valid(const KmzImage * const restrict me, const KmzPoint point) {
    return (me->dimen.w > point.x && point.x > -1 && me->dimen.h > point.y && point.y > -1);
}

static inline void _KmzImage__populate_from_gd_2x(KmzImage * const restrict me, const KmzGd2xImageFile * const restrict image) {
    me->dimen = image->header.signature.dimen;
    me->len = me->dimen.h * me->dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    memcpy(me->pixels, image->pixels, me->len * sizeof(kmz_color_32));
}

KmzImage * const KmzImage__new_from_gd_2x(const KmzGd2xImageFile * const restrict image) {
    KmzImage * const restrict me = malloc(sizeof(KmzImage));
    _KmzImage__populate_from_gd_2x(me, image);
    return me;
}

KmzImage * const KmzImage__new_from_buffer(const KmzSize dimen, const kmz_color_32 * const restrict pixels) {
    KmzImage * const restrict me = malloc(sizeof(KmzImage));
    me->dimen = dimen;
    me->len = dimen.h * dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    memcpy(me->pixels, pixels, me->len * sizeof(kmz_color_32));
    return me;
}
// endregion;

// region Filtering:
extern inline const kmz_color_32 KmzImageMatrix__get_argb_at(const KmzImageMatrix * const restrict me, const KmzPoint point) {
    return KmzImage__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image->dimen));
}

extern inline void KmzImageMatrix__set_argb_at(KmzImageMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    KmzImage__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image->dimen), color);
}

KmzImageMatrix * const KmzImageMatrix__new_from_image(KmzImage * const restrict image, const KmzPoint point, const size_t size) {
    KmzImageMatrix * const restrict me = malloc(sizeof(KmzImageMatrix));
    me->image = image;
    me->pos = point;
    me->size = size;
    me->hsize = me->size / 2;
    return me;
}

void KmzImage__apply_filter(KmzImage * const restrict me, kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                            const size_t m_size) {
    const ssize_t x = kmz__clamp(area.pos.x, 0, me->dimen.w),
                  y = kmz__clamp(area.pos.y, 0, me->dimen.h),
                  max_x = kmz__clamp(area.size.w + x, x, me->dimen.w),
                  max_y = kmz__clamp(area.size.h + y, y, me->dimen.h);
    
    KmzImageMatrix * const restrict matrix = KmzImage__get_matrix_at(me, KmzPoint__ZERO, m_size);
    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            KmzImage__set_argb_at(me, matrix->pos, filter(argv, matrix));
        }
    }
    free(matrix);
}

void KmzImage__apply_buffered_filter(KmzImage * const restrict me, kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                                     const size_t m_size, KmzImage * const restrict buffer) {
    const ssize_t x = kmz__clamp(area.pos.x, 0, me->dimen.w),
                  y = kmz__clamp(area.pos.y, 0, me->dimen.h),
                  max_x = kmz__clamp(area.size.w + x, x, me->dimen.w),
                  max_y = kmz__clamp(area.size.h + y, y, me->dimen.h);
    
    KmzImageMatrix * const restrict matrix = KmzImage__get_matrix_at(me, KmzPoint__ZERO, m_size);
    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            KmzImage__set_argb_at(buffer, matrix->pos, filter(argv, matrix));
        }
    }
    free(matrix);
}
// endregion;
