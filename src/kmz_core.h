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
typedef KmzImageLikeVTab * KmzImageLikeVTabPtr;

struct kmz_image_like_t {
    /**
     * @const
     */
    KmzImageLikeVTabPtr _vt;
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
typedef KmzImage * KmzImagePtr;

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
};
typedef struct kmz_matrix_t KmzMatrix;
typedef KmzMatrix * KmzMatrixPtr;

typedef kmz_color_32 (*KmzFilter)(size_t, kmz_arg_ptr, KmzMatrixPtr);
// endregion;

// region Functions:

/**
 * Creates a new KmzImage using the given GD 2x image file.
 */
KmzImagePtr KmzImage__new_from_gd_2x(KmzGd2xImageFile * image);

/**
 * Creates a new KmzImage using the given color buffer.
 */
KmzImagePtr KmzImage__new_from_buffer(KmzSize dimen, kmz_color_32 * pixels);

/**
 * Creates a new image-like for the given image.
 */
KmzImageLike KmzImage__to_image_like(KmzImagePtr me);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at(KmzImagePtr me, KmzPoint point);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImage__get_argb_at_x_y(KmzImagePtr me, size_t x, size_t y);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at(KmzImagePtr me, KmzPoint point, kmz_color_32 color);

/**
 * Sets a color within the image.
 */
void KmzImage__set_argb_at_x_y(KmzImagePtr me, size_t x, size_t y, kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImage__is_valid(KmzImagePtr me, KmzPoint point);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImage__is_valid_x_y(KmzImagePtr me, size_t x, size_t y);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrixPtr KmzMatrix__new_from_image_like(KmzImageLike image, size_t size);

/**
 * Creates a new KmzMatrix for the given image.
 */
KmzMatrixPtr KmzMatrix__new_from_image_like_and_pos(KmzImageLike image, KmzPoint point, size_t size);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at(KmzMatrixPtr me, KmzPoint point);

/**
 * Gets a color from the image referenced by the given matrix relative to the matrix's current position.
 */
kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrixPtr me, size_t x, size_t y);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_color_at(KmzMatrixPtr me, KmzPoint point, kmz_color_32 color);

/**
 * Sets a color in the image referenced by the given matrix relative to the matrix's current position.
 */
void KmzMatrix__set_color_at_x_y(KmzMatrixPtr me, size_t x, size_t y, kmz_color_32 color);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImage__get_matrix(KmzImagePtr me, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImage__get_matrix_at(KmzImagePtr me, KmzPoint point, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImage__get_matrix_at_x_y(KmzImagePtr me, size_t x, size_t y, size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter(KmzImagePtr me, KmzFilter filter, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter_at(KmzImagePtr me, KmzFilter filter, KmzPoint pos, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter_to(KmzImagePtr me, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImage__apply_filter_with_args_to(KmzImagePtr me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter(KmzImagePtr me, KmzFilter filter, size_t m_size, KmzImagePtr buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter_at(KmzImagePtr me, KmzFilter filter, KmzPoint pos, size_t m_size, KmzImagePtr buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter_to(KmzImagePtr me, KmzFilter filter, KmzRectangle area, size_t m_size, KmzImagePtr buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImage__apply_buffered_filter_with_args_to(KmzImagePtr me, size_t argc, void * argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                                  KmzImagePtr buffer);

/**
 * Produces a new KmzImageLike wrapper for the given virtual table and image reference.
 */
const KmzImageLike KmzImageLike__wrap(const KmzImageLikeVTabPtr vt_ref, kmz_image_ptr ref);

/**
 * Gets the dimensions of the image..
 */
KmzSize KmzImageLike__get_dimen(const KmzImageLike me);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImageLike__get_argb_at(const KmzImageLike me, KmzPoint point);

/**
 * Gets a color from within the image.
 */
kmz_color_32 KmzImageLike__get_argb_at_x_y(const KmzImageLike me,
                                           size_t x,
                                           size_t y);

/**
 * Sets a color within the image.
 */
void KmzImageLike__set_argb_at(const KmzImageLike me,
                               KmzPoint point,
                               kmz_color_32 color);

/**
 * Sets a color within the image.
 */
void KmzImageLike__set_argb_at_x_y(const KmzImageLike me,
                                   size_t x,
                                   size_t y,
                                   kmz_color_32 color);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImageLike__is_valid(const KmzImageLike me, KmzPoint point);

/**
 * Determines if the point is a valid coordinate within the image.
 */
KmzBool KmzImageLike__is_valid_x_y(const KmzImageLike me, size_t x, size_t y);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImageLike__get_matrix(const KmzImageLike me, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImageLike__get_matrix_at(const KmzImageLike me, KmzPoint point, size_t size);

/**
 * Creates a new matrix of the given size.
 */
KmzMatrixPtr KmzImageLike__get_matrix_at_x_y(const KmzImageLike me, size_t x, size_t y, size_t size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImageLike__apply_filter(const KmzImageLike me, KmzFilter filter, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImageLike__apply_filter_at(const KmzImageLike me, KmzFilter filter, KmzPoint pos, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KmzImageLike__apply_filter_to(const KmzImageLike me, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced.
 */
void KKmzImageLike__apply_filter_with_args_to(const KmzImageLike me, size_t argc, kmz_arg_ptr argv, KmzFilter filter, KmzRectangle area, size_t m_size);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter(const KmzImageLike me, KmzFilter filter, size_t m_size, const KmzImageLike buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter_at(const KmzImageLike me, KmzFilter filter, KmzPoint pos, size_t m_size, const KmzImageLike buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter_to(const KmzImageLike me, KmzFilter filter, KmzRectangle area, size_t m_size, const KmzImageLike buffer);

/**
 * Applies a matrix filter function to the image referenced and outputs the change to the buffer referenced.
 */
void KmzImageLike__apply_buffered_filter_with_args_to(const KmzImageLike me, size_t argc, void * argv, KmzFilter filter, KmzRectangle area, size_t m_size,
                                                      const KmzImageLike buffer);
// endregion;

#endif /* kmz_core_h */
