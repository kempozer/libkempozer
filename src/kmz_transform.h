#ifndef kmz_transform_h
#define kmz_transform_h

#include <stdio.h>
#include <stdlib.h>
#include "kmz_core.h"
#include "kmz_color.h"
#include "kmz_geometry.h"

typedef kmz_color_32 (*KmzColorTransform)(kmz_color_32);

typedef kmz_color_32 (*KmzMatrixTransform)(KmzMatrix *);

// region Transform List:
/**
 * Provides an individual node within a KmzTransformList.
 */
struct kmz_transform_node_t;
struct kmz_transform_node_t {
    uint8_t is_matrix_transform;
    union { KmzColorTransform color; KmzMatrixTransform matrix; } value;
    struct kmz_transform_node_t * prev;
    struct kmz_transform_node_t * next;
};
typedef struct kmz_transform_node_t KmzTransformNode;

/**
 * Provides a linked list containing multiple transformation functions that should be applied during a composite transform.
 */
struct kmz_transform_list_t {
    KmzTransformNode * head;
    KmzTransformNode * tail;
};
typedef struct kmz_transform_list_t KmzTransformList;

void kmz_transform_list_push_color(KmzTransformList * list, KmzColorTransform transform);

void kmz_transform_list_push_matrix(KmzTransformList * list, KmzMatrixTransform transform);

KmzTransformNode * kmz_transform_list_pop(KmzTransformList * list);

void kmz_transform_list_unshift_color(KmzTransformList * list, KmzColorTransform transform);

void kmz_transform_list_unshift_matrix(KmzTransformList * list, KmzMatrixTransform transform);

KmzTransformNode * kmz_transform_list_dequeue(KmzTransformList * list);

#define kmz_transform_list_push(list, transform) _Generic((transform), \
    KmzColorTransform: kmz_transform_list_push_color, \
    KmzMatrixTransform: kmz_transform_list_push_matrix \
)(list, transform)

#define kmz_transform_list_unshift(list, transform) _Generic((transform), \
    KmzColorTransform: kmz_transform_list_unshift_color, \
    KmzMatrixTransform: kmz_transform_list_unshift_matrix \
)(list, transform)
// endregion;

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform(KmzColorTransform transformation,
                               KmzImage * image);

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform_from(KmzColorTransform transformation,
                                    KmzPoint pos,
                                    KmzImage * image);

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform_in(KmzColorTransform transformation,
                                  KmzPoint pos,
                                  KmzRectangle dimen,
                                  KmzImage * image);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform(KmzMatrixTransform transformation,
                                KmzImage * image,
                                size_t size);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform_from(KmzMatrixTransform transformation,
                                     KmzPoint pos,
                                     KmzImage * image,
                                     size_t size);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform_in(KmzMatrixTransform transformation,
                                   KmzPoint pos,
                                   KmzRectangle dimen,
                                   KmzImage * image,
                                   size_t size);

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform(KmzTransformList transformation,
                                  KmzImage * image,
                                  size_t size);

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform_from(KmzTransformList transformation,
                                       KmzPoint pos,
                                       KmzImage * image,
                                       size_t size);

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform_in(KmzTransformList transformation,
                                     KmzPoint pos,
                                     KmzRectangle dimen,
                                     KmzImage * image,
                                     size_t size);

#endif /* kmz_transform_h */
