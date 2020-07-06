//
//  kmz_core.c
//  checker
//
//  Created by Bryan Wofter on 7/6/20.
//  Copyright © 2020 dirtypixels. All rights reserved.
//

#include "kmz_core.h"

static const char * _KMZ_CORE_STD_IMAGE_TYPE = "Kmz.Core.Std.Image";
static const char * _KMZ_CORE_STD_MATRIX_TYPE = "Kmz.Core.Std.Matrix";

// region Matrix:
struct _kmz_core_std_matrix_body_t {
    size_t size;
    size_t freed;
    size_t hsize;
    kmz_point pos;
    KmzImage * image;
};
typedef struct _kmz_core_std_matrix_body_t _KmzCoreStdMatrixBody;

struct _kmz_core_std_matrix_t {
    KmzMatrix header;
    _KmzCoreStdMatrixBody body;
};
typedef struct _kmz_core_std_matrix_t _KmzCoreStdMatrix;

const char * _KmzCoreStdMatrix__get_type(KmzMatrix * me) {
    return _KMZ_CORE_STD_MATRIX_TYPE;
}

size_t _KmzCoreStdMatrix__get_size(KmzMatrix * me) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        return this->body.size;
    }
    // TODO: Implement error flag
    return 0;
}

kmz_point _KmzCoreStdMatrix__get_pos(KmzMatrix * me) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        return this->body.pos;
    }
    // TODO: Implement error flag
    return kmz_point__ZERO;
}

void _KmzCoreStdMatrix__set_pos(KmzMatrix * me, kmz_point point) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        this->body.pos = point;
    }
    // TODO: Implement error flag
}

ssize_t _KmzCoreStdMatrix__clamp(ssize_t val, ssize_t min, ssize_t max) {
    if (val < min) {
        return min;
    } else if (val > max) {
        return max;
    }
    return val;
}

kmz_point _KmzCoreStdMatrix__clamp_point(_KmzCoreStdMatrix * this, kmz_point point) {
    const kmz_rectangle dimen = KmzImage__get_dimen(this->body.image);
    const ssize_t x = this->body.pos.x + (point.x - this->body.hsize),
                  y = this->body.pos.y + (point.y - this->body.hsize);
    const kmz_point p = {
        .x=_KmzCoreStdMatrix__clamp(x, 0, dimen.w - 1),
        .y=_KmzCoreStdMatrix__clamp(y, 0, dimen.h - 1)
    };
    
    return p;
}

kmz_color_32 _KmzCoreStdMatrix__get_color_at(KmzMatrix * me, kmz_point point) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        return KmzImage__get_argb_at(this->body.image, _KmzCoreStdMatrix__clamp_point(this, point));
    }
    // TODO: Implement error flag
    return 0x00000000;
}

void _KmzCoreStdMatrix__set_color_at(KmzMatrix * me, kmz_point point, kmz_color_32 color) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        KmzImage__set_argb_at(this->body.image, _KmzCoreStdMatrix__clamp_point(this, point), color);
    }
    // TODO: Implement error flag
}

void _KmzCoreStdMatrix__free(KmzMatrix * me) {
    if (KmzMatrix__get_type(me) == _KMZ_CORE_STD_MATRIX_TYPE &&
        me->get_type == _KmzCoreStdMatrix__get_type) {
        _KmzCoreStdMatrix * this = (void*)me;
        
        if (0 == this->body.freed) {
            this->body.freed = 1;
            this->body.size = 0;
            this->body.hsize = 0;
            this->body.pos = kmz_point__ZERO;
            this->body.image = NULL;
        }
    }
}

static const KmzMatrix _KmzCoreStdMatrix__methods = {
    .get_type=&_KmzCoreStdMatrix__get_type,
    .get_size=&_KmzCoreStdMatrix__get_size,
    .get_pos=&_KmzCoreStdMatrix__get_pos,
    .set_pos=&_KmzCoreStdMatrix__set_pos,
    .get_color_at=&_KmzCoreStdMatrix__get_color_at,
    .set_color_at=&_KmzCoreStdMatrix__set_color_at,
    .free=&_KmzCoreStdMatrix__free,
};

KmzMatrix * make_matrix_from_image(KmzImage * image,
                                   size_t size) {
    return make_matrix_from_image_and_pos(image, kmz_point__ZERO, size);
}

KmzMatrix * make_matrix_from_image_and_pos(KmzImage * image,
                                           kmz_point point,
                                           size_t size) {
    _KmzCoreStdMatrix * this = malloc(sizeof(_KmzCoreStdMatrix));
    this->header = _KmzCoreStdMatrix__methods;
    this->body.freed = 0;
    this->body.hsize = size / 2;
    this->body.image = image;
    this->body.pos = point;
    this->body.size = size;
    return (void*)this;
}

KmzMatrix * make_matrix_from_image_and_pos_x_y(KmzImage * image,
                                               ssize_t x,
                                               ssize_t y,
                                               size_t size) {
    const kmz_point point = {.x=x, .y=y};
    
    return make_matrix_from_image_and_pos(image, point, size);
}
// endregion;

// region Image:
struct _kmz_core_std_image_body_t {
    kmz_rectangle dimen;
    size_t freed;
    size_t len;
    kmz_color_32 * pixels;
};
typedef struct _kmz_core_std_image_body_t _KmzCoreStdImageBody;

struct _kmz_core_std_image_t {
    KmzImage header;
    _KmzCoreStdImageBody image;
};
typedef struct _kmz_core_std_image_t _KmzCoreStdImage;

const char * _KmzCoreStdImage__get_type(KmzImage * me) {
    return _KMZ_CORE_STD_IMAGE_TYPE;
}

kmz_rectangle _KmzCoreStdImage__get_dimen(KmzImage * me) {
    if (KmzImage__get_type(me) == _KMZ_CORE_STD_IMAGE_TYPE &&
        me->get_type == _KmzCoreStdImage__get_type) {
        _KmzCoreStdImage * this = (void*)me;
        
        return this->image.dimen;
    }
    // TODO: Implement error flag
    return kmz_rectangle__ZERO;
}

ssize_t _KmzCoreStdImage__get_index(_KmzCoreStdImage * this, kmz_point point) {
    return ((this->image.dimen.w * point.y) + point.x);
}

kmz_color_32 _KmzCoreStdImage__get_argb_at(KmzImage * me, kmz_point point) {
    if (KmzImage__get_type(me) == _KMZ_CORE_STD_IMAGE_TYPE &&
        me->get_type == _KmzCoreStdImage__get_type) {
        _KmzCoreStdImage * this = (void*)me;
        const ssize_t i = _KmzCoreStdImage__get_index(this, point);
        
        if (i > -1) {
            return this->image.pixels[i];
        }
    }
    // TODO: Implement error flag
    return 0x00000000;
}

void _KmzCoreStdImage__set_argb_at(KmzImage * me, kmz_point point, kmz_color_32 color) {
    if (KmzImage__get_type(me) == _KMZ_CORE_STD_IMAGE_TYPE &&
           me->get_type == _KmzCoreStdImage__get_type) {
        _KmzCoreStdImage * this = (void*)me;
        const ssize_t i = _KmzCoreStdImage__get_index(this, point);
        
        if (i > -1) {
            this->image.pixels[i] = color;
        }
    }
    // TODO: Implement error flag
}

KmzMatrix * _KmzCoreStdImage__get_matrix_at(KmzImage * me, kmz_point point, size_t size) {
    return make_matrix_from_image_and_pos(me, point, size);
}

size_t _KmzCoreStdImage__is_valid(KmzImage * me, kmz_point point) {
    if (KmzImage__get_type(me) == _KMZ_CORE_STD_IMAGE_TYPE &&
        me->get_type == _KmzCoreStdImage__get_type) {
        _KmzCoreStdImage * this = (void*)me;
        
        return (this->image.dimen.w > point.x && point.x > -1 &&
                this->image.dimen.h > point.y && point.y > -1);
    }
    return 0;
}

void _KmzCoreStdImage__free(KmzImage * me) {
    if (KmzImage__get_type(me) == _KMZ_CORE_STD_IMAGE_TYPE &&
        me->get_type == _KmzCoreStdImage__get_type) {
        _KmzCoreStdImage * this = (void*)me;
        
        if (0 == this->image.freed) {
            this->image.freed = 1;
            free(this->image.pixels);
        }
    }
}

static const KmzImage _KmzCoreStdImage__methods = {
    .get_type=&_KmzCoreStdImage__get_type,
    .get_dimen=&_KmzCoreStdImage__get_dimen,
    .get_argb_at=&_KmzCoreStdImage__get_argb_at,
    .set_argb_at=&_KmzCoreStdImage__set_argb_at,
    .get_matrix_at=&_KmzCoreStdImage__get_matrix_at,
    .is_valid=&_KmzCoreStdImage__is_valid,
    .free=&_KmzCoreStdImage__free,
};

KmzImage * make_image_from_gd_x2(KmzGd2xImageFile image) {
    _KmzCoreStdImage * this = malloc(sizeof(_KmzCoreStdImage));
    this->header = _KmzCoreStdImage__methods;
    this->image.dimen = image.header.signature.dimen;
    this->image.freed = 0;
    this->image.len = this->image.dimen.h * this->image.dimen.w;
    this->image.pixels = calloc(this->image.len, sizeof(kmz_color_32));
    
    if (image.header.color.is_truecolor) {
        memcpy(this->image.pixels, image.pixels, this->image.len);
    } else {
        for (size_t i = 0; i < this->image.len; ++i) {
            this->image.pixels[i] = image.header.color.value.palette.palette[image.pixels[i]];
        }
    }
    
    return (void*)this;
}
// endregion;
