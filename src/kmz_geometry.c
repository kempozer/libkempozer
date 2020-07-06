#include "kmz_geometry.h"

kmz_rectangle kmz_rectangle_from_dimen(size_t w, size_t h) {
    const kmz_rectangle r = {.w=w, .h=h};
    
    return r;
}

kmz_point kmz_point_from_coord(ssize_t x, ssize_t y) {
    const kmz_point p = {.x=x, .y=y};
    
    return p;
}
