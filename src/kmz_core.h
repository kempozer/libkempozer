#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"
#include <assert.h>

// region Image:

/**
 * Provides an interface for interacting with an abstract image. Implementers of this struct must provide a construction interface as well as implement every function exposed.
 */
struct kmz_image_t;
struct kmz_image_t {
    /**
     * @const
     */
    kmz_rectangle dimen;
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

/**
 * Creates a new KmzImage using the built-in KmzImage type for the given GD 2x image file.
 */
KmzImage * kmz_make_image_from_gd_x2(KmzGd2xImageFile image);

kmz_color_32 KmzImage__get_argb_at(KmzImage * me, kmz_point point);

kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y);

void KmzImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color);

void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color);

size_t KmzImage__is_valid(KmzImage * me, kmz_point point);

size_t KmzImage__is_valid_x_y(KmzImage * me, size_t x, size_t y);
// endregion;

// region Matrix:
/**
 * Provides an interface for interacting with an abstract matrix. Implements of this struct must provide a construction interface as well as implement every function exposed.
 */
struct kmz_matrix_t;
struct kmz_matrix_t {
    /**
     * @const
     */
    size_t size;
    /**
     * @const
     */
    size_t hsize;
    kmz_point pos;
    /**
     * @const
     */
    struct kmz_image_t * image;
};
typedef struct kmz_matrix_t KmzMatrix;

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image(KmzImage * image, size_t size);

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image_and_pos(KmzImage * image, kmz_point point, size_t size);

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image_and_pos_x_y(KmzImage * image, ssize_t x, ssize_t y, size_t size);

kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, kmz_point point);

kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y);

void KmzMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color);

void KmzMatrix__set_color_at_x_y(KmzMatrix * me, size_t x, size_t y, kmz_color_32 color);
// endregion;

KmzMatrix * KmzImage__get_matrix(KmzImage * me, size_t size);

KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size);

KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size);

#endif /* kmz_core_h */
