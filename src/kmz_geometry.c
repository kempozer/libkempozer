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
#include <stdint.h>
#include "kmz_config.h"
#include "libkempozer.h"

const KmzBool KmzSize__equal_to(const KmzSize me, const KmzSize other) {
    return me.h == other.h && me.w == other.w;
}

const KmzBool KmzSizeF__equal_to(const KmzSizeF me, const KmzSizeF other) {
    return me.h == other.h && me.w == other.w;
}

const KmzBool KmzPoint__equal_to(const KmzPoint me, const KmzPoint other) {
    return me.x == other.x && me.y == other.y;
}

const KmzBool KmzPointF__equal_to(const KmzPointF me, const KmzPointF other) {
    return me.x == other.x && me.y == other.y;
}

const KmzBool KmzRectangle__equal_to(const KmzRectangle me, const KmzRectangle other) {
    return KmzPoint__equal_to(me.pos, other.pos) && KmzSize__equal_to(me.size, other.size);
}

const KmzBool KmzRectangleF__equal_to(const KmzRectangleF me, const KmzRectangleF other) {
    return KmzPointF__equal_to(me.pos, other.pos) && KmzSizeF__equal_to(me.size, other.size);
}

const KmzBool KmzLine__equal_to(const KmzLine me, const KmzLine other) {
    return KmzPoint__equal_to(me.start, other.start) && KmzPoint__equal_to(me.end, other.end);
}

const KmzBool KmzLineF__equal_to(const KmzLineF me, const KmzLineF other) {
    return KmzPointF__equal_to(me.start, other.start) && KmzPointF__equal_to(me.end, other.end);
}

const KmzBool KmzPolygonF__equal_to(const KmzPolygonF me, const KmzPolygonF other) {
    if (me.count == other.count) {
        for (size_t i = 0; i < me.count; ++i) {
            if (!KmzPointF__equal_to(me.points[i], other.points[i])) {
                return KMZ_FALSE;
            }
        }
        return KMZ_TRUE;
    }
    return KMZ_FALSE;
}

const KmzBool KmzPolygon__equal_to(const KmzPolygon me, const KmzPolygon other) {
    if (me.count == other.count) {
        for (size_t i = 0; i < me.count; ++i) {
            if (!KmzPoint__equal_to(me.points[i], other.points[i])) {
                return KMZ_FALSE;
            }
        }
        return KMZ_TRUE;
    }
    return KMZ_FALSE;
}
