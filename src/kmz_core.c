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
#define _kmz__get_index(dimen, point) ((dimen.w * point.y) + point.x)
#define _KmzImage__get_index(me, point) _kmz__get_index(me->dimen, point)
// endregion;

// region Matrix:


extern inline const kmz_color_32 KmzMatrix__get_argb_at(const KmzMatrix * const restrict me, const KmzPoint point) {
    const KmzPoint p = kmz_point((me->pos.x + point.x + (ssize_t)me->hsize), (me->pos.y + point.y + (ssize_t)me->hsize));
    return me->pixels[_kmz__get_index(me->image_dimen, p)];
}

extern inline void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    const KmzPoint p = kmz_point((me->pos.x + point.x + (ssize_t)me->hsize), (me->pos.y + point.y + (ssize_t)me->hsize));
    me->pixels[_kmz__get_index(me->image_dimen, p)] = color;
}

KmzMatrix * const KmzMatrix__new_from_buffer(kmz_color_32 * const restrict buffer, const KmzSize image_dimen, const KmzPoint pos, const size_t size) {
    KmzMatrix * const restrict me = malloc(sizeof(KmzMatrix));
    if (me != NULL) {
        me->pixels = buffer;
        me->image_dimen = image_dimen;
        me->pos = pos;
        me->size = size;
        me->hsize = size / 2;
    }
    return me;
}

// endregion;

// region Imagelike:
extern inline const KmzImageLike KmzImageLike__wrap(const KmzImageLikeVTab * const restrict vt_ref, const kmz_image_ptr ref) {
    return (KmzImageLike) {vt_ref, ref};
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

static inline KmzPixelOperationStatus _KmzImageLike__populate_buffer(const KmzImageLike me, kmz_color_32 * const restrict buffer, KmzRectangle i_area,
                                                                     const KmzSize buffer_size, const KmzSize h_buffer_size, const size_t hsize,
                                                                     const size_t w) {
    const size_t w_m_o = w - 1;
    KmzPixelOperationStatus status = PIXEL_OP_OK;
    KmzPoint b_p = KmzPoint__ZERO;
    KmzBool in_y_border = KMZ_FALSE, in_x_border = KMZ_FALSE;
    size_t b_o = 0;
    i_area.size.h = 1;
    
    // Copy the image into the buffer.
    for (; b_p.y < buffer_size.h; ++b_p.y) {
        in_y_border = (b_p.y < hsize || b_p.y >= h_buffer_size.h);
        for (b_p.x = 0; b_p.x < buffer_size.w; ++b_p.x) {
            in_x_border = (b_p.x < hsize || b_p.x >= h_buffer_size.w);
            
            if (in_y_border || in_x_border) {
                buffer[b_o++] = 0x00000000;
            } else {
                status = KmzImageLike__read_argb_block(me, i_area, buffer + b_o);
                if (status != PIXEL_OP_OK) {
                    return status;
                }
                b_p.x += w_m_o;
                b_o += w;
            }
        }
        if (!in_y_border) {
            ++i_area.pos.y;
        }
    }
    return PIXEL_OP_OK;
}

extern inline KmzPixelOperationStatus KmzImageLike__apply_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter,
                                                                 const KmzRectangle area,
                                               const size_t m_size) {
    return KmzImageLike__apply_buffered_filter(me, argv, filter, area, m_size, me);
}

KmzPixelOperationStatus KmzImageLike__apply_buffered_filter(const KmzImageLike me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                                            const size_t m_size, const KmzImageLike output) {
    const KmzSize dimen = KmzImageLike__get_dimen(me);
    const size_t hsize = m_size / 2;
    const ssize_t x = kmz__clamp(area.pos.x, 0, dimen.w),
                  y = kmz__clamp(area.pos.y, 0, dimen.h),
                  max_x = kmz__clamp(area.size.w + x, x, dimen.w),
                  max_y = kmz__clamp(area.size.h + y, y, dimen.h);
    
    const size_t w = (size_t)(max_x - x),
                 h = (size_t)(max_y - y);
    
    const uint16_t h_w = (uint16_t)(w + hsize),
                   h_h = (uint16_t)(h + hsize),
                   b_w = (uint16_t)(h_w + hsize),
                   b_h = (uint16_t)(h_h + hsize);
    
    kmz_color_32 * const restrict buffer = calloc(b_w * b_h, sizeof(kmz_color_32));
    if (NULL == buffer) {
        return ERR_PIXEL_OP_OUT_OF_MEMORY;
    }
    kmz_color_32 * const restrict o_buffer = calloc(w * h, sizeof(kmz_color_32));
    if (NULL == o_buffer) {
        free(buffer);
        return ERR_PIXEL_OP_OUT_OF_MEMORY;
    }
    
    KmzPixelOperationStatus status = _KmzImageLike__populate_buffer(me, buffer, area, kmz_size(b_w, b_h), kmz_size(h_w, h_h), hsize, w);
    if (status != PIXEL_OP_OK) {
        free(buffer);
        free(o_buffer);
        return status;
    }
    
    KmzMatrix * m = KmzMatrix__new_from_buffer(buffer, kmz_size((uint16_t)b_w, (uint16_t)b_h), kmz_point(0, 0), m_size);
    KmzPoint p = KmzPoint__ZERO;
    size_t o = 0;
    
    if (NULL == m) {
        free(buffer);
        free(o_buffer);
        return ERR_PIXEL_OP_OUT_OF_MEMORY;
    }
    
    for (; p.y < h; ++p.y) {
        for (p.x = 0; p.x < w; ++p.x) {
            m->pos = p;
            o_buffer[o++] = filter(argv, m);
        }
    }
    
    KmzImageLike__write_argb_block(output, area, o_buffer);
    
    // Free the resources.
    free(m);
    free(buffer);
    free(o_buffer);
    
    return PIXEL_OP_OK;
}
// endregion;
