#ifndef kmz_matrix_h
#define kmz_matrix_h

#include <stdio.h>
#include "kmz_geometry.h"
#include "kmz_color.h"

/**
 * Provides an interface for interacting with an abstract matrix. Implements of this struct must provide a construction interface as well as implement every function exposed.
 */
struct kmz_matrix_t;
struct kmz_matrix_t {

    /**
     * Gets the type identifier of the matrix referenced.
     *
     * @param me
     */
    char * (*get_type)(struct kmz_matrix_t *);

    /**
     * Gets the size of the matrix referenced.
     *
     * @param me
     */
    size_t (*get_size)(struct kmz_matrix_t *);

    /**
     * Gets the position of the matrix referenced.
     *
     * @param me
     */
    kmz_point (*get_pos)(struct kmz_matrix_t *);

    /**
     * Sets the position of the matrix referenced.
     *
     * @param me
     * @param point
     */
    void (*set_pos)(struct kmz_matrix_t *, kmz_point);

    /**
     * Gets an ARGB color at the given point within the matrix referenced.
     *
     * @param me
     * @param point
     */
    kmz_color_32 (*get_color_at)(struct kmz_matrix_t *, kmz_point);

    /**
     * Sets an ARGB color at the given point within the matrix referenced.
     *
     * @param me
     * @param point
     * @param color
     */
    void (*set_color_at)(struct kmz_matrix_t *, kmz_point, kmz_color_32);

    /**
     * Determines if the given point lies within the matrix referenced.
     *
     * @param me
     * @param point
     */
    size_t (*is_valid)(struct kmz_matrix_t *, kmz_point);

    /**
     * Frees the matrix referenced.
     */
    void (*free)(struct kmz_matrix_t *);
};
typedef struct kmz_matrix_t KmzMatrix;

// region Functions:
char * KmzMatrix__get_type(KmzMatrix * me);

size_t KmzMatrix__get_size(KmzMatrix * me);

kmz_point KmzMatrix__get_pos(KmzMatrix * me);

void KmzMatrix__set_pos(KmzMatrix * me, kmz_point point);

void KmzMatrix__set_pos_x_y(KmzMatrix * me, size_t x, size_t y);

kmz_color_32 KmzMatrix__get_color_at(KmzMatrix * me, kmz_point point);

kmz_color_32 KmzMatrix__get_color_at_x_y(KmzMatrix * me, size_t x, size_t y);

void KmzMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color);

void KmzMatrix__set_color_at_x_y(KmzMatrix * me, size_t x, size_t y, kmz_color_32 color);

size_t KmzMatrix__is_valid(KmzMatrix * me, kmz_point point);

size_t KmzMatrix__is_valid_x_y(KmzMatrix * me, size_t x, size_t y);

void KmzMatrix__free(KmzMatrix * me);
// endregion;

#endif /* kmz_matrix_h */
