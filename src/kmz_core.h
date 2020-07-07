#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"
#include <assert.h>

// region Image:

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

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at(KmzImage * me, kmz_point point);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
size_t KmzImage__is_valid(KmzImage * me, kmz_point point);

/**
 * Determines if the point is a valid coordinate within the image.
 */
size_t KmzImage__is_valid_x_y(KmzImage * me, size_t x, size_t y);

// endregion;

// region Matrix:

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
    KmzImage * image;
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

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, kmz_point point);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_color_at_x_y(KmzMatrix * me, size_t x, size_t y, kmz_color_32 color);
// endregion;

// region Image Matrix:

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImage__get_matrix(KmzImage * me, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size);

// endregion;

#endif /* kmz_core_h */
