#ifndef kmz_color_h
#define kmz_color_h

#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include "kmz_geometry.h"

typedef float kmz_percent;
typedef uint8_t kmz_channel;
typedef uint16_t kmz_long_channel;
typedef uint32_t kmz_color_32;

struct kmz_argb_color_t {
    kmz_channel a : 7, r, g, b;
};
typedef struct kmz_argb_color_t KmzArgbColor;

// TODO: Implement more colors
static const KmzArgbColor KmzArgbColor__BLACK = {.a=0, .r=0, .g=0, .b=0},
                          KmzArgbColor__RED = {.a=0, .r=0xFF, .g=0, .b=0},
                          KmzArgbColor__BLUE = {.a=0, .r=0, .g=0, .b=0xFF},
                          KmzArgbColor__FUSCIA = {.a=0, .r=0xFF, .g=0, .b=0xFF},
                          KmzArgbColor__CYAN = {.a=0, .r=0, .g=0x8B, .b=0x8B},
                          KmzArgbColor__LIME = {.a=0, .r=0, .g=0xFF, .b=0},
                          KmzArgbColor__GREY = {.a=0, .r=0x40, .g=0x40, .b=0x40};

struct kmz_ahsl_color_t {
    kmz_channel a : 7;
    kmz_percent h, s, l;
};
typedef struct kmz_ahsl_color_t KmzAhslColor;

// region Functions:

KmzArgbColor KmzArgbColor__from_color_32(kmz_color_32 color);

KmzArgbColor KmzArgbColor__from_channels(kmz_channel a, kmz_channel r, kmz_channel g, kmz_channel b);

KmzArgbColor KmzArgbColor__from_ahsl_color(KmzAhslColor color);

KmzAhslColor KmzAhslColor__from_color_32(kmz_color_32 color);

KmzAhslColor KmzAhslColor__from_channels(kmz_channel a, kmz_percent h, kmz_percent s, kmz_percent l);

KmzAhslColor KmzAhslColor__from_argb_color(KmzArgbColor color);

kmz_color_32 kmz_color_32__from_argb_color(KmzArgbColor color);

kmz_color_32 kmz_color_32__from_ahsl_color(KmzAhslColor color);

// endregion;

#endif /* kmz_color_h */
