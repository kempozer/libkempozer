#include "kmz_gd_2x_image_file.h"
// region Helpers:

int _kmz_read_byte(FILE * f, uint8_t * r) {
    if (1 == fread(r, sizeof(uint8_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

int _kmz_write_byte(FILE * f, uint8_t v) {
    if (1 == fwrite(&v, sizeof(uint8_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

int _kmz_read_short(FILE * f, uint16_t * r) {
    if (1 == fread(r, sizeof(uint16_t), 1, f)) {
        *r = ntohs(*r);
        return 0;
    }
    return ferror(f);
}

int _kmz_write_short(FILE * f, uint16_t v) {
    v = htons(v);
    if (1 == fwrite(&v, sizeof(uint16_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

int _kmz_read_int_buffer(FILE * f, uint32_t * r, size_t s) {
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fread(r + total, sizeof(uint32_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fread(r + total, sizeof(uint32_t), remainder, f);
    }
    if (s == total) {
        for (size_t i = 0; i < s; ++i) {
            r[i] = ntohl(r[i]);
        }
        return 0;
    }
    return ferror(f);
}

int _kmz_write_int_buffer(FILE * f, uint32_t * r, size_t s) {
    for (size_t i = 0; i < s; ++i) {
        r[i] = htonl(r[i]);
    }
    size_t total = 0, remainder = s;
    while (remainder > 8192 && !feof(f)) {
        total += fwrite(r + total, sizeof(uint32_t), 8192, f);
        remainder -= 8192;
    }
    if (remainder && !feof(f)) {
        total += fwrite(r + total, sizeof(uint32_t), remainder, f);
    }
    return s == total ? 0 : ferror(f);
}

int _kmz_read_int(FILE * f, uint32_t * r) {
    if (1 == fread(r, sizeof(uint32_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}

int _kmz_write_int(FILE * f, uint32_t v) {
    if (1 == fwrite(&v, sizeof(uint32_t), 1, f)) {
        return 0;
    }
    return ferror(f);
}
// endregion;

// region Functions:

kmz_gd_2x_image_file_status kmz_read_gd_2x_image_file(FILE * f, KmzGd2xImageFile * o) {
    if (NULL == f) {
        return ERR_INVALID_FILE_PTR;
    } else if (NULL == o) {
        return ERR_INVALID_IMAGE_PTR;
    }
    
    int r;
    if (0 != (r = _kmz_read_short(f, &o->header.signature.type))) {
        return ERR_READ_SIGNATURE;
    }
    if (0 != (r = _kmz_read_short(f, &o->header.signature.dimen.w))) {
        return ERR_READ_WIDTH;
    }
    if (0 != (r = _kmz_read_short(f, &o->header.signature.dimen.h))) {
        return ERR_READ_HEIGHT;
    }
    if (0 != (r = _kmz_read_byte(f, &o->header.color.is_truecolor))) {
        return ERR_READ_IS_TRUECOLOR;
    }
    
    switch (o->header.signature.type) {
        case KMZ_GD_2x_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_read_int(f, &o->header.color.value.truecolor.transparent)) {
                return ERR_READ_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2x_IMAGE_FILE_PALETTE:
            // TODO: Implement palette image loading
            return ERR_UNSUPPORTED_OPERATION;
    }
    
    size_t len = o->header.signature.dimen.w * o->header.signature.dimen.h;
    size_t is_truecolor = o->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR;
    o->header.color.is_truecolor = is_truecolor;
    
    if (is_truecolor) {
        o->pixels = calloc(len, sizeof(kmz_color_32));
        if (0 != _kmz_read_int_buffer(f, o->pixels, len)) {
            return ERR_READ_PIXELS;
        }
    } else {
        return ERR_UNKNOWN;
    }
    
    return OK;
}


kmz_gd_2x_image_file_status kmz_write_gd_2x_image_file(FILE * f, KmzGd2xImageFile * i) {
    if (NULL == f) {
        return ERR_INVALID_FILE_PTR;
    } else if (NULL == i) {
        return ERR_INVALID_IMAGE_PTR;
    }
    
    if (0 != _kmz_write_short(f, i->header.signature.type)) {
        return ERR_WRITE_SIGNATURE;
    }
    if (0 != _kmz_write_short(f, i->header.signature.dimen.w)) {
        return ERR_WRITE_WIDTH;
    }
    if (0 != _kmz_write_short(f, i->header.signature.dimen.h)) {
        return ERR_WRITE_HEIGHT;
    }
    if (0 != _kmz_write_byte(f, i->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR)) {
        return ERR_WRITE_IS_TRUECOLOR;
    }
    
    switch (i->header.signature.type) {
        case KMZ_GD_2x_IMAGE_FILE_TRUECOLOR:
            if (0 != _kmz_write_int(f, i->header.color.value.truecolor.transparent)) {
                return ERR_WRITE_TRUECOLOR_TRANSPARENT;
            }
            break;
        case KMZ_GD_2x_IMAGE_FILE_PALETTE:
            // TODO: Implement palette image writing
            return ERR_UNSUPPORTED_OPERATION;
    }
    
    size_t len = i->header.signature.dimen.w * i->header.signature.dimen.h;
    size_t is_truecolor = i->header.signature.type == KMZ_GD_2x_IMAGE_FILE_TRUECOLOR;
    i->header.color.is_truecolor = is_truecolor;
    
    if (is_truecolor) {
        if (0 != _kmz_write_int_buffer(f, i->pixels, len)) {
            return ERR_WRITE_PIXELS;
        }
    } else {
        // TODO: Implement palette image writing
        return ERR_UNSUPPORTED_OPERATION;
    }
    return OK;
}

const char * kmz_status_msg(kmz_gd_2x_image_file_status status) {
    switch (status) {
        case OK:
            return NULL;
        case ERR_INVALID_FILE_PTR:
            return "An invalid file pointer has been provided";
        case ERR_INVALID_IMAGE_PTR:
            return "An invalid image pointer has been provided";
        case ERR_READ_SIGNATURE:
            return "An error has occurred while reading the GD 2x header signature";
        case ERR_WRITE_SIGNATURE:
            return "An error has occurred while writing the GD 2x header signature";
        case ERR_READ_WIDTH:
            return "An error has occurred while reading the GD 2x header width";
        case ERR_READ_HEIGHT:
            return "An error has occurred while reading the GD 2x header height";
        case ERR_WRITE_WIDTH:
            return "An error has occurred while writing the GD 2x header width";
        case ERR_WRITE_HEIGHT:
            return "An error has occurred while writing the GD 2x header height";
        case ERR_READ_IS_TRUECOLOR:
            return "An error has occurred while reading the GD 2x header truecolor flag";
        case ERR_WRITE_IS_TRUECOLOR:
            return "An error has occurred while writing the GD 2x header truecolor flag";
        case ERR_READ_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header truecolor transparent color";
        case ERR_WRITE_TRUECOLOR_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header truecolor transparent color";
        case ERR_READ_PALETTE_COUNT:
            return "An error has occurred while reading the GD 2x header palette count";
        case ERR_WRITE_PALETTE_COUNT:
            return "An error has occurred while writing the GD 2x header palette count";
        case ERR_READ_PALETTE_TRANSPARENT:
            return "An error has occurred while reading the GD 2x header palette transparent color";
        case ERR_WRITE_PALETTE_TRANSPARENT:
            return "An error has occurred while writing the GD 2x header palette transparent color";
        case ERR_READ_PALETTE_COLORS:
            return "An error has occurred while reading the GD 2x header palette colors";
        case ERR_WRITE_PALETTE_COLORS:
            return "An error has occurred while writing the GD 2x header palette colors";
        case ERR_READ_PIXELS:
            return "An error has occurred while reading the GD 2x pixels";
        case ERR_WRITE_PIXELS:
            return "An error has occurred while writing the GD 2x pixels";
        case ERR_UNSUPPORTED_OPERATION:
            return "An unsupported operation has been encountered";
        case ERR_UNKNOWN:
            return "An unknown error has occurred";
    }
}

const char * kmz_status_msg_with_err_code(kmz_gd_2x_image_file_status status, int error) {
    const char * msg = kmz_status_msg(status);
    char * o = calloc(strlen(msg) + 24, sizeof(char));
    sprintf(o, "%s: %d", msg, error);
    return o;
}

// endregion;
