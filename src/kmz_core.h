#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"

// region Image:

struct kmz_image_t {
    /**
     * @const
     */
    KmzRectangle dimen;
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
 * Creates a new KmzImage using the given GD 2x image file.
 */
KmzImage * KmzImage__new_from_gd_2x(KmzGd2xImageFile * image);

/**
 * Creates a new KmzImage using the given color buffer.
 */
KmzImage * KmzImage__new_from_buffer(KmzRectangle dimen, kmz_color_32 * pixels);

/**
 * Frees the image and its pixel pointer.
 */
void KmzImage__free(KmzImage * me);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at(KmzImage * me, KmzPoint point);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(KmzImage * me, KmzPoint point, kmz_color_32 color);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
size_t KmzImage__is_valid(KmzImage * me, KmzPoint point);

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
    KmzPoint pos;
    /**
     * @const
     */
    KmzImage * image;
};
typedef struct kmz_matrix_t KmzMatrix;

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * KmzMatrix__new_from_image(KmzImage * image, size_t size);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrix * KmzMatrix__new_from_image_and_pos(KmzImage * image, KmzPoint point, size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, KmzPoint point);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_color_at(KmzMatrix * me, KmzPoint point, kmz_color_32 color);

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
KmzMatrix * KmzImage__get_matrix_at(KmzImage * me, KmzPoint point, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrix * KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size);

// endregion;

#endif /* kmz_core_h */
