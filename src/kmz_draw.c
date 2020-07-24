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

#include "kmz_draw.h"

/*
struct _kmz_painter_layer_t {
    KmzRectangle _area;
    size_t _len;
    kmz_color_32 * _pixels;
};
typedef struct _kmz_painter_layer_t _KmzPainterLayer;

struct _kmz_painter_t {
    KmzBrush _brush;
    KmzBool _is_penf;
    KmzPen _pen;
    KmzPenF _penf;
    size_t _hcount;
    size_t _count;
    size_t _size;
    _KmzPainterLayer * _layers;
};
typedef struct _kmz_painter_t _KmzPainter;

KmzPainter * const KmzPainter__new(void) {
    _KmzPainter * const restrict me = malloc(sizeof(_KmzPainter));
    if (me != NULL) {
        me->_brush = KmzBrush__TRANSPARENT;
        me->_pen = KmzPen__TRANSPARENT;
        me->_penf = KmzPenF__TRANSPARENT;
        me->_count = 0;
        me->_hcount = 0;
        me->_size = 0;
        me->_layers = NULL;
    }
    return (KmzPainter*)me;
}

void KmzPainter__free(KmzPainter * const me) {
    _KmzPainter * const restrict self = (_KmzPainter*)me;
    if (self->_layers != NULL) {
        for (size_t i = 0; i < self->_count; ++i) {
            free(self->_layers[i]._pixels);
        }
        free(self->_layers);
    }
    free(self);
}

void KmzPainter__set_brush(KmzPainter * const me, const KmzBrush brush) {
    _KmzPainter * const restrict self = (_KmzPainter*)me;
    self->_brush = brush;
}

void KmzPainter__set_pen(KmzPainter * const me, const KmzPen pen) {
    _KmzPainter * const restrict self = (_KmzPainter*)me;
    self->_pen = pen;
    self->_is_penf = KMZ_FALSE;
}

void KmzPainter__set_penf(KmzPainter * const me, const KmzPenF pen) {
    _KmzPainter * const restrict self = (_KmzPainter*)me;
    self->_penf = pen;
    self->_is_penf = KMZ_TRUE;
}

static inline KmzBool _KmzPainter__try_grow_stack(_KmzPainter * const restrict me) {
    // Attempts to reallocate the stack. KMZ_TRUE is returned if the stack isn't resized due to it being of sufficient size or
    // if there's enough memory to resize, otherwise KMZ_FALSE is returned.
    if (me->_count == me->_size) {
        const size_t size = 0 == me->_size ? 8 : (me->_size * 2);
        _KmzPainterLayer * restrict layers = NULL;
        if (NULL == me->_layers) {
            layers = calloc(size, sizeof(_KmzPainterLayer));
        } else {
            layers = realloc(me->_layers, size * sizeof(_KmzPainterLayer));
        }
        if (NULL == layers) {
            return KMZ_FALSE;
        }
        me->_layers = layers;
        me->_size = size;
    }
    return KMZ_TRUE;
}

static inline KmzBool _KmzPainter__push_layer(_KmzPainter * const restrict me, _KmzPainterLayer layer) {
    // Attempts to push a layer onto the stack. KMZ_TRUE is returned if the push is successful, otherwise KMZ_FALSE is returned.
    if (_KmzPainter__try_grow_stack(me)) {
        me->_layers[me->_count++] = layer;
        return KMZ_TRUE;
    }
    return KMZ_FALSE;
}

static inline KmzBool _KmzPainter__pop_layer(_KmzPainter * const restrict me, _KmzPainterLayer * layer) {
    // Attempts to pop a layer from the stack. KMZ_TRUE is returned if the pop is successful, otherwise KMZ_FALSE is returned.
    if (0 == me->_count) {
        return KMZ_FALSE;
    }
    *layer = me->_layers[--me->_count];
    return KMZ_TRUE;
}

const KmzBrush KmzBrush__TRANSPARENT = {.color=0x7F000000};
const KmzPen KmzPen__TRANSPARENT = {.color=0x7F000000};
const KmzPenF KmzPenF__TRANSPARENT = {.color=0x7F000000};
*/
