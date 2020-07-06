#include "kmz_matrix.h"

char * KmzMatrix__get_type(KmzMatrix * me) {
    return me->get_type(me);
}

size_t KmzMatrix__get_size(KmzMatrix * me) {
    return me->get_size(me);
}

kmz_point KmzMatrix__get_pos(KmzMatrix * me) {
    return me->get_pos(me);
}

void KmzMatrix__set_pos(KmzMatrix * me, kmz_point point) {
    me->set_pos(me, point);
}

void KmzMatrix__set_pos_x_y(KmzMatrix * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    
    me->set_pos(me, point);
}

kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, kmz_point point) {
    return me->get_color_at(me, point);
}

kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    
    return me->get_color_at(me, point);
}

void KmzMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color) {
    me->set_color_at(me, point, color);
}

void KmzMatrix__set_color_at_x_y(KmzMatrix * me, size_t x, size_t y, kmz_color_32 color) {
    const kmz_point point = {.x=x, .y=y};
    
    me->set_color_at(me, point, color);
}

size_t KmzMatrix__is_valid(KmzMatrix * me, kmz_point point) {
    return me->is_valid(me, point);
}

size_t KmzMatrix__is_valid_x_y(KmzMatrix * me, size_t x, size_t y) {
    const kmz_point point = {.x=x, .y=y};
    
    return me->is_valid(me, point);
}

void KmzMatrix__free(KmzMatrix * me) {
    me->free(me);
}
