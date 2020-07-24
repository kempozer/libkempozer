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

#ifndef libkempozer_draw_h
#define libkempozer_draw_h

#include <libkempozer.h>
#include <libkempozer/geometry.h>
#include <libkempozer/color.h>
#include <libkempozer/image.h>

/**
 * Defines an abstract, opaque painter within kempozer.
 */
struct kmz_painter_t;
typedef struct kmz_painter_t KmzPainter;

/**
 * Defines an abstract, opaque pattern within kempozer.
 */
struct kmz_pattern_t;
typedef struct kmz_pattern_t KmzPattern;

/**
 * Defines the structure of a brush used for filling in solid objects while drawing within kempozer.
 */
struct kmz_brush_t {
    kmz_color_32 color;
    KmzPattern * pattern;
};
typedef struct kmz_brush_t KmzBrush;

/**
 * Defines the structure of a pen used for filling in line objects while drawing within kempozer.
 */
struct kmz_pen_t {
    KmzBool antialias;
    kmz_color_32 color;
    float width;
};
typedef struct kmz_pen_t KmzPen;

/**
 * Defines the methods available to an abstract pattern within kempozer.
 */
struct kmz_pattern_type_t {
    // region Version 1:

    /**
     * @par Allocates an uninitialized pattern represented by this {@link KmzPatternType}.
     *
     * @par This method MUST:
     * * be defined
     * * only initialize pointer fields to {@link NULL}
     * * return the appropriate pointer type for the pattern type being returned instead of `void * const`.
     *
     * @return A pointer to a memory location that contains an unitialized pattern represented by this {@link KmzPatternType}, or {@link NULL} if there isn't enough memory available.
     */
    void * const (* const _new)(void);

    /**
     * @par Initializes an uninitialized pattern represented by this {@link KmzPatternType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the pattern being initialized instead of `void * const`
     * * free `me` if initialization fails.
     *
     * @par This method MAY:
     * * accept an argument (or multiple arguments using a struct) in `argv`
     * * accept the appropriate pointer type for the argument structure being used for initialization if needed.
     *
     * @param me A pointer to an uninitialized pattern represented by this {@link KmzPatternType}.
     * @param argv A pointer to the arguments used to initialize the uninitialized pattern, or {@link NULL} if no arguments are to be used.
     */
    void (* const _ctor)(void * const restrict, const void * const restrict);

    /**
     * @par Deallocates an initialized pattern represented by this {@link KmzPatternType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * free all pointers held
     * * free `me` when all other pointers are freed
     * * accept the appropriate pointer type for the pattern being deallocated instead of `void * const`.
     *
     * @param me A pointer to an initialized pattern represented by this {@link KmzPatternType}.
     */
    void (* const _dtor)(void * const restrict);

    // endregion;
};
typedef struct kmz_pattern_type_t KmzPatternType;

KmzPattern * const KmzPattern__new(const KmzPatternType * const restrict type, const void * const restrict argv);

void KmzPattern__free(KmzPattern * const restrict me);

/**
 * Defines the methods available to an abstract painter within kempozer.
 */
struct kmz_painter_type_t {
    // region Version 1:

    /**
     * @par Allocates an uninitialized painter represented by this {@link KmzPainterType}.
     *
     * @par This method MUST:
     * * be defined
     * * only initialize pointer fields to {@link NULL}
     * * return the appropriate pointer type for the painter type being returned instead of `void * const`.
     *
     * @return A pointer to a memory location that contains an unitialized painter represented by this {@link KmzPainterType}, or {@link NULL} if there isn't enough memory available.
     */
    void * const (* const _new)(void);

    /**
     * @par Initializes an uninitialized painter represented by this {@link KmzPainterType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being initialized instead of `void * const`
     * * free `me` if initialization fails.
     *
     * @par This method MAY:
     * * accept an argument (or multiple arguments using a struct) in `argv`
     * * accept the appropriate pointer type for the argument structure being used for initialization if needed.
     *
     * @param me A pointer to an uninitialized painter represented by this {@link KmzPatternType}.
     * @param argv A pointer to the arguments used to initialize the uninitialized painter, or {@link NULL} if no arguments are to be used.
     */
    void (* const _ctor)(void * const restrict, const void * const restrict);

    /**
     * @par Deallocates an initialized painter represented by this {@link KmzPainterType}.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * free all pointers held
     * * free `me` when all other pointers are freed
     * * accept the appropriate pointer type for the painter being deallocated instead of `void * const`.
     *
     * @param me A pointer to an initialized painter represented by this {@link KmzPainterType}.
     */
    void (* const _dtor)(void * const restrict);

    /**
     * @par Returns the brush of the target painter for filling in solid shapes.
     *
     * @par This method MUST:
     * * be defined
     * * return {@link KmzBrush__TRANSPARENT} if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @return The {@link KmzBrush} that will be used to fill in solid shapes.
     */
    const KmzBrush (* const brush)(void * const restrict);

    /**
     * @par Updates the brush of the target painter for filling in solid shapes.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @param brush The new brush to use.
     */
    void (* const set_brush)(void * const restrict, const KmzBrush);

    /**
     * @par Returns the pen of the target painter for filling in lines.
     *
     * @par This method MUST:
     * * be defined
     * * return {@link KmzPen__TRANSPARENT} if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @return The {@link KmzPen} that will be used to fill in lines.
     */
    const KmzPen (* const pen)(void * const restrict);

    /**
     * @par Updates the pen of the target painter for filling in lines.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @param pen The new pen to use.
     */
    void (* const set_pen)(void * const restrict, const KmzPen);

    /**
     * @par Draws an integer line on the target painter using the target painter's pen.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_linef} if integer drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_line} or {@link KmzPainterType::draw_linef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param line The integer line to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_line)(void * const restrict, const KmzLine);

    /**
     * @par Draws a float line on the target painter using the target painter's pen.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_line} if float drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_line} or {@link KmzPainterType::draw_linef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param line The float line to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_linef)(void * const restrict, const KmzLineF);

    /**
     * @par Draws an integer point on the target painter using the target painter's pen.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_pointf} if integer drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_point} or {@link KmzPainterType::draw_pointf} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param point The integer point to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_point)(void * const restrict, const KmzPoint);

    /**
     * @par Draws a float point on the target painter using the target painter's pen.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_point} if float drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_point} or {@link KmzPainterType::draw_pointf} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param point The float point to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_pointf)(void * const restrict, const KmzPointF);

    /**
     * @par Draws an integer polygon or polyline on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_polygonf} if integer drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_polygon} or {@link KmzPainterType::draw_polygonf} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param polygon The integer polygon or polyline to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_polygon)(void * const restrict, const KmzPolygon);

    /**
     * @par Draws a float polygon or polyline on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_polygon} if float drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_polygon} or {@link KmzPainterType::draw_polygonf} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param polygon The float polygon to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_polygonf)(void * const restrict, const KmzPolygonF);

    /**
     * @par Draws an integer rectangle on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_rectanglef} if integer drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_rectangle} or {@link KmzPainterType::draw_rectanglef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param rectangle The integer rectangle to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_rectangle)(void * const restrict, const KmzRectangle);

    /**
     * @par Draws a float rectangle on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_rectangle} if float drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_rectangle} or {@link KmzPainterType::draw_rectanglef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param rectangle The float rectangle to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_rectanglef)(void * const restrict, const KmzRectangleF);

    /**
     * @par Draws an integer circle on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_circlef} if integer drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_circle} or {@link KmzPainterType::draw_circlef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param circle The integer circle to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_circle)(void * const restrict, const KmzCircle);

    /**
     * @par Draws a float line on the target painter using the target painter's pen and brush.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @par This method MAY:
     * * forward its arguments to {@link KmzPainter__draw_circle} if float drawing is not supported.
     *
     * @remark Either {@link KmzPainterType::draw_circle} or {@link KmzPainterType::draw_circlef} MUST implement a drawing routine. They MUST NOT cause an infinite loop.
     *
     * @param me The target of this invocation.
     * @param circle The float circle to draw.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const draw_circlef)(void * const restrict, const KmzCircleF);

    /**
     * @par Saves the contents of the target painter at the provided posiition within the provided image.
     *
     * @par This method MUST:
     * * be defined
     * * do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @param pos The position to draw the changes to.
     * @param image The image to draw the changes to.
     * @return {@link KMZ_DRAW_OK} if the drawing operation is successful, otherwise an appropriate value from {@link KmzDrawStatus}.
     */
    const KmzDrawStatus (* const paint)(void * const restrict, const KmzPoint, KmzImage * const restrict);

    /**
     * @par Undoes the most recent change of the target painter.
     *
     * @par This method MUST:
     * * be defined if {@link KmzPainterType::redo} is defined
     * * do nothing if `me` is {@link NULL}
     * * return {@link KMZ_FALSE} if undo operations are not supported
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @return {@link KMZ_TRUE} if the undo operation is successful, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const undo)(void * const restrict);

    /**
     * @par Redoes the most recent change of the target painter.
     *
     * @par This method MUST:
     * * be defined if {@link KmzPainterType::undo} is defined
     * * do nothing if `me` is {@link NULL}
     * * return {@link KMZ_FALSE} if redo operations are not supported
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @return {@link KMZ_TRUE} if the redo operation is successful, otherwise {@link KMZ_FALSE}.
     */
    const KmzBool (* const redo)(void * const restrict);

    // endregion;
};
typedef struct kmz_painter_type_t KmzPainterType;

KmzPainter * const KmzPainter__new(const KmzPainterType * const restrict type, const void * const restrict argv);

void KmzPainter__free(KmzPainter * const restrict me);

KmzBrush KmzPainter__brush(const KmzPainter * const restrict me);

void KmzPainter__set_brush(KmzPainter * const restrict me, const KmzBrush brush);

KmzPen KmzPainter__pen(const KmzPainter * const restrict me);

void KmzPainter__set_pen(KmzPainter * const restrict me, const KmzPen brush);

const KmzDrawStatus KmzPainter__draw_circle(KmzPainter * const restrict me, const KmzCircle circle);

const KmzDrawStatus KmzPainter__draw_circlef(KmzPainter * const restrict me, const KmzCircleF circle);

const KmzDrawStatus KmzPainter__draw_line(KmzPainter * const restrict me, const KmzLine line);

const KmzDrawStatus KmzPainter__draw_linef(KmzPainter * const restrict me, const KmzLineF line);

const KmzDrawStatus KmzPainter__draw_point(KmzPainter * const restrict me, const KmzPoint point);

const KmzDrawStatus KmzPainter__draw_pointf(KmzPainter * const restrict me, const KmzPointF point);

const KmzDrawStatus KmzPainter__draw_polygon(KmzPainter * const restrict me, const KmzPolygon polygon);

const KmzDrawStatus KmzPainter__draw_polygonf(KmzPainter * const restrict me, const KmzPolygonF polygon);

const KmzDrawStatus KmzPainter__draw_rectangle(KmzPainter * const restrict me, const KmzRectangle rectangle);

const KmzDrawStatus KmzPainter__draw_rectanglef(KmzPainter * const restrict me, const KmzRectangleF rectangle);

const KmzDrawStatus KmzPainter__paint(KmzPainter * const restrict me, KmzImage * const restrict me);

const KmzBool KmzPainter__redo(KmzPainter * const restrict me);

const KmzBool KmzPainter__undo(KmzPainter * const restrict me);

extern const KmzBrush KmzBrush__TRANSPARENT;

extern const KmzPen KmzPen__TRANSPARENT;

#endif /* libkempozer_draw_h */
