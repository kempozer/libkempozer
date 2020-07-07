#ifndef kmz_transform_h
#define kmz_transform_h

#include <stdio.h>
#include <stdlib.h>
#include "kmz_core.h"
#include "kmz_color.h"
#include "kmz_geometry.h"

typedef kmz_color_32 (*KmzColorTransform)(kmz_color_32);

typedef kmz_color_32 (*KmzMatrixTransform)(KmzMatrix *);

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform(KmzColorTransform transformation, KmzImage * image);

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform_from(KmzColorTransform transformation, kmz_point pos, KmzImage * image);

/**
 * Applies the given transformation function to each pixel within the image.
 */
void kmz_apply_color_transform_in(KmzColorTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform(KmzMatrixTransform transformation, KmzImage * image, size_t size);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform_from(KmzMatrixTransform transformation, kmz_point pos, KmzImage * image, size_t size);

/**
 * Applies the given matrix transformation function to each pixel within the image.
 */
void kmz_apply_matrix_transform_in(KmzMatrixTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image, size_t size);

#endif /* kmz_transform_h */
