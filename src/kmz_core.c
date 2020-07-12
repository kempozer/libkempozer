#include "kmz_core.h"

// region Helpers:
#define _KmzImage__get_index(me, point) ((me->dimen.w * point.y) + point.x)
#define _KmzImage__between(val, in_min, ex_max) val >= in_min && val < ex_max
#define _kmz__clamp(val, min, max) val < min ? min : (val > max ? max : val)
// endregion;

// region Image:
KmzSize _KmzImage__get_dimen(KmzImagePtr me) {
    return me->dimen;
}

KmzImageLike KmzImage__to_image_like(KmzImagePtr me) {
    static KmzImageLikeVTab vt = {
        .get_dimen=(KmzSize (*)(kmz_image_ptr))&_KmzImage__get_dimen,
        .get_argb_at=(kmz_color_32 (*)(kmz_image_ptr, KmzPoint))&KmzImage__get_argb_at,
        .set_argb_at=(void (*)(kmz_image_ptr, KmzPoint, kmz_color_32))&KmzImage__set_argb_at,
        .is_valid=(KmzBool (*)(kmz_image_ptr, KmzPoint))&KmzImage__is_valid,
        .get_matrix_at=(KmzMatrixPtr (*)(kmz_image_ptr, KmzPoint, size_t))&KmzImage__get_matrix_at
    };
    return KmzImageLike__wrap(&vt, me);
}

kmz_color_32 KmzImage__get_argb_at(KmzImagePtr me, KmzPoint point) {
    const ssize_t i = _KmzImage__get_index(me, point);
    return me->pixels[i];
}

kmz_color_32 KmzImage__get_argb_at_x_y(KmzImagePtr me, size_t x, size_t y) {
    const KmzPoint point = {.x=x, .y=y};
    return KmzImage__get_argb_at(me, point);
}

void KmzImage__set_argb_at(KmzImagePtr me, KmzPoint point, kmz_color_32 color) {
    const ssize_t i = _KmzImage__get_index(me, point);
    me->pixels[i] = color;
}

void KmzImage__set_argb_at_x_y(KmzImagePtr me, size_t x, size_t y, kmz_color_32 color) {
    const KmzPoint point = {.x=x, .y=y};
    KmzImage__set_argb_at(me, point, color);
}

KmzMatrix * KmzImage__get_matrix(KmzImagePtr me, size_t size) {
    return KmzImageLike__get_matrix(KmzImage__to_image_like(me), size);
}

KmzMatrix * KmzImage__get_matrix_at(KmzImagePtr me, KmzPoint point, size_t size) {
    return KmzImageLike__get_matrix_at(KmzImage__to_image_like(me), point, size);
}

KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImagePtr me, size_t x, size_t y, size_t size) {
    const KmzPoint point = {.x=x, .y=y};
    return KmzImageLike__get_matrix_at(KmzImage__to_image_like(me), point, size);
}

KmzBool KmzImage__is_valid(KmzImagePtr me, KmzPoint point) {
    return (me->dimen.w > point.x && point.x > -1 && me->dimen.h > point.y && point.y > -1);
}

KmzBool KmzImage__is_valid_x_y(KmzImagePtr me, size_t x, size_t y) {
    const KmzPoint point = {.x=x, .y=y};
    return KmzImage__is_valid(me, point);
}

void _KmzImage__populate_from_gd_2x(KmzImagePtr me, KmzGd2xImageFile * image) {
    me->dimen = image->header.signature.dimen;
    me->len = me->dimen.h * me->dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    
    if (image->header.color.is_truecolor) {
        memcpy(me->pixels, image->pixels, me->len * sizeof(kmz_color_32));
    } else {
        for (size_t i = 0; i < me->len; ++i) {
            me->pixels[i] = image->header.color.value.palette.colors[image->pixels[i]];
        }
    }
}

KmzImage * KmzImage__new_from_gd_2x(KmzGd2xImageFile * image) {
    KmzImage * me = malloc(sizeof(KmzImage));
    _KmzImage__populate_from_gd_2x(me, image);
    return me;
}

KmzImage * KmzImage__new_from_buffer(KmzSize dimen, kmz_color_32 * pixels) {
    KmzImage * me = malloc(sizeof(KmzImage));
    me->dimen = dimen;
    me->len = dimen.h * dimen.w;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    memcpy(me->pixels, pixels, me->len * sizeof(kmz_color_32));
    return me;
}
// endregion;

// region Matrix:
KmzPoint _KmzMatrix__clamp_point(KmzMatrixPtr me, KmzPoint point) {
    KmzSize dimen = KmzImageLike__get_dimen(me->image);
    const ssize_t x = me->pos.x + (point.x - me->hsize),
                  y = me->pos.y + (point.y - me->hsize),
                  max_x = dimen.w - 1,
                  max_y = dimen.h - 1;
    
    const KmzPoint p = {
        .x=_kmz__clamp(x, 0, max_x),
        .y=_kmz__clamp(y, 0, max_y)
    };
    return p;
}

kmz_color_32 KmzMatrix__get_color_at(KmzMatrixPtr me, KmzPoint point) {
    return KmzImageLike__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point));
}

kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrixPtr me, size_t x, size_t y) {
    const KmzPoint point = {.x=x, .y=y};
    return KmzMatrix__get_color_at(me, point);
}

void KmzMatrix__set_color_at(KmzMatrixPtr me, KmzPoint point, kmz_color_32 color) {
    KmzImageLike__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point), color);
}

void KmzMatrix__set_color_at_x_y(KmzMatrixPtr me, size_t x, size_t y, kmz_color_32 color) {
    const KmzPoint point = {.x=x, .y=y};
    KmzMatrix__set_color_at(me, point, color);
}

KmzMatrixPtr KmzMatrix__new_from_image_like(KmzImageLike image, size_t size) {
    return KmzMatrix__new_from_image_like_and_pos(image, KmzPoint__ZERO, size);
}

KmzMatrixPtr KmzMatrix__new_from_image_like_and_pos(KmzImageLike image, KmzPoint point, size_t size) {
    KmzMatrix * me = malloc(sizeof(KmzMatrix));
    me->image = image;
    me->pos = point;
    me->size = size;
    me->hsize = me->size / 2;
    return me;
}
// endregion;

// region Filtering:
void KmzImage__apply_filter(KmzImagePtr me, KmzFilter filter, size_t m_size) {
    KmzRectangle area = {.pos={.x=0, .y=0}, .size=me->dimen};
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, me);
}

void KmzImage__apply_filter_at(KmzImagePtr me, KmzFilter filter, KmzPoint pos, size_t m_size) {
    KmzRectangle area = {.pos=pos, .size={.w=me->dimen.w - pos.x, .h=me->dimen.h - pos.y}};
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, me);
}

void KmzImage__apply_filter_to(KmzImagePtr me, KmzFilter filter, KmzRectangle area, size_t m_size) {
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, me);
}

void KmzImage__apply_filter_with_args_to(KmzImagePtr me, size_t argc, void * argv, KmzFilter filter, KmzRectangle area, size_t m_size) {
    KmzImage__apply_buffered_filter_with_args_to(me, argc, argv, filter, area, m_size, me);
}

void KmzImage__apply_buffered_filter(KmzImagePtr me, KmzFilter filter, size_t m_size, KmzImagePtr buffer) {
    KmzRectangle area = {.pos={.x=0, .y=0}, .size=me->dimen};
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImage__apply_buffered_filter_at(KmzImagePtr me, KmzFilter filter, KmzPoint pos, size_t m_size, KmzImagePtr buffer) {
    KmzRectangle area = {.pos=pos, .size={.w=me->dimen.w - pos.x, .h=me->dimen.h - pos.y}};
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImage__apply_buffered_filter_to(KmzImagePtr me, KmzFilter filter, KmzRectangle area, size_t m_size, KmzImagePtr buffer) {
    KmzImage__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImage__apply_buffered_filter_with_args_to(KmzImagePtr me, size_t argc, void * argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                                  KmzImagePtr buffer) {
    KmzImageLike _me = KmzImage__to_image_like(me);
    KmzImageLike _buffer = KmzImage__to_image_like(buffer);
    KmzImageLike__apply_buffered_filter_with_args_to(_me, argc, argv, filter, area, m_size, _buffer);
}
// endregion;

// region Imagelike:
const KmzImageLike KmzImageLike__wrap(KmzImageLikeVTabPtr vt_ref, kmz_image_ptr ref) {
    const KmzImageLike me = {._vt = vt_ref, ._me = ref};
    return me;
}

KmzSize KmzImageLike__get_dimen(KmzImageLike me) {
    return me._vt->get_dimen(me._me);
}

kmz_color_32 KmzImageLike__get_argb_at(KmzImageLike me, KmzPoint point) {
    return me._vt->get_argb_at(me._me, point);
}

kmz_color_32 KmzImageLike__get_argb_at_x_y(KmzImageLike me, size_t x, size_t y) {
    const KmzPoint point = {.x=x, .y=y};
    return me._vt->get_argb_at(me._me, point);
}

void KmzImageLike__set_argb_at(KmzImageLike me, KmzPoint point, kmz_color_32 color) {
    me._vt->set_argb_at(me._me, point, color);
}

void KmzImageLike__set_argb_at_x_y(KmzImageLike me, size_t x, size_t y, kmz_color_32 color) {
    const KmzPoint point = {.x=x, .y=y};
    me._vt->set_argb_at(me._me, point, color);
}

KmzBool KmzImageLike__is_valid(KmzImageLike me, KmzPoint point) {
    return me._vt->is_valid(me._me, point);
}

KmzBool KmzImageLike__is_valid_x_y(KmzImageLike me, size_t x, size_t y) {
    const KmzPoint point = {.x=x, .y=y};
    return me._vt->is_valid(me._me, point);
}

KmzMatrixPtr KmzImageLike__get_matrix(KmzImageLike me, size_t size) {
    return KmzMatrix__new_from_image_like_and_pos(me, KmzPoint__ZERO, size);
}

KmzMatrixPtr KmzImageLike__get_matrix_at(KmzImageLike me, KmzPoint point, size_t size) {
    return KmzMatrix__new_from_image_like_and_pos(me, point, size);
}

KmzMatrixPtr KmzImageLike__get_matrix_at_x_y(KmzImageLike me, size_t x, size_t y, size_t size) {
    KmzPoint point = {.x=x, .y=y};
    return KmzMatrix__new_from_image_like_and_pos(me, point, size);
}

void KmzImageLike__apply_filter(KmzImageLike me, KmzFilter filter, size_t m_size) {
    KmzImageLike__apply_buffered_filter(me, filter, m_size, me);
}

void KmzImageLike__apply_filter_at(KmzImageLike me, KmzFilter filter, KmzPoint pos, size_t m_size) {
    KmzImageLike__apply_buffered_filter_at(me, filter, pos, m_size, me);
}

void KmzImageLike__apply_filter_to(KmzImageLike me, KmzFilter filter, KmzRectangle area, size_t m_size) {
    KmzImageLike__apply_buffered_filter_to(me, filter, area, m_size, me);
}

void KKmzImageLike__apply_filter_with_args_to(KmzImageLike me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size) {
    KmzImageLike__apply_buffered_filter_with_args_to(me, argc, argv, filter, area, m_size, me);
}

void KmzImageLike__apply_buffered_filter(KmzImageLike me, KmzFilter filter, size_t m_size, KmzImageLike buffer) {
    KmzRectangle area = {.pos={.x=0, .y=0}, .size=KmzImageLike__get_dimen(me)};
    KmzImageLike__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImageLike__apply_buffered_filter_at(KmzImageLike me, KmzFilter filter, KmzPoint pos, size_t m_size, KmzImageLike buffer) {
    KmzSize dimen = KmzImageLike__get_dimen(me);
    KmzRectangle area = {.pos=pos, .size={.w=dimen.w - pos.x, .h=dimen.h - pos.y}};
    KmzImageLike__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImageLike__apply_buffered_filter_to(const KmzImageLike me, KmzFilter filter, KmzRectangle area, size_t m_size, const KmzImageLike buffer) {
    KmzImageLike__apply_buffered_filter_with_args_to(me, 0, NULL, filter, area, m_size, buffer);
}

void KmzImageLike__apply_buffered_filter_with_args_to(const KmzImageLike me, size_t argc, void * argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                                      const KmzImageLike buffer) {
    KmzSize dimen = KmzImageLike__get_dimen(me);
    size_t x = _kmz__clamp(area.pos.x, 0, dimen.w),
           y = _kmz__clamp(area.pos.y, 0, dimen.h),
           max_x = _kmz__clamp(area.size.w + x, x, dimen.w),
           max_y = _kmz__clamp(area.size.h + y, y, dimen.h);
    
    KmzMatrix * matrix = KmzImageLike__get_matrix(me, m_size);
    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            me._vt->set_argb_at(buffer._me, matrix->pos, filter(argc, argv, matrix));
        }
    }
    free(matrix);
}
// endregion;
