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

#ifndef kmz_draw_h
#define kmz_draw_h

#include "kmz_config.h"
#include "kmz_shared.h"
#include "kmz_geometry.h"
#include "kmz_color.h"
#include "kmz_core.h"

/**
 * Defines the possible values returned by a drawing command.
 */
enum kmz_draw_status_e {
    KMZ_DRAW_OK = 0,
    KMZ_DRAW_ERR_OUT_OF_MEMORY = -1,
};
typedef enum kmz_draw_status_e KmzDrawStatus;

/**
 * Defines an object that can be used to fill in shapes.
 */
struct kmz_brush_t {
    kmz_color_32 color;
};
typedef struct kmz_brush_t KmzBrush;

/**
 * Defines an object that can be used to draw lines.
 */
struct kmz_pen_t {
    KmzBool antialias;
    KmzBrush fill;
    kmz_color_32 color;
    size_t width;
};
typedef struct kmz_pen_t KmzPen;

/**
 * Defines an object that can be used to draw lines with floating point coordinates.
 */
struct kmz_pen_f_t {
    KmzBool antialias;
    KmzBrush fill;
    kmz_color_32 color;
    float width;
};
typedef struct kmz_pen_f_t KmzPenF;

/**
 * Defines an opaque object that can be used to paint onto an internal buffer.
 */
struct kmz_painter_t;
typedef struct kmz_painter_t KmzPainter;

/**
 * Creates a new KmzPainter for use with painting.
 */
KmzPainter * const KmzPainter__new(void);

/**
 * Frees the KmzPainter and all of its internal contents.
 */
void KmzPainter__free(KmzPainter * const me);

/**
 * Sets the fill brush for this painter.
 */
void KmzPainter__set_brush(KmzPainter * const me, const KmzBrush brush);

/**
 * Sets the pen for this painter and marks it as non-floating point line drawing.
 */
void KmzPainter__set_pen(KmzPainter * const me, const KmzPen pen);

/**
 * Sets the pen for this painter and marks it as floating point line drawing.
 */
void KmzPainter__set_penf(KmzPainter * const me, const KmzPenF pen);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_line(KmzPainter * const restrict me, const KmzLine line);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_linef(KmzPainter * const restrict me, const KmzLineF line);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_point(KmzPainter * const restrict me, const KmzPoint point);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_pointf(KmzPainter * const restrict me, const KmzPointF point);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_polygon(KmzPainter * const restrict me, const KmzPolygon polygon);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_polygonf(KmzPainter * const restrict me, const KmzPolygonF polygon);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_rectangle(KmzPainter * const restrict me, const KmzRectangle rectangle);

/**
 * Draws a shape onto the painter.
 */
const KmzDrawStatus KmzPainter__draw_rectanglef(KmzPainter * const restrict me, const KmzRectangleF rectangle);

/**
 * Paints the painter back to the image-like. Anything that overflows out of the image will be discarded.
 */
const void KmzPainter__paint(KmzPainter * const restrict me, KmzPoint pos, KmzImagePtr target);

/**
 * Undoes the most recent draw operation if possible. KMZ_TRUE is returned if the undo is successful, otherwise KMZ_FALSE is returned.
 */
const KmzBool KmzPainter__undo(KmzPainter * const restrict me);

/**
 * Redoes the most recent draw operation if possible. KMZ_TRUE is returned if the redo is successful, otherwise KMZ_FALSE is returned.
 */
const KmzBool KmzPainter__redo(KmzPainter * const restrict me);

extern const KmzBrush KmzBrush__TRANSPARENT;
extern const KmzPen KmzPen__TRANSPARENT;
extern const KmzPenF KmzPenF__TRANSPARENT;

#endif /* kmz_draw_h */
