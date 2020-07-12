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
KmzMatrix *: KmzMatrix__get_argb_at)(me, point)

#define kmzexp__set_argb_at_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__get_argb_at_x_y, \
KmzImageLike: KmzImageLike__get_argb_at_x_y, \
KmzMatrix *: KmzMatrix__get_argb_at_x_y)(me, x, y, color)

#define kmzexp__get_argb_at_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__get_argb_at_x_y, \
KmzImageLike: KmzImageLike__get_argb_at_x_y, \
KmzMatrix *: KmzMatrix__get_argb_at_x_y)(me, x, y)

#define kmzexp__set_argb_at(me, point, color) _Generic((me), \
KmzImage *: KmzImage__set_argb_at, \
KmzImageLike: KmzImageLike__set_argb_at, \
KmzMatrix *: KmzMatrix__set_argb_at)(me, point, color)

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
