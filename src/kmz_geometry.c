#include "kmz_geometry.h"

KmzBool KmzSize__equal_to(KmzSize me, KmzSize other) {
    return me.h == other.h && me.w == other.w;
}

KmzBool KmzSizeF__equal_to(KmzSizeF me, KmzSizeF other) {
    return me.h == other.h && me.w == other.w;
}

KmzBool KmzPoint__equal_to(KmzPoint me, KmzPoint other) {
    return me.x == other.x && me.y == other.y;
}

KmzBool KmzPointF__equal_to(KmzPointF me, KmzPointF other) {
    return me.x == other.x && me.y == other.y;
}

KmzBool KmzRectangle__equal_to(KmzRectangle me, KmzRectangle other) {
    return KmzPoint__equal_to(me.pos, other.pos) && KmzSize__equal_to(me.size, other.size);
}

KmzBool KmzRectangleF__equal_to(KmzRectangleF me, KmzRectangleF other) {
    return KmzPointF__equal_to(me.pos, other.pos) && KmzSizeF__equal_to(me.size, other.size);
}

KmzBool KmzLine__equal_to(KmzLine me, KmzLine other) {
    return KmzPoint__equal_to(me.start, other.start) && KmzPoint__equal_to(me.end, other.end);
}

KmzBool KmzLineF__equal_to(KmzLineF me, KmzLineF other) {
    return KmzPointF__equal_to(me.start, other.start) && KmzPointF__equal_to(me.end, other.end);
}
