/*-
  BSD 3-Clause License

  Copyright (c) 2020, Kempozer
  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

  1. Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

  2. Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

  3. Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  */

#include "kmz_image_file.h"

struct kmz_image_file_t {
    const KmzImageFileType * _type;
    void * _me;
};

KmzImageFile * const KmzImageFile__new(const KmzImageFileType * const restrict type, const void * const restrict argv) {
    KmzImageFile * const restrict ptr = malloc(sizeof(KmzImageFile));

    if (NULL == ptr) {
        return NULL;
    }

    ptr->_type = type;
    ptr->_me = ptr->_type->_new();
    if (NULL == ptr->_me) {
        free(ptr);
        return NULL;
    }

    if (ptr->_type->_ctor) {
        ptr->_type->_ctor(ptr->_me, argv);
    }
    return ptr;
}

void KmzImageFile__free(KmzImageFile * const restrict me) {
    if (NULL == me->_type->_dtor) {
        free(me->_me);
    } else {
        me->_type->_dtor(me->_me);
    }
    free(me);
}

const KmzImageFileType * const KmzImageFile__type(const KmzImageFile * const restrict me) {
    return me->_type;
}

const KmzSize KmzImageFile__dimen(const KmzImageFile * const restrict me) {
    return me->_type->dimen(me->_me);
}

const KmzImageFileColorType KmzImageFile__color_type(const KmzImageFile * const restrict me) {
    return me->_type->color_type(me->_me);
}

const KmzImageFileStatus KmzImageFile__status(const KmzImageFile * const restrict me) {
    return me->_type->status(me->_me);
}

const char * const KmzImageFile__status_msg(const KmzImageFile * const restrict me, const KmzImageFileStatus status) {
    const char * status_msg = me->_type->status_msg(me->_me, status);

    if (NULL == status_msg) {

    }

    return status_msg;
}

const KmzImageFileStatus KmzImageFile__save(KmzImageFile * const restrict me, const char * const restrict path) {
    FILE * const restrict file = fopen(path, "wb+");

    if (NULL == file) {
        return KMZ_IMAGE_FILE_ERR_WRITE_FAILED;
    }

    const KmzImageFileStatus status = KmzImageFile__save_to(me, file);

    fclose(file);
    return status;
}

const KmzImageFileStatus KmzImageFile__save_to(KmzImageFile * const restrict me, FILE * const restrict path) {
    return me->_type->save_to(me->_me, path);
}

const KmzImageFileStatus KmzImageFile__load(KmzImageFile * const restrict me, const char * const restrict path) {
    FILE * const restrict file = fopen(path, "rb+");

    if (NULL == file) {
        return KMZ_IMAGE_FILE_ERR_READ_FAILED;
    }

    const KmzImageFileStatus status = KmzImageFile__load_from(me, file);

    fclose(file);
    return status;
}

const KmzImageFileStatus KmzImageFile__load_from(KmzImageFile * const restrict me, FILE * const restrict path) {
    return me->_type->load_from(me->_me, path);
}

const size_t KmzImageFile__palette_color_count(const KmzImageFile * const restrict me) {
    if (me->_type->palette_color_count) {
        return me->_type->palette_color_count(me->_me);
    }
    return 0;
}

const KmzImageFileStatus KmzImageFile__read_palette_colors(KmzImageFile * const restrict me, kmz_color_32 * const restrict buffer) {
    if (me->_type->read_palette_colors) {
        return me->_type->read_palette_colors(me->_me, buffer);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_PALETTE_IMAGE;
}

const KmzImageFileStatus KmzImageFile__read_palette_pixels(KmzImageFile * const restrict me, uint8_t * const restrict buffer) {
    if (me->_type->read_palette_pixels) {
        return me->_type->read_palette_pixels(me->_me, buffer);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_PALETTE_IMAGE;
}

const KmzImageFileStatus KmzImageFile__read_truecolor_pixels(KmzImageFile * const restrict me, kmz_color_32 * const restrict buffer) {
    if (me->_type->read_truecolor_pixels) {
        return me->_type->read_truecolor_pixels(me->_me, buffer);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_TRUECOLOR_IMAGE;
}

const KmzImageFileStatus KmzImageFile__read_ahsl_pixels(KmzImageFile * const restrict me, KmzAhslColor * const restrict buffer) {
    if (me->_type->read_ahsl_pixels) {
        return me->_type->read_ahsl_pixels(me->_me, buffer);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_AHSL_IMAGE;
}

const KmzImageFileStatus KmzImageFile__set_palette_image(KmzImageFile * const restrict me,
        const size_t color_count,
        const kmz_color_32 * restrict palette,
        const KmzSize dimen,
        uint8_t * const restrict pixels,
        const KmzBool copy_source) {
    if (me->_type->set_palette_image) {
        return me->_type->set_palette_image(me->_me, color_count, palette, dimen, pixels, copy_source);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_PALETTE_IMAGE;
}

const KmzImageFileStatus KmzImageFile__set_truecolor_image(KmzImageFile * const restrict me,
        const KmzSize dimen,
        kmz_color_32 * const restrict buffer,
        const KmzBool copy_source) {
    if (me->_type->set_truecolor_image) {
        return me->_type->set_truecolor_image(me->_me, dimen, buffer, copy_source);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_TRUECOLOR_IMAGE;
}

const KmzImageFileStatus KmzImageFile__set_ahsl_image(KmzImageFile * const restrict me,
        const KmzSize dimen,
        KmzAhslColor * const restrict buffer,
        const KmzBool copy_source) {
    if (me->_type->set_ahsl_image) {
        return me->_type->set_ahsl_image(me->_me, dimen, buffer, copy_source);
    }
    return KMZ_IMAGE_FILE_ERR_NOT_AHSL_IMAGE;
}

const KmzBool KmzImageFile__supports_metadata(const KmzImageFile * const restrict me) {
    if (me->_type->supports_metadata) {
        return me->_type->supports_metadata(me->_me);
    }
    return KMZ_FALSE;
}

const KmzBool KmzImageFile__is_supported_metadata(const KmzImageFile * const restrict me, const char * const restrict name) {
    if (me->_type->is_supported_metadata) {
        return me->_type->is_supported_metadata(me->_me, name);
    }
    return KMZ_FALSE;
}

const char * const KmzImageFile__metadata(const KmzImageFile * const restrict me, const char * const restrict name) {
    if (me->_type->metadata) {
        return me->_type->metadata(me->_me, name);
    }
    return NULL;
}

const KmzBool KmzImageFile__has_metadata(const KmzImageFile * const restrict me, const char * const restrict name) {
    if (me->_type->has_metadata) {
        return me->_type->has_metadata(me->_me, name);
    }
    return KMZ_FALSE;
}

const KmzImageFileStatus KmzImageFile__set_metadata(KmzImageFile * const restrict me, const char * const restrict name, const char * const restrict value) {
    if (me->_type->set_metadata) {
        return me->_type->set_metadata(me->_me, name, value);
    }
    return KMZ_IMAGE_FILE_ERR_METADATA_UNSUPPORTED;
}

const KmzImageFileStatus KmzImageFile__remove_metadata(KmzImageFile * const restrict me, const char * const restrict name) {
    if (me->_type->remove_metadata) {
        return me->_type->remove_metadata(me->_me, name);
    }
    return KMZ_IMAGE_FILE_ERR_METADATA_UNSUPPORTED;
}
