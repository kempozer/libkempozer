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
#include "kmz_config.h"
#include "libkempozer.h"

#define _kmz__get_index(dimen, point) ((dimen.w * point.y) + point.x)

struct kmz_image_like_t {
    const KmzImageType * _type;
    kmz_image_ptr _me;
};

struct kmz_matrix_t  {
    size_t _size;
    size_t _hsize;
    KmzPoint _pos;
    KmzSize _image_dimen;
    kmz_color_32 * _pixels;
};

const size_t KmzMatrix__size(const KmzMatrix * const restrict me) {
    return me->_size;
}

const size_t KmzMatrix__hsize(const KmzMatrix * const restrict me) {
    return me->_hsize;
}

const KmzPoint KmzMatrix__pos(const KmzMatrix * const restrict me) {
    return me->_pos;
}

void KmzMatrix__set_pos(KmzMatrix * const restrict me, const KmzPoint pos) {
    me->_pos = pos;
}

const kmz_color_32 KmzMatrix__argb_at(const KmzMatrix * const restrict me, const KmzPoint point) {
    const KmzPoint p = kmz_point((me->_pos.x + point.x + (ssize_t)me->_hsize), (me->_pos.y + point.y + (ssize_t)me->_hsize));
    return me->_pixels[_kmz__get_index(me->_image_dimen, p)];
}

void KmzMatrix__set_argb_at(KmzMatrix * const restrict me, const KmzPoint point, const kmz_color_32 color) {
    const KmzPoint p = kmz_point((me->_pos.x + point.x + (ssize_t)me->_hsize), (me->_pos.y + point.y + (ssize_t)me->_hsize));
    me->_pixels[_kmz__get_index(me->_image_dimen, p)] = color;
}

KmzMatrix * const KmzMatrix__new_from_buffer(kmz_color_32 * const restrict buffer, const KmzSize image_dimen, const KmzPoint pos, const size_t size) {
    KmzMatrix * const restrict me = malloc(sizeof(KmzMatrix));
    if (me != NULL) {
        me->_pixels = buffer;
        me->_image_dimen = image_dimen;
        me->_pos = pos;
        me->_size = size;
        me->_hsize = size / 2;
    }
    return me;
}

const KmzImagePtr KmzImage__new(const KmzImageType * const restrict type, kmz_arg_ptr argv) {
    KmzImagePtr ptr = malloc(sizeof(struct kmz_image_like_t));
    if (NULL == ptr) {
        return NULL;
    }
    
    ptr->_type = type;
    ptr->_me = ptr->_type->_new();
    if (NULL == ptr->_me) {
        free(ptr);
        return NULL;
    }
    
    if (ptr->_type->_ctor) {
        ptr->_type->_ctor(ptr->_me, argv);
    }
    
    return ptr;
}

void KmzImage__free(KmzImagePtr me) {
    if (NULL == me->_type->_dtor) {
        free(me->_me);
    } else {
        me->_type->_dtor(me->_me);
    }
    free(me);
}

const KmzImageType * const KmzImage__type(const KmzImagePtr me) {
    return me->_type;
}

const KmzSize KmzImage__dimen(const KmzImagePtr me) {
    return me->_type->dimen(me->_me);
}

const kmz_color_32 KmzImage__argb_at(const KmzImagePtr me, const KmzPoint point) {
    return me->_type->argb_at(me->_me, point);
}

void KmzImage__set_argb_at(const KmzImagePtr me, const KmzPoint point, const kmz_color_32 color) {
    me->_type->set_argb_at(me->_me, point, color);
}

const KmzPixelOperationStatus KmzImage__read_argb_block(const KmzImagePtr me, const KmzRectangle src_area, kmz_color_32 * const restrict dst) {
    if (me->_type->read_argb_block) {
        return me->_type->read_argb_block(me->_me, src_area, dst);
    }
    
    const KmzSize dimen = KmzImage__dimen(me);
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
            dst[o++] = KmzImage__argb_at(me, p);
        }
    }
    
    return PIXEL_OP_OK;
}

const KmzPixelOperationStatus KmzImage__write_argb_block(const KmzImagePtr me, const KmzRectangle dst_area, const kmz_color_32 * const restrict src) {
    if (me->_type->write_argb_block) {
        return me->_type->write_argb_block(me->_me, dst_area, src);
    }
    
    const KmzSize dimen = KmzImage__dimen(me);
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
            KmzImage__set_argb_at(me, p, src[o++]);
        }
    }
    
    return PIXEL_OP_OK;
}

const KmzBool KmzImage__is_valid(const KmzImagePtr me, const KmzPoint point) {
    return me->_type->is_valid(me->_me, point);
}

static inline KmzPixelOperationStatus _KmzImageLike__populate_buffer(const KmzImagePtr me, kmz_color_32 * const restrict buffer, KmzRectangle i_area,
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
                status = KmzImage__read_argb_block(me, i_area, buffer + b_o);
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

extern inline KmzPixelOperationStatus KmzImage__apply_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter,
                                                                 const KmzRectangle area, const size_t m_size) {
    return KmzImage__apply_buffered_filter(me, argv, filter, area, m_size, me);
}

KmzPixelOperationStatus KmzImage__apply_buffered_filter(const KmzImagePtr me, const kmz_arg_ptr argv, const KmzFilter filter, const KmzRectangle area,
                                                        const size_t m_size, const KmzImagePtr output) {
    const KmzSize dimen = KmzImage__dimen(me);
    const size_t hsize = m_size / 2;
    const ssize_t x = kmz_clamp(area.pos.x, 0, dimen.w),
                  y = kmz_clamp(area.pos.y, 0, dimen.h),
                  max_x = kmz_clamp(area.size.w + x, x, dimen.w),
                  max_y = kmz_clamp(area.size.h + y, y, dimen.h);
    
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
            m->_pos = p;
            o_buffer[o++] = filter(argv, m);
        }
    }
    
    KmzImage__write_argb_block(output, area, o_buffer);
    
    // Free the resources.
    free(m);
    free(buffer);
    free(o_buffer);
    
    return PIXEL_OP_OK;
}
