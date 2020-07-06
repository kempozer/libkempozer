//
//  kmz_core.h
//  checker
//
//  Created by Bryan Wofter on 7/6/20.
//  Copyright © 2020 dirtypixels. All rights reserved.
//

#ifndef kmz_core_h
#define kmz_core_h

#include <stdio.h>
#include "kmz_image.h"
#include "kmz_matrix.h"
#include "kmz_gd_2x_image_file.h"
#include "kmz_color.h"
#include "kmz_geometry.h"
#include <assert.h>

/**
 * Creates a new KmzImage using the built-in KmzImage type for the given GD 2x image file.
 */
KmzImage * kmz_make_image_from_gd_x2(KmzGd2xImageFile image);

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image(KmzImage * image,
                                   size_t size);

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image_and_pos(KmzImage * image,
                                           kmz_point point,
                                           size_t size);

/**
 * Creates a new KmzMatrix using the built-in KmzMatrix type for the given image.
 */
KmzMatrix * kmz_make_matrix_from_image_and_pos_x_y(KmzImage * image,
                                               ssize_t x,
                                               ssize_t y,
                                               size_t size);

#endif /* kmz_core_h */
