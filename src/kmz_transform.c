#include "kmz_transform.h"

// region Transform List:
KmzTransformNode * _kmz_make_transform_node(KmzTransformList * list,
                                            uint8_t is_push,
                                            uint8_t is_matrix_transform) {
    KmzTransformNode * node = malloc(sizeof(KmzTransformNode));
    node->next = NULL;
    node->prev = NULL;
    node->is_matrix_transform = is_matrix_transform;
    if (is_push) {
        if (list->tail) {
            list->tail->next = node;
        } else {
            list->head = node;
        }
        node->prev = list->tail;
        list->tail = node;
    } else {
        if (list->head) {
            list->head->prev = node;
        } else {
            list->tail = node;
        }
        node->next = list->head;
        list->head = node;
    }
    return node;
}

void kmz_transform_list_push_color(KmzTransformList * list, KmzColorTransform transform) {
    KmzTransformNode * node = _kmz_make_transform_node(list, 1, 0);
    node->value.color = transform;
}

void kmz_transform_list_push_matrix(KmzTransformList * list, KmzMatrixTransform transform) {
    KmzTransformNode * node = _kmz_make_transform_node(list, 1, 1);
    node->value.matrix = transform;
}

void kmz_transform_list_unshift_color(KmzTransformList * list, KmzColorTransform transform) {
    KmzTransformNode * node = _kmz_make_transform_node(list, 0, 0);
    node->value.color = transform;
}

void kmz_transform_list_unshift_matrix(KmzTransformList * list, KmzMatrixTransform transform) {
    KmzTransformNode * node = _kmz_make_transform_node(list, 0, 1);
    node->value.matrix = transform;
}

KmzTransformNode * kmz_transform_list_pop(KmzTransformList * list) {
    KmzTransformNode * node = NULL;
    if (list->tail) {
        node = list->tail;
        list->tail = node->prev;
        if (list->tail) {
            list->tail->next = NULL;
        } else {
            list->head = NULL;
        }
        node->prev = NULL;
    }
    return node;
}

KmzTransformNode * kmz_transform_list_dequeue(KmzTransformList * list) {
    KmzTransformNode * node = NULL;
    if (list->head) {
        node = list->head;
        list->head = node->next;
        if (list->head) {
            list->head->prev = NULL;
        } else {
            list->tail = NULL;
        }
        node->next = NULL;
    }
    return node;
}
// endregion;

ssize_t _kmz_clamp(ssize_t val, ssize_t min, ssize_t max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

void kmz_apply_color_transform(KmzColorTransform transformation,
                               KmzImage * image) {
    kmz_apply_color_transform_in(transformation, kmz_point__ZERO, image->dimen, image);
}

void kmz_apply_color_transform_from(KmzColorTransform transformation,
                                    kmz_point pos,
                                    KmzImage * image) {
    kmz_apply_color_transform_in(transformation, pos, image->dimen, image);
}

void kmz_apply_color_transform_in(KmzColorTransform transformation,
                                  kmz_point pos,
                                  kmz_rectangle dimen,
                                  KmzImage * image) {
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

void kmz_apply_matrix_transform(KmzMatrixTransform transformation,
                                KmzImage * image,
                                size_t size) {
    kmz_apply_matrix_transform_in(transformation, kmz_point__ZERO, image->dimen, image, size);
}

void kmz_apply_matrix_transform_from(KmzMatrixTransform transformation,
                                     kmz_point pos,
                                     KmzImage * image,
                                     size_t size) {
    kmz_apply_matrix_transform_in(transformation, pos, image->dimen, image, size);
}

void kmz_apply_matrix_transform_in(KmzMatrixTransform transformation,
                                   kmz_point pos,
                                   kmz_rectangle dimen,
                                   KmzImage * image,
                                   size_t size) {
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

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform(KmzTransformList transformation,
                                  KmzImage * image,
                                  size_t size) {
    kmz_apply_compound_transform_in(transformation, kmz_point__ZERO, image->dimen, image, size);
}

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform_from(KmzTransformList transformation,
                                       kmz_point pos,
                                       KmzImage * image,
                                       size_t size) {
    kmz_apply_compound_transform_in(transformation, pos, image->dimen, image, size);
}

/**
 * Applies the given compound transformation function to each pixel within the image.
 */
void kmz_apply_compound_transform_in(KmzTransformList transformation,
                                     kmz_point pos,
                                     kmz_rectangle dimen,
                                     KmzImage * image,
                                     size_t size) {
    size_t x = _kmz_clamp(pos.x, 0, image->dimen.w),
    y = _kmz_clamp(pos.y, 0, image->dimen.h),
    max_x = _kmz_clamp(dimen.w, x, image->dimen.w),
    max_y = _kmz_clamp(dimen.h, y, image->dimen.h);
    
    KmzMatrix * matrix = KmzImage__get_matrix(image, size);
    
    for (matrix->pos.y = y; matrix->pos.y < max_y; ++matrix->pos.y) {
        for (matrix->pos.x = x; matrix->pos.x < max_x; ++matrix->pos.x) {
            kmz_color_32 c;
            KmzTransformNode * node = transformation.head;
            while (node) {
                if (node->is_matrix_transform) {
                    c = node->value.matrix(matrix);
                } else {
                    c = node->value.color(KmzImage__get_argb_at(image, matrix->pos));
                }
                KmzImage__set_argb_at(image, matrix->pos, c);
            }
        }
    }
    free(matrix);
}
