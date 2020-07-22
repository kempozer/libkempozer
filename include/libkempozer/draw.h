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

#ifndef draw_h
#define draw_h

#include <libkempozer.h>
#include <libkempozer/color.h>
#include <libkempozer/image.h>

/**
 * Defines an abstract, opaque painter within kempozer.
 */
struct kmz_painter_t;
typedef struct kmz_painter_t KmzPainter;

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
};
typedef struct kmz_pattern_type_t KmzPatternType;

/**
 * Defines an abstract, opaque pattern within kempozer.
 */
struct kmz_pattern_t;
typedef struct kmz_pattern_t KmzPattern;

/**
 * Defines the methods available to an abstract painter within kempozer.
 */
struct kmz_painter_type_t {
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
     * * Do nothing if `me` is {@link NULL}
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
     * * Do nothing if `me` is {@link NULL}
     * * accept the appropriate pointer type for the painter being accessed instead of `void * const`.
     *
     * @param me The target of this invocation.
     * @param pen The new pen to use.
     */
    void (* const set_pen)(void * const restrict, const KmzPen);

    /**
     *
     */
    const KmzDrawStatus (* const draw_line)(void * const restrict, const KmzLine);

    /**
     *
     */
    const KmzDrawStatus (* const draw_linef)(void * const restrict, const KmzLineF);

    /**
     *
     */
    const KmzDrawStatus (* const draw_point)(void * const restrict, const KmzPoint);

    /**
     *
     */
    const KmzDrawStatus (* const draw_pointf)(void * const restrict, const KmzPointF);

    /**
     *
     */
    const KmzDrawStatus (* const draw_polygon)(void * const restrict, const KmzPolygon);

    /**
     *
     */
    const KmzDrawStatus (* const draw_polygonf)(void * const restrict, const KmzPolygonF);

    /**
     *
     */
    const KmzDrawStatus (* const draw_rectangle)(void * const restrict, const KmzRectangle);

    /**
     *
     */
    const KmzDrawStatus (* const draw_rectanglef)(void * const restrict, const KmzRectangleF);

    /**
     *
     */
    const KmzDrawStatus (* const draw_circle)(void * const restrict, const KmzCircle);

    /**
     *
     */
    const KmzDrawStatus (* const draw_circlef)(void * const restrict, const KmzCircleF);

    /**
     *
     */
    void (* const paint)(void * const restrict, const KmzPoint, KmzImage * const restrict);

    /**
     *
     */
    const KmzBool (* const undo)(void * const restrict);

    /**
     *
     */
    const KmzBool (* const redo)(void * const restrict);
};
typedef struct kmz_painter_type_t KmzPainterType;

extern const KmzBrush KmzBrush__TRANSPARENT;

extern const KmzPen KmzPen__TRANSPARENT;

#endif /* draw_h */
