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
    kmz_apply_color_transform_in(transformation, kmz_point__ZERO, image->dimen, image);
}

void kmz_apply_color_transform_from(KmzColorTransform transformation, kmz_point pos, KmzImage * image) {
    kmz_apply_color_transform_in(transformation, pos, image->dimen, image);
}

void kmz_apply_color_transform_in(KmzColorTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image) {
    size_t x = _kmz_clamp(pos.x, 0, image->dimen.w),
           y = _kmz_clamp(pos.y, 0, image->dimen.h),
           max_x = _kmz_clamp(dimen.w, x, image->dimen.w),
           max_y = _kmz_clamp(dimen.h, y, image->dimen.h);
    
    kmz_point p = {.x=0, .y=0};
    for (p.y = y; p.y < max_y; ++p.y) {
        for (p.x = x; p.x < max_x; ++p.x) {
            KmzImage__set_argb_at(image, p, transformation(KmzImage__get_argb_at(image, p)));
        }
    }
}

void kmz_apply_matrix_transform(KmzMatrixTransform transformation, KmzImage * image, size_t size) {
    kmz_apply_matrix_transform_in(transformation, kmz_point__ZERO, image->dimen, image, size);
}

void kmz_apply_matrix_transform_from(KmzMatrixTransform transformation, kmz_point pos, KmzImage * image, size_t size) {
    kmz_apply_matrix_transform_in(transformation, pos, image->dimen, image, size);
}

void kmz_apply_matrix_transform_in(KmzMatrixTransform transformation, kmz_point pos, kmz_rectangle dimen, KmzImage * image, size_t size) {
    size_t x = _kmz_clamp(pos.x, 0, image->dimen.w),
           y = _kmz_clamp(pos.y, 0, image->dimen.h),
           max_x = _kmz_clamp(dimen.w, x, image->dimen.w),
           max_y = _kmz_clamp(dimen.h, y, image->dimen.h);
    
    KmzMatrix * matrix = KmzImage__get_matrix(image, size);

    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            KmzImage__set_argb_at(image, matrix->pos, transformation(matrix));
        }
    }
    free(matrix);
}
