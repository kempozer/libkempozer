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
static inline const size_t _KmzImage__get_index(const KmzImage * const restrict me, const KmzPoint point) {
    return ((me->dimen.w * point.y) + point.x);
}
// endregion;

// region Image:
const KmzSize _KmzImage__get_dimen(const KmzImage * const restrict me) {
    return me->dimen;
}

const KmzImageLike KmzImage__to_image_like(KmzImage * const restrict me) {
    static const KmzImageLikeVTab vt = {
        .get_dimen=(const KmzSize (*)(const kmz_image_ptr))&_KmzImage__get_dimen,
        .get_argb_at=(const kmz_color_32 (*)(const kmz_image_ptr, const KmzPoint))&KmzImage__get_argb_at,
        .set_argb_at=(void (*)(kmz_image_ptr, const KmzPoint, const kmz_color_32))&KmzImage__set_argb_at,
        .is_valid=(const KmzBool (*)(const kmz_image_ptr, const KmzPoint))&KmzImage__is_valid
    };
    return KmzImageLike__wrap(&vt, me);
}

const kmz_color_32 KmzImage__get_argb_at(const KmzImage * const restrict me, const KmzPoint point) {
    return me->pixels[_KmzImage__get_index(me, point)];
}

void KmzImage__set_argb_at(KmzImage * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    me->pixels[_KmzImage__get_index(me, point)] = color;
}

KmzImageMatrix * const restrict KmzImage__get_matrix_at(KmzImage * const restrict me, const KmzPoint point, const size_t size) {
    return KmzImageMatrix__new_from_image(me, point, size);
}

const KmzBool KmzImage__is_valid(const KmzImage * const restrict me, const KmzPoint point) {
    return (me->dimen.w > point.x && point.x > -1 && me->dimen.h > point.y && point.y > -1);
}

static inline void _KmzImage__populate_from_gd_2x(KmzImage * const restrict me, const KmzGd2xImageFile * const restrict image) {
    me->dimen = image->header.signature.dimen;
    me->len = me->dimen.h * me->dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    memcpy(me->pixels, image->pixels, me->len * sizeof(kmz_color_32));
}

KmzImage * const restrict KmzImage__new_from_gd_2x(const KmzGd2xImageFile * const restrict image) {
    KmzImage * me = malloc(sizeof(KmzImage));
    _KmzImage__populate_from_gd_2x(me, image);
    return me;
}

KmzImage * const restrict KmzImage__new_from_buffer(const KmzSize dimen, const kmz_color_32 * const restrict pixels) {
    KmzImage * const me = malloc(sizeof(KmzImage));
    me->dimen = dimen;
    me->len = dimen.h * dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    memcpy(me->pixels, pixels, me->len * sizeof(kmz_color_32));
    return me;
}
// endregion;

// region Matrix:
#define _KmzMatrix__clamp_point(me, point, dimen) \
(kmz_point(kmz__clamp(me->pos.x + (point.x - me->hsize), 0, dimen.w - 1), \
           kmz__clamp(me->pos.y + (point.y - me->hsize), 0, dimen.h - 1)))

const kmz_color_32 KmzMatrix__get_argb_at(const KmzMatrix * const restrict me, const KmzPoint point) {
    return KmzImageLike__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image_dimen));
}

void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    KmzImageLike__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image_dimen), color);
}

KmzMatrix * const restrict KmzMatrix__new_from_image_like(const KmzImageLike image, const KmzPoint point, const size_t size) {
    KmzMatrix * const me = malloc(sizeof(KmzMatrix));
    me->image = image;
    me->pos = point;
    me->size = size;
    me->hsize = me->size / 2;
    return me;
}

// endregion;

// region Filtering:
const kmz_color_32 KmzImageMatrix__get_argb_at(const KmzImageMatrix * const restrict me, const KmzPoint point) {
    return KmzImage__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image->dimen));
}

void KmzImageMatrix__set_argb_at(KmzImageMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    KmzImage__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point, me->image->dimen), color);
}

KmzImageMatrix * const restrict KmzImageMatrix__new_from_image(KmzImage * const restrict image, const KmzPoint point, const size_t size) {
    KmzImageMatrix * const me = malloc(sizeof(KmzImageMatrix));
    me->image = image;
    me->pos = point;
    me->size = size;
    me->hsize = me->size / 2;
    return me;
}

void KmzImage__apply_filter(KmzImage * const restrict me, kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                            const size_t m_size) {
    KmzImage__apply_buffered_filter(me, argv, filter, area, m_size, me);
}

void KmzImage__apply_buffered_filter(KmzImage * const restrict me, kmz_arg_ptr argv, const KmzImageFilter filter, const KmzRectangle area,
                                     const size_t m_size, KmzImage * const restrict buffer) {
    const size_t x = kmz__clamp(area.pos.x, 0, me->dimen.w),
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

// region Imagelike:
const KmzImageLike KmzImageLike__wrap(const KmzImageLikeVTab * const restrict vt_ref, const kmz_image_ptr ref) {
    return (KmzImageLike) {._vt = vt_ref, ._me = ref};
}

const KmzSize KmzImageLike__get_dimen(const KmzImageLike me) {
    return me._vt->get_dimen(me._me);
}

const kmz_color_32 KmzImageLike__get_argb_at(const KmzImageLike me, const KmzPoint point) {
    return me._vt->get_argb_at(me._me, point);
}

void KmzImageLike__set_argb_at(const KmzImageLike me, const KmzPoint point, const kmz_color_32 color) {
    me._vt->set_argb_at(me._me, point, color);
}

const KmzBool KmzImageLike__is_valid(const KmzImageLike me, const KmzPoint point) {
    return me._vt->is_valid(me._me, point);
}

KmzMatrix * const restrict KmzImageLike__get_matrix_at(const KmzImageLike me, const KmzPoint point, const size_t size) {
    return KmzMatrix__new_from_image_like(me, point, size);
}

void KKmzImageLike__apply_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area, const size_t m_size) {
    KmzImageLike__apply_buffered_filter(me, argv, filter, area, m_size, me);
}

void KmzImageLike__apply_buffered_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                         const size_t m_size, const KmzImageLike buffer) {
    const KmzSize dimen = KmzImageLike__get_dimen(me);
    const size_t x = kmz__clamp(area.pos.x, 0, dimen.w),
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
