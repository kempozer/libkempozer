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

#if __STDC_VERSION__ == 201112L
#ifndef kmz_experimental_h
#define kmz_experimental_h

#include "kmz_core.h"
#include "kmz_color.h"

/**
 * All macros implemented within this namespace may be removed or changed in future versions of the API without prior warning or notice.
 *
 * Experimental syntax, such as _Generic usage, should *always* be placed within this header.
 */

#define kmzexp__get_argb_at(me, point) _Generic((me), \
KmzImage *: KmzImage__get_argb_at, \
KmzImageLike: KmzImageLike__get_argb_at, \
KmzMatrix *: KmzMatrix__get_argb_at, \
KmzImageMatrix *: KmzImageMatrix__get_argb_at)(me, point)

#define kmzexp__get_argb_at_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__get_argb_at_x_y, \
KmzImageLike: KmzImageLike__get_argb_at_x_y, \
KmzMatrix *: KmzMatrix__get_argb_at_x_y, \
KmzImageMatrix *: KmzImageMatrix__get_argb_at_x_y)(me, x, y)

#define kmzexp__set_argb_at(me, point, color) _Generic((me), \
KmzImage *: KmzImage__set_argb_at, \
KmzImageLike: KmzImageLike__set_argb_at, \
KmzMatrix *: KmzMatrix__set_argb_at, \
KmzImageMatrix *: KmzImageMatrix__set_argb_at)(me, point, color)

#define kmzexp__set_argb_at_x_y(me, x, y, color) _Generic((me), \
KmzImage *: KmzImage__set_argb_at_x_y, \
KmzImageLike: KmzImageLike__set_argb_at_x_y, \
KmzMatrix *: KmzMatrix__set_argb_at_x_y, \
KmzImageMatrix *: KmzImageMatrix__set_argb_at_x_y)(me, x, y, color)

#define kmzexp__is_valid(me, point) _Generic((me), \
KmzImage *: KmzImage__is_valid, \
KmzImageLike: KmzImageLike__is_valid)(me, point)

#define kmzexp__is_valid_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__is_valid_x_y, \
KmzImageLike: KmzImageLike__is_valid_x_y)(me, x, y)

#define kmzexp__get_matrix_at(me, point) _Generic((me), \
KmzImage *: KmzImage__get_matrix_at, \
KmzImageLike: KmzImagelike__get_matrix_at)(me, point)

#define kmzexp__get_matrix_at_x_y(me, point) _Generic((me), \
KmzImage *: KmzImage__get_matrix_at_x_y, \
KmzImageLike: KmzImageLike__get_matrix_at_x_y)(m, x, y)



#define kmzexp_rectangle(p_or_x, s_or_y, w_and_h...) (_Generic((p_or_x), \
KmzPoint: (KmzRectangle) {p_or_x,s_or_y}, \
default: (KmzRectangle) {{p_or_x,s_or_y}, {w_and_h}}))

#define kmzexp_rectanglef(p_or_x, s_or_y, w_and_h...) (_Generic((p_or_x), \
KmzPointF: (KmzRectangleF) {p_or_x,s_or_y}, \
default: (KmzRectangleF) {{p_or_x,s_or_y}, {w_and_h}}))

#define kmzexp_line(s_or_x, e_or_y, e_x_and_e_y...) (_Generic((s_or_x), \
KmzPoint: (KmzLine) {s_or_x,e_or_y} \
default: (KmzLine) {{s_or_x,e_or_y},{e_x_and_e_y}}))

#define kmzexp_linef(s_or_x, e_or_y, e_x_and_e_y...) (_Generic((s_or_x), \
KmzPointF: (KmzLineF) {s_or_x,e_or_y} \
default: (KmzLineF) {{s_or_x,e_or_y},{e_x_and_e_y}}))

#endif /* kmz_experimental_h */
#endif
