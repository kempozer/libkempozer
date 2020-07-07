#include "kmz_core.h"

// region Image:
ssize_t _KmzImage__get_index(KmzImage * me, kmz_point point) {
    return ((me->dimen.w * point.y) + point.x);
}

kmz_color_32 KmzImage__get_argb_at(KmzImage * me, kmz_point point) {
    const ssize_t i = _KmzImage__get_index(me, point);
    return me->pixels[i];
}

kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    return KmzImage__get_argb_at(me, point);
}

void KmzImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color) {
    const ssize_t i = _KmzImage__get_index(me, point);
    me->pixels[i] = color;
}

void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color) {
    const kmz_point point = {.x=x, .y=y};
    KmzImage__set_argb_at(me, point, color);
}

KmzMatrix * KmzImage__get_matrix(KmzImage * me, size_t size) {
    return KmzImage__get_matrix_at(me, kmz_point__ZERO, size);
}

KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size) {
    KmzMatrix * matrix = malloc(sizeof(KmzMatrix));
    matrix->image = me;
    matrix->pos = point;
    matrix->size = size;
    matrix->hsize = matrix->size / 2;
    return matrix;
}

KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size) {
    const kmz_point point = {.x=x, .y=y};
    
    return KmzImage__get_matrix_at(me, point, size);
}

size_t KmzImage__is_valid(KmzImage * me, kmz_point point) {
    
    return (me->dimen.w > point.x && point.x > -1 &&
            me->dimen.h > point.y && point.y > -1);
}

size_t KmzImage__is_valid_x_y(KmzImage * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    return KmzImage__is_valid(me, point);
}

KmzImage * kmz_make_image_from_gd_x2(KmzGd2xImageFile image) {
    KmzImage * me = malloc(sizeof(KmzImage));
    me->dimen = image.header.signature.dimen;
    me->len = me->dimen.h * me->dimen.w;
    me->pixels = image.pixels;
    me->pixels = calloc(me->len, sizeof(kmz_color_32));
    
    if (image.header.color.is_truecolor) {
        memcpy(me->pixels, image.pixels, me->len * sizeof(kmz_color_32));
    } else {
        for (size_t i = 0; i < me->len; ++i) {
            me->pixels[i] = image.header.color.value.palette.palette[image.pixels[i]];
        }
    }
    
    return me;
}

// endregion;

// region Matrix:
ssize_t _KmzMatrix__clamp(ssize_t val, ssize_t min, ssize_t max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

kmz_point _KmzMatrix__clamp_point(KmzMatrix * me, kmz_point point) {
    const ssize_t x = me->pos.x + (point.x - me->hsize),
                  y = me->pos.y + (point.y - me->hsize);
    const kmz_point p = {
        .x=_KmzMatrix__clamp(x, 0, me->image->dimen.w - 1),
        .y=_KmzMatrix__clamp(y, 0, me->image->dimen.h - 1)
    };
    return p;
}

kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, kmz_point point) {
    return KmzImage__get_argb_at(me->image, _KmzMatrix__clamp_point(me, point));
}

kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    return KmzMatrix__get_color_at(me, point);
}

void KmzMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color) {
    KmzImage__set_argb_at(me->image, _KmzMatrix__clamp_point(me, point), color);
}

void KmzMatrix__set_color_at_x_y(KmzMatrix * me, size_t x, size_t y, kmz_color_32 color) {
    const kmz_point point = {.x=x, .y=y};
    KmzMatrix__set_color_at(me, point, color);
}

// endregion;
