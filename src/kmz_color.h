#ifndef kmz_color_h
#define kmz_color_h

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "kmz_geometry.h"

typedef float kmz_percent;
typedef uint8_t kmz_channel;
typedef uint16_t kmz_double_channel;
typedef uint32_t kmz_color_32;

struct kmz_argb_color_t {
    kmz_channel a : 7, r, g, b;
};
typedef struct kmz_argb_color_t kmz_argb_color;

// TODO: Implement more colors
static const kmz_argb_color kmz_argb_color__BLACK = {.a=0, .r=0, .g=0, .b=0},
                            kmz_argb_color__RED = {.a=0, .r=0xFF, .g=0, .b=0},
                            kmz_argb_color__GREEN = {.a=0, .r=0, .g=0xFF, .b=0},
                            kmz_argb_color__BLUE = {.a=0, .r=0, .g=0, .b=0xFF},
                            kmz_argb_color__FUSCIA = {.a=0, .r=0xFF, .g=0, .b=0xFF},
                            kmz_argb_color__CYAN = {.a=0, .r=0, .g=0x8B, .b=0x8B},
                            kmz_argb_color__LIME = {.a=0, .r=0, .g=0xFF, .b=0},
                            kmz_argb_color__GREY = {.a=0, .r=0x40, .g=0x40, .b=0x40};

struct kmz_ahsl_color_t {
    kmz_channel a : 7;
    kmz_percent h, s, l;
};
typedef struct kmz_ahsl_color_t kmz_ahsl_color;

// TODO: Implement more colors
static const kmz_ahsl_color kmz_ahsl_color__BLACK = {.a=0, .h=0., .s=0., .l=0.},
                            kmz_ahsl_color__RED = {.a=0, .h=0., .s=1., .l=0.5},
                            kmz_ahsl_color__GREEN = {.a=0, .h=0.333333333333333, .s=1., .l=0.5},
                            kmz_ahsl_color__BLUE = {.a=0, .h=0.666666666666667, .s=1., .l=0.5};


// region Functions:

kmz_argb_color kmz_argb_color_from_color_32(kmz_color_32 color);

kmz_argb_color kmz_argb_color_from_channels(kmz_channel a, kmz_channel r, kmz_channel g, kmz_channel b);

kmz_argb_color kmz_argb_color_from_ahsl_color(kmz_ahsl_color color);

kmz_ahsl_color kmz_ahsl_color_from_color_32(kmz_color_32 color);

kmz_ahsl_color kmz_ahsl_color_from_channels(kmz_channel a, kmz_percent h, kmz_percent s, kmz_percent l);

kmz_ahsl_color kmz_ahsl_color_from_argb_color(kmz_argb_color color);

kmz_color_32 kmz_color_32_from_argb_color(kmz_argb_color color);

kmz_color_32 kmz_color_32_from_ahsl_color(kmz_ahsl_color color);

// endregion;

#endif /* kmz_color_h */
