#ifndef kmz_image_h
#define kmz_image_h

#include <stdio.h>
#include <stdint.h>
#include "kmz_color.h"
#include "kmz_geometry.h"
#include "kmz_matrix.h"

/**
 * Provides an interface for interacting with an abstract image. Implementers of this struct must provide a construction interface as well as implement every function exposed.
 */
struct kmz_image_t;
struct kmz_image_t {
    
    /**
     * Gets the type identifier of the image referenced.
     *
     * @param me
     */
    char * (*get_type)(struct kmz_image_t *);
    
    /**
     * Gets the size of the image referenced.
     *
     * @param me
     */
    kmz_rectangle (*get_dimen)(struct kmz_image_t *);
    
    /**
     * Gets an ARGB color at the given point within the image referenced.
     *
     * @param me
     * @param point
     */
    kmz_color_32 (*get_argb_at)(struct kmz_image_t *, kmz_point);
    
    /**
     * Sets an ARGB color at the given point within the image referenced.
     *
     * @param me
     * @param point
     * @param color
     */
    void (*set_argb_at)(struct kmz_image_t *, kmz_point, kmz_color_32);
    
    /**
     * Gets an ARGB matrix at the given point within the image referenced.
     *
     * @param me
     * @param point
     */
    KmzMatrix (*get_matrix_at)(struct kmz_image_t *, kmz_point, size_t);
    
    /**
     * Gets whether or not the point is within the image referenced.
     *
     * @param me
     * @param point
     */
    size_t (*is_valid)(struct kmz_image_t *, kmz_point);
    
    /**
     * Frees the image referenced.
     *
     * @param me
     */
    void (*free)(struct kmz_image_t *);
};
typedef struct kmz_image_t KmzImage;

// region Functions:
char * KmzImage__get_type(KmzImage * me);

struct kmz_rectangle_t KmzImage__get_dimen(KmzImage * me);

kmz_color_32 KmzImage__get_argb_at(KmzImage * me, kmz_point point);

kmz_color_32 KmzImage__get_argb_at_x_y(KmzImage * me, size_t x, size_t y);

void KmzImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color);

void KmzImage__set_argb_at_x_y(KmzImage * me, size_t x, size_t y, kmz_color_32 color);

KmzMatrix KmzImage__get_matrix(KmzImage * me, size_t size);

KmzMatrix KmzImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size);

KmzMatrix KmzImage__get_matrix_at_x_y(KmzImage * me, size_t x, size_t y, size_t size);

size_t KmzImage__is_valid(KmzImage * me, kmz_point point);

size_t KmzImage__is_valid_x_y(KmzImage * me, size_t x, size_t y);

void KmzImage__free(KmzImage * me);
// endregion;

#endif /* kmz_image_h */
