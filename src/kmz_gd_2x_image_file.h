#ifndef kmz_gd_image_file_h
#define kmz_gd_image_file_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "kmz_color.h"
#include "kmz_geometry.h"

#define KMZ_GD_2x_IMAGE_FILE_TRUECOLOR 0xFFFE
#define KMZ_GD_2x_IMAGE_FILE_PALETTE 0xFFFF
#define KMZ_GD_2x_IMAGE_NO_TRANSPARENT 0xFFFFFFFF

/**
 * Represents the signature portion of a GD image.
 */
struct kmz_gd_2x_image_file_signature_header_t {
    uint16_t type;
    kmz_rectangle dimen;
};
typedef struct kmz_gd_2x_image_file_signature_header_t KmzGd2xImageFileSignatureHeader;

/**
 * Represents the header of a truecolor image.
 */
struct kmz_gd_2x_image_file_truecolor_header_t {
    kmz_color_32 transparent;
};
typedef struct kmz_gd_2x_image_file_truecolor_header_t KmzGd2xImageFileTruecolorHeader;

/**
 * Represents the header of a palette image.
 */
struct kmz_gd_2x_image_file_palette_header_t {
    uint16_t count;
    kmz_color_32 transparent;
    kmz_color_32 palette[256];
};
typedef struct kmz_gd_2x_image_file_palette_header_t KmzGd2xImageFilePaletteHeader;

/**
 * Represents the chunk of the header that contains color information.
 */
struct kmz_gd_2x_image_file_color_header_t {
    uint8_t is_truecolor;
    union {
        KmzGd2xImageFileTruecolorHeader truecolor;
        KmzGd2xImageFilePaletteHeader palette;
    } value;
};
typedef struct kmz_gd_2x_image_file_color_header_t KmzGd2xImageFileColorHeader;

/**
 * Represents a fully composed header.
 */
struct kmz_gd_2x_image_file_header_t {
    KmzGd2xImageFileSignatureHeader signature;
    KmzGd2xImageFileColorHeader color;
};
typedef struct kmz_gd_2x_image_file_header_t KmzGd2xImageFileHeader;

/**
 * Represents a fully composed image file loaded into RAM.
 */
struct kmz_gd_2x_image_file_t {
    KmzGd2xImageFileHeader header;
    kmz_color_32 * pixels;
};
typedef struct kmz_gd_2x_image_file_t KmzGd2xImageFile;

enum kmz_gd_2x_image_file_status_e {
    OK = 0,
    ERR_READ_SIGNATURE = -1,
    ERR_WRITE_SIGNATURE = -2,
    ERR_READ_WIDTH = -3,
    ERR_READ_HEIGHT = -4,
    ERR_WRITE_WIDTH = -5,
    ERR_WRITE_HEIGHT = -6,
    ERR_READ_IS_TRUECOLOR = -7,
    ERR_WRITE_IS_TRUECOLOR = -8,
    ERR_READ_TRUECOLOR_TRANSPARENT = -9,
    ERR_WRITE_TRUECOLOR_TRANSPARENT = -10,
    ERR_READ_PALETTE_COUNT = -11,
    ERR_WRITE_PALETTE_COUNT = -12,
    ERR_READ_PALETTE_TRANSPARENT = -13,
    ERR_WRITE_PALETTE_TRANSPARENT = -14,
    ERR_READ_PALETTE_COLORS = -15,
    ERR_WRITE_PALETTE_COLORS = -16,
    ERR_READ_PIXELS = -17,
    ERR_WRITE_PIXELS = -18,
    ERR_INVALID_FILE_PTR = -19,
    ERR_INVALID_IMAGE_PTR = -20,
    ERR_UNKNOWN = 0x7FFFFFFF,
    
};
typedef enum kmz_gd_2x_image_file_status_e kmz_gd_2x_image_file_status;

// region Functions:
/**
 * Reads a GD file with a 2x header from the given file pointer.
 */
kmz_gd_2x_image_file_status kmz_read_gd_2x_image_file(FILE * f, KmzGd2xImageFile * o);

/**
 * Writes a GD file with a 2x header to the given file pointer.
 */
kmz_gd_2x_image_file_status kmz_write_gd_2x_image_file(FILE * f, KmzGd2xImageFile * i);

/**
 * Returns a plain-english message for the given file status.
 */
const char * kmz_status_msg(kmz_gd_2x_image_file_status status);

/**
 * Returns a plain-english message for the given file status with the given file error appended to it.
 */
const char * kmz_status_msg_with_err_code(kmz_gd_2x_image_file_status status, int error);
// endregion;

#endif /* kmz_gd_image_file_h */
