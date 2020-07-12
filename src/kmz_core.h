#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"

// region Types:
typedef void * kmz_image_ptr;
typedef void * kmz_arg_ptr;

struct kmz_matrix_t;

struct kmz_image_like_vtab_t {
    /**
     * @const
     */
    KmzSize (* get_dimen)(kmz_image_ptr);
    /**
     * @const
     */
    kmz_color_32 (* get_argb_at)(kmz_image_ptr, KmzPoint);
    /**
     * @const
     */
    void (* set_argb_at)(kmz_image_ptr, KmzPoint, kmz_color_32);
    /**
     * @const
     */
    KmzBool (* is_valid)(kmz_image_ptr, KmzPoint);
    /**
     * @const
     */
    struct kmz_matrix_t * (* get_matrix_at)(kmz_image_ptr, KmzPoint, size_t);
};
typedef struct kmz_image_like_vtab_t KmzImageLikeVTab;

struct kmz_image_like_t {
    /**
     * @const
     */
    KmzImageLikeVTab * _vt;
    /**
     * @const
     */
    kmz_image_ptr _me;
};
typedef struct kmz_image_like_t KmzImageLike;

struct kmz_image_t {
    /**
     * @const
     */
    KmzSize dimen;
    /**
     * @const
     */
    size_t len;
    /**
     * @const
     */
    kmz_color_32 * pixels;
};
typedef struct kmz_image_t KmzImage;

struct kmz_matrix_t {
    /**
     * @const
     */
    size_t size;
    /**
     * @const
     */
    size_t hsize;
    KmzPoint pos;
    /**
     * @const
     */
    KmzImageLike image;
    /**
     * @const
     */
    KmzSize image_dimen;
};
typedef struct kmz_matrix_t KmzMatrix;

typedef kmz_color_32 (*KmzFilter)(size_t, kmz_arg_ptr, KmzMatrix *);
// endregion;

// region Functions:

/**
 * Creates a new KmzImage using the given GD 2x image file.
 */
KmzImage * KmzImage__new_from_gd_2x(KmzGd2xImageFile * image);

/**
 * Creates a new KmzImage using the given color buffer.
 */
KmzImage * KmzImage__new_from_buffer(KmzSize dimen, kmz_color_32 * pixels);

/**
 * Creates a new image-like for the given image.
 */
KmzImageLike KmzImage__to_image_like(KmzImage * me);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at(KmzImage * me, KmzPoint point);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(KmzImage * me, KmzPoint point, kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImage__is_valid(KmzImage * me, KmzPoint point);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * KmzMatrix__new_from_image_like(KmzImageLike image, KmzPoint point, size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_argb_at(KmzMatrix * me, KmzPoint point);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_argb_at(KmzMatrix * me, KmzPoint point, kmz_color_32 color);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, KmzPoint point, size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter(KmzImage * me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter(KmzImage * me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                     KmzImage * buffer);

/**
 * Produces a new KmzImageLike wrapper for the given virtual table and image reference.
 */
KmzImageLike KmzImageLike__wrap(KmzImageLikeVTab * vt_ref, kmz_image_ptr ref);

/**
 * Gets the dimensions of the image..
 */
KmzSize KmzImageLike__get_dimen(KmzImageLike me);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImageLike__get_argb_at(KmzImageLike me, KmzPoint point);

/**
 * Sets a color within the image.
 */
void KmzImageLike__set_argb_at(KmzImageLike me, KmzPoint point, kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImageLike__is_valid(KmzImageLike me, KmzPoint point);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImageLike__get_matrix_at(KmzImageLike me, KmzPoint point, size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KKmzImageLike__apply_filter(KmzImageLike me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter(KmzImageLike me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                         KmzImageLike buffer);
// endregion;

// region Helpers:
#define KmzImage__get_argb_at_x_y(me, x, y) KmzImage__get_argb_at(me, kmz_point(x, y))

#define KmzImage__set_argb_at_x_y(me, x, y, color) KmzImage__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__is_valid_x_y(me, x, y) KmzImage__is_valid(me, kmz_point(x, y))

#define KmzMatrix__get_argb_at_x_y(me, x, y) KmzMatrix__get_argb_at(me, kmz_point(x, y), c)

#define KmzMatrix__set_argb_at_x_y(me, x, y, color) KmzMatrix__set_argb_at(me, kmz_point(x, y), c)

#define KmzImage__get_matrix_at_x_y(me, x, y) KmzImage__get_matrix_at(me, kmz_point(x, y))

#define KmzImageLike__get_argb_at_x_y(me, x, y) KmzImageLike__get_argb_at(me, kmz_point(x, y))

#define KmzImageLike__set_argb_at_x_y(me, x, y, color) KmzImageLike__set_argb_at(me, kmz_point(x, y), c)

#define KmzImageLike__is_valid_x_y(me, x, y) KmzImageLike__is_valid(me, kmz_point(x, y))

#define KmzImageLike__get_matrix_at_x_y(me, x, y, size) KmzImageLike__get_matrix_at(me, kmz_point(x, y), size)
// endregion;

// region Hacks:
// NOTE: These macros *may not* be present in future versions. Avoid relying on them until they've been decided upon.
#define kmz__get_argb_at(me, point) _Generic((me), \
KmzImage *: KmzImage__get_argb_at, KmzImageLike: KmzImageLike__get_argb_at, KmzMatrix *: KmzMatrix__get_argb_at)(me, point)

#define kmz__set_argb_at_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__get_argb_at_x_y, KmzImageLike: KmzImageLike__get_argb_at_x_y, KmzMatrix *: KmzMatrix__get_argb_at_x_y)(me, x, y, color)

#define kmz__get_argb_at_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__get_argb_at_x_y, KmzImageLike: KmzImageLike__get_argb_at_x_y, KmzMatrix *: KmzMatrix__get_argb_at_x_y)(me, x, y)

#define kmz__set_argb_at(me, point, color) _Generic((me), \
KmzImage *: KmzImage__set_argb_at, KmzImageLike: KmzImageLike__set_argb_at, KmzMatrix *: KmzMatrix__set_argb_at)(me, point, color)

#define kmz__is_valid(me, point) _Generic((me), \
KmzImage *: KmzImage__is_valid, KmzImageLike: KmzImageLike__is_valid)(me, point)

#define kmz__is_valid_x_y(me, x, y) _Generic((me), \
KmzImage *: KmzImage__is_valid_x_y, KmzImageLike: KmzImageLike__is_valid_x_y)(me, x, y)

#define kmz__get_matrix_at(me, point) _Generic((me), \
KmzImage *: KmzImage__get_matrix_at, KmzImageLike: KmzImagelike__get_matrix_at)(me, point)

#define kmz__get_matrix_at_x_y(me, point) _Generic((me), \
KmzImage *: KmzImage__get_matrix_at_x_y, KmzImageLike: KmzImageLike__get_matrix_at_x_y)(m, x, y)
// endregion;

#endif /* kmz_core_h */
