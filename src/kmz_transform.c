//
//  kmz_transform.c
//  checker
//
//  Created by Bryan Wofter on 7/6/20.
//  Copyright © 2020 dirtypixels. All rights reserved.
//

#include "kmz_transform.h"

ssize_t _kmz_clamp(ssize_t val, ssize_t min, ssize_t max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

void kmz_apply_color_transform(KmzColorTransform transformation, KmzImage * image) {
    kmz_apply_color_transform_in(transformation, kmz_point__ZERO, KmzImage__get_dimen(image), image);
}

void kmz_apply_color_transform_from(KmzColorTransform transformation, kmz_point pos, KmzImage * image) {
    kmz_apply_color_transform_in(transformation, pos, KmzImage__get_dimen(image), image);
}

void kmz_apply_color_transform_in(KmzColorTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image) {
    const kmz_rectangle i_dimen = KmzImage__get_dimen(image);
    
    size_t i_h = i_dimen.h,
           i_w = i_dimen.w;
    
    size_t x = _kmz_clamp(pos.x, 0, i_w),
           y = _kmz_clamp(pos.y, 0, i_h),
           max_x = _kmz_clamp(dimen.w, x, i_w),
           max_y = _kmz_clamp(dimen.h, y, i_h);
    
    kmz_point p = {};
    for (p.y = y; p.y < max_y; ++p.y) {
        for (p.x = x; p.x < max_x; ++p.x) {
            KmzImage__set_argb_at(image, p, transformation(KmzImage__get_argb_at(image, p)));
        }
    }
}

void kmz_apply_matrix_transform(KmzMatrixTransform transformation, KmzImage * image, size_t size) {
    kmz_apply_matrix_transform_in(transformation, kmz_point__ZERO, KmzImage__get_dimen(image), image, size);
}

void kmz_apply_matrix_transform_from(KmzMatrixTransform transformation, kmz_point pos, KmzImage * image, size_t size) {
    kmz_apply_matrix_transform_in(transformation, pos, KmzImage__get_dimen(image), image, size);
}

void kmz_apply_matrix_transform_in(KmzMatrixTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image, size_t size) {
    const kmz_rectangle i_dimen = KmzImage__get_dimen(image);
    
    size_t i_h = i_dimen.h,
           i_w = i_dimen.w;
    
    size_t x = _kmz_clamp(pos.x, 0, i_w),
           y = _kmz_clamp(pos.y, 0, i_h),
           max_x = _kmz_clamp(dimen.w, x, i_w),
           max_y = _kmz_clamp(dimen.h, y, i_h);
    
    KmzMatrix * matrix = KmzImage__get_matrix(image, size);

    kmz_point p = {};
    for (p.y = y; p.y < max_y; ++p.y) {
        for (p.x = x; p.x < max_x; ++p.x) {
            KmzMatrix__set_pos(matrix, p);
            KmzImage__set_argb_at(image, p, transformation(matrix));
        }
    }
    
    KmzMatrix__free(matrix);
    free(matrix);
}
