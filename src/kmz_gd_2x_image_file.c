#include "kmz_gd_2x_image_file.h"
// region Helpers:

// endregion;

// region Functions:

kmz_gd_2x_image_file_status kmz_read_gd_2x_image_file(FILE * f, KmzGd2xImageFile * o) {
    return ERR_UNKNOWN;
}


kmz_gd_2x_image_file_status kmz_write_gd_2x_image_file(FILE * f, KmzGd2xImageFile * i) {
    return ERR_UNKNOWN;
}

const char * kmz_status_msg(kmz_gd_2x_image_file_status status) {
    switch (status) {
        case OK:
            return NULL;
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
