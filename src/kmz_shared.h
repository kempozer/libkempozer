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

#ifndef kmz_shared_h
#define kmz_shared_h

#include <stdio.h>
#include <stdint.h>

#include "kmz_config.h"

typedef float kmz_percent;
typedef uint8_t kmz_channel;

enum kmz_bool_e {
    KMZ_FALSE = 0,
    KMZ_TRUE = 1,
};
typedef enum kmz_bool_e KmzBool;

#define kmz_clamp(val, min, max) (val < min ? min : (val > max ? max : val))

#define kmz_size(w, h) ((KmzSize){w,h})

#define kmz_sizef(w, h) ((KmzSizeF){w,h})

#define kmz_point(x, y) ((KmzPoint){x,y})

#define kmz_pointf(x, y) ((KmzPointF){x,y})

#define kmz_rectangle(pos, size) ((KmzRectangle){pos,size})

#define kmz_rectanglef(pos, size) ((KmzRectangleF){pos,size})

#define kmz_line(start, end) ((KmzLine){start,end})

#define kmz_linef(start, end) ((KmzLineF){start,end})

#define kmz_polygon(count, points) ((KmzPolygon){count,points})

#define kmz_polygonf(count, points) ((KmzPolygonF){count,points})

#endif /* kmz_shared_h */
