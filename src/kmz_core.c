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


#include "kmz_core.h"

// region Helpers:
#define _KmzImage__get_index(me, point) ((me->dimen.w * point.y) + point.x)
// endregion;

// region Matrix:
#define _KmzMatrix__clamp_point(me, point, dimen) \
(kmz_point(kmz__clamp(me->pos.x + (point.x - (ssize_t)me->hsize), 0, dimen.w - 1), \
           kmz__clamp(me->pos.y + (point.y - (ssize_t)me->hsize), 0, dimen.h - 1)))

extern inline const kmz_color_32 KmzMatrix__get_argb_at(const KmzMatrix * const restrict me, const KmzPoint point) {
    return KmzImageLike__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image_dimen));
}

extern inline void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    KmzImageLike__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image_dimen), color);
}

KmzMatrix * const KmzMatrix__new_from_image_like(const KmzImageLike image, const KmzPoint point, const size_t size) {
    KmzMatrix * const me = malloc(sizeof(KmzMatrix));
    me->image = image;
    me->pos = point;
    me->size = size;
    me->hsize = me->size / 2;
    return me;
}

// endregion;

// region Imagelike:
extern inline const KmzImageLike KmzImageLike__wrap(const KmzImageLikeVTab * const restrict vt_ref, const kmz_image_ptr ref) {
    return (KmzImageLike) {._vt = vt_ref, ._me = ref};
}

extern inline const KmzSize KmzImageLike__get_dimen(const KmzImageLike me) {
    return me._vt->get_dimen(me._me);
}

extern inline const kmz_color_32 KmzImageLike__get_argb_at(const KmzImageLike me, const KmzPoint point) {
    return me._vt->get_argb_at(me._me, point);
}

extern inline void KmzImageLike__set_argb_at(const KmzImageLike me, const KmzPoint point, const kmz_color_32 color) {
    me._vt->set_argb_at(me._me, point, color);
}

const KmzPixelOperationStatus KmzImageLike__read_argb_block(const KmzImageLike me, const KmzRectangle src_area, kmz_color_32 * const restrict dst) {
    if (me._vt->read_argb_block) {
        return me._vt->read_argb_block(me._me, src_area, dst);
    }
    
    const KmzSize dimen = KmzImageLike__get_dimen(me);
    const ssize_t max_y = src_area.size.h + src_area.pos.y, max_x = src_area.size.w + src_area.pos.x;
    
    if (src_area.pos.x < 0 || src_area.pos.x >= dimen.w || src_area.pos.y < 0 || src_area.pos.y >= dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_POS;
    } else if (max_x > dimen.w || max_y > dimen.h) {
        return ERR_PIXEL_OP_READ_INVALID_SIZE;
    } else if (NULL == dst) {
        return ERR_PIXEL_OP_READ_INVALID_PTR;
    }
    KmzPoint p = src_area.pos;
    for (size_t o = 0; p.y < max_y; ++p.y) {
        for (p.x = src_area.pos.x; p.x < max_x; ++p.x) {
            dst[o++] = KmzImageLike__get_argb_at(me, p);
        }
    }
    
    return PIXEL_OP_OK;
}

const KmzPixelOperationStatus KmzImageLike__write_argb_block(const KmzImageLike me, const KmzRectangle dst_area, const kmz_color_32 * const restrict src) {
    if (me._vt->write_argb_block) {
        return me._vt->write_argb_block(me._me, dst_area, src);
    }
    
    const KmzSize dimen = KmzImageLike__get_dimen(me);
    const ssize_t max_y = dst_area.size.h + dst_area.pos.y, max_x = dst_area.size.w + dst_area.pos.x;
    
    if (dst_area.pos.x < 0 || dst_area.pos.x >= dimen.w || dst_area.pos.y < 0 || dst_area.pos.y >= dimen.h) {
        return ERR_PIXEL_OP_WRITE_INVALID_POS;
    } else if (max_x > dimen.w || max_y > dimen.h) {
        return ERR_PIXEL_OP_WRITE_INVALID_SIZE;
    } else if (NULL == src) {
        return ERR_PIXEL_OP_WRITE_INVALID_PTR;
    }
    KmzPoint p = dst_area.pos;
    for (size_t o = 0; p.y < max_y; ++p.y) {
        for (p.x = dst_area.pos.x; p.x < max_x; ++p.x) {
            KmzImageLike__set_argb_at(me, p, src[o++]);
        }
    }
    
    return PIXEL_OP_OK;
}

extern inline const KmzBool KmzImageLike__is_valid(const KmzImageLike me, const KmzPoint point) {
    return me._vt->is_valid(me._me, point);
}

extern inline KmzMatrix * const KmzImageLike__get_matrix_at(const KmzImageLike me, const KmzPoint point, const size_t size) {
    return KmzMatrix__new_from_image_like(me, point, size);
}

extern inline void KKmzImageLike__apply_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                               const size_t m_size) {
    KmzImageLike__apply_buffered_filter(me, argv, filter, area, m_size, me);
}

void KmzImageLike__apply_buffered_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                         const size_t m_size, const KmzImageLike buffer) {
    const KmzSize dimen = KmzImageLike__get_dimen(me);
    const ssize_t x = kmz__clamp(area.pos.x, 0, dimen.w),
                  y = kmz__clamp(area.pos.y, 0, dimen.h),
                  max_x = kmz__clamp(area.size.w + x, x, dimen.w),
                  max_y = kmz__clamp(area.size.h + y, y, dimen.h);
    
    KmzMatrix * const restrict matrix = KmzImageLike__get_matrix_at(me, KmzPoint__ZERO, m_size);
    matrix->image_dimen = dimen;
    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            KmzImageLike__set_argb_at(buffer, matrix->pos, filter(argv, matrix));
        }
    }
    free(matrix);
}
// endregion;
