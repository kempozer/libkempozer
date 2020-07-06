#include "kmz_image.h"

const char * KmzImage__get_type(KmzImage * me) {
    return me->get_type(me);
}

kmz_rectangle KmzImage__get_dimen(KmzImage * me) {
    return me->get_dimen(me);
}

size_t KmzImage__has_argb_buffer(KmzImage * me) {
    return me->has_argb_buffer(me);
}

kmz_color_32 * KmzImage__get_argb_buffer(KmzImage * me) {
    return me->get_argb_buffer(me);
}

kmz_color_32 KmzImage__get_argb_at(KmzImage * me, kmz_point point) {
    return me->get_argb_at(me, point);
}

kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    
    return me->get_argb_at(me, point);
}

void KmzImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color) {
    me->set_argb_at(me, point, color);
}

void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color) {
    const kmz_point point = {.x=x, .y=y};
    
    me->set_argb_at(me, point, color);
}

KmzMatrix * KmzImage__get_matrix(KmzImage * me, size_t size) {
    return me->get_matrix_at(me, kmz_point__ZERO, size);
}

KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size) {
    return me->get_matrix_at(me, point, size);
}

KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size) {
    const kmz_point point = {.x=x, .y=y};
    
    return me->get_matrix_at(me, point, size);
}

size_t KmzImage__is_valid(KmzImage * me, kmz_point point) {
    return me->is_valid(me, point);
}

size_t KmzImage__is_valid_x_y(KmzImage * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    
    return me->is_valid(me, point);
}

void KmzImage__free(KmzImage * me) {
    me->free(me);
}
