#ifndef kmz_color_h
#define kmz_color_h

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "kmz_geometry.h"
#include "kmz_numerics.h"

// region Types:
typedef uint32_t kmz_color_32;

struct kmz_argb_color_t {
    kmz_channel a : 7, r, g, b;
};
typedef struct kmz_argb_color_t KmzArgbColor;

struct kmz_ahsl_color_t {
    kmz_channel a : 7;
    kmz_percent h, s, l;
};
typedef struct kmz_ahsl_color_t KmzAhslColor;
// endregion;

// region Functions:
/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_color_32(kmz_color_32 color);

/**
 * Creates a new ARGB color from the provided values.
 */
KmzArgbColor KmzArgbColor__from_channels(kmz_channel a, kmz_channel r, kmz_channel g, kmz_channel b);

/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_ahsl_color(KmzAhslColor color);

/**
 * Creates a new ARGB color from the provided value.
 */
KmzArgbColor KmzArgbColor__from_hex(const char * color);

/**
 * Determines if the provided ARGB colors are equal.
 */
KmzBool KmzArgbColor__equal_to(KmzArgbColor me, KmzArgbColor other);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_color_32(kmz_color_32 color);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_channels(kmz_channel a, kmz_percent h, kmz_percent s, kmz_percent l);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_argb_color(KmzArgbColor color);

/**
 * Creates a new AHSL color from the provided value.
 */
KmzAhslColor KmzAhslColor__from_hex(const char * color);

/**
 * Determines if the provided AHSL colors are equal.
 */
KmzBool KmzAhslColor__equal_to(KmzAhslColor me, KmzAhslColor other);

/**
 * Creates a new color 32 color from the provided value.
 */
kmz_color_32 kmz_color_32__from_argb_color(KmzArgbColor color);

/**
 * Creates a new color 32 color from the provided value.
 */
kmz_color_32 kmz_color_32__from_ahsl_color(KmzAhslColor color);

/**
 * Creates a new color 32 color from the provided value.
 */
kmz_color_32 kmz_color_32__from_hex(const char * color);

/**
 * Determines if the provided color 32 colors are equal.
 */
KmzBool kmz_color_32__equal_to(kmz_color_32 me, kmz_color_32 other);
// endregion;

// region Constants:
static const KmzArgbColor KmzArgbColor__ALICE_BLUE = {.a=0, .r=0xF0, .g=0xF8, .b=0xFF},
KmzArgbColor__ANTIQUE_WHITE = {.a=0, .r=0xFA, .g=0xEB, .b=0xD7},
KmzArgbColor__AQUA = {.a=0, .r=0x00, .g=0xFF, .b=0xFF},
KmzArgbColor__AQUAMARINE = {.a=0, .r=0x7F, .g=0xFF, .b=0xD4},
KmzArgbColor__AZURE = {.a=0, .r=0xF0, .g=0xFF, .b=0xFF},
KmzArgbColor__BEIGE = {.a=0, .r=0xF5, .g=0xF5, .b=0xDC},
KmzArgbColor__BISQUE = {.a=0, .r=0xFF, .g=0xE4, .b=0xC4},
KmzArgbColor__BLACK = {.a=0, .r=0x00, .g=0x00, .b=0x00},
KmzArgbColor__BLANCHED_ALMOND = {.a=0, .r=0xFF, .g=0xEB, .b=0xCD},
KmzArgbColor__BLUE = {.a=0, .r=0x00, .g=0x00, .b=0xFF},
KmzArgbColor__BLUE_VIOLET = {.a=0, .r=0x8A, .g=0x2B, .b=0xE2},
KmzArgbColor__BROWN = {.a=0, .r=0xA5, .g=0x2A, .b=0x2A},
KmzArgbColor__BURLY_WOOD = {.a=0, .r=0xDE, .g=0xB8, .b=0x87},
KmzArgbColor__CADET_BLUE = {.a=0, .r=0x5F, .g=0x9E, .b=0xA0},
KmzArgbColor__CHARTREUSE = {.a=0, .r=0x7F, .g=0xFF, .b=0x00},
KmzArgbColor__CHOCOLATE = {.a=0, .r=0xD2, .g=0x69, .b=0x1E},
KmzArgbColor__CORAL = {.a=0, .r=0xFF, .g=0x7F, .b=0x50},
KmzArgbColor__CORNFLOWER_BLUE = {.a=0, .r=0x64, .g=0x95, .b=0xED},
KmzArgbColor__CORNSILK = {.a=0, .r=0xFF, .g=0xF8, .b=0xDC},
KmzArgbColor__CRIMSON = {.a=0, .r=0xDC, .g=0x14, .b=0x3C},
KmzArgbColor__CYAN = {.a=0, .r=0x00, .g=0xFF, .b=0xFF},
KmzArgbColor__DAR_KBLUE = {.a=0, .r=0x00, .g=0x00, .b=0x8B},
KmzArgbColor__DARK_CYAN = {.a=0, .r=0x00, .g=0x8B, .b=0x8B},
KmzArgbColor__DARK_GOLDENROD = {.a=0, .r=0xB8, .g=0x86, .b=0x0B},
KmzArgbColor__DARK_GRAY = {.a=0, .r=0xA9, .g=0xA9, .b=0xA9},
KmzArgbColor__DARK_GREEN = {.a=0, .r=0x00, .g=0x64, .b=0x00},
KmzArgbColor__DARK_KHAKI = {.a=0, .r=0xBD, .g=0xB7, .b=0x6B},
KmzArgbColor__DARK_MAGENTA = {.a=0, .r=0x8B, .g=0x00, .b=0x8B},
KmzArgbColor__DARK_OLIVE_GREEN = {.a=0, .r=0x55, .g=0x6B, .b=0x2F},
KmzArgbColor__DARK_ORANGE = {.a=0, .r=0xFF, .g=0x8C, .b=0x00},
KmzArgbColor__DARK_ORCHID = {.a=0, .r=0x99, .g=0x32, .b=0xCC},
KmzArgbColor__DARK_RED = {.a=0, .r=0x8B, .g=0x00, .b=0x00},
KmzArgbColor__DARK_SALMON = {.a=0, .r=0xE9, .g=0x96, .b=0x7A},
KmzArgbColor__DARK_SEA_GREEN = {.a=0, .r=0x8F, .g=0xBC, .b=0x8B},
KmzArgbColor__DARK_SLATE_BLUE = {.a=0, .r=0x48, .g=0x3D, .b=0x8B},
KmzArgbColor__DARK_SLATE_GRAY = {.a=0, .r=0x2F, .g=0x4F, .b=0x4F},
KmzArgbColor__DARK_TURQUOISE = {.a=0, .r=0x00, .g=0xCE, .b=0xD1},
KmzArgbColor__DARK_VIOLET = {.a=0, .r=0x94, .g=0x00, .b=0xD3},
KmzArgbColor__DEEP_PINK = {.a=0, .r=0xFF, .g=0x14, .b=0x93},
KmzArgbColor__DEEP_SKY_BLUE = {.a=0, .r=0x00, .g=0xBF, .b=0xFF},
KmzArgbColor__DIM_GRAY = {.a=0, .r=0x69, .g=0x69, .b=0x69},
KmzArgbColor__DODGER_BLUE = {.a=0, .r=0x1E, .g=0x90, .b=0xFF},
KmzArgbColor__FIREBRICK = {.a=0, .r=0xB2, .g=0x22, .b=0x22},
KmzArgbColor__FLORAL_WHITE = {.a=0, .r=0xFF, .g=0xFA, .b=0xF0},
KmzArgbColor__FOREST_GREEN = {.a=0, .r=0x22, .g=0x8B, .b=0x22},
KmzArgbColor__FUCHSIA = {.a=0, .r=0xFF, .g=0x00, .b=0xFF},
KmzArgbColor__GAINSBORO = {.a=0, .r=0xDC, .g=0xDC, .b=0xDC},
KmzArgbColor__GHOST_WHITE = {.a=0, .r=0xF8, .g=0xF8, .b=0xFF},
KmzArgbColor__GOLD = {.a=0, .r=0xFF, .g=0xD7, .b=0x00},
KmzArgbColor__GOLDENROD = {.a=0, .r=0xDA, .g=0xA5, .b=0x20},
KmzArgbColor__GRAY = {.a=0, .r=0x80, .g=0x80, .b=0x80},
KmzArgbColor__GREEN = {.a=0, .r=0x00, .g=0x80, .b=0x00},
KmzArgbColor__GREEN_YELLOW = {.a=0, .r=0xAD, .g=0xFF, .b=0x2F},
KmzArgbColor__HONEYDEW = {.a=0, .r=0xF0, .g=0xFF, .b=0xF0},
KmzArgbColor__HOT_PINK = {.a=0, .r=0xFF, .g=0x69, .b=0xB4},
KmzArgbColor__INDIAN_RED = {.a=0, .r=0xCD, .g=0x5C, .b=0x5C},
KmzArgbColor__INDIGO = {.a=0, .r=0x4B, .g=0x00, .b=0x82},
KmzArgbColor__IVORY = {.a=0, .r=0xFF, .g=0xFF, .b=0xF0},
KmzArgbColor__KHAKI = {.a=0, .r=0xF0, .g=0xE6, .b=0x8C},
KmzArgbColor__LAVENDER = {.a=0, .r=0xE6, .g=0xE6, .b=0xFA},
KmzArgbColor__LAVENDER_BLUSH = {.a=0, .r=0xFF, .g=0xF0, .b=0xF5},
KmzArgbColor__LAWN_GREEN = {.a=0, .r=0x7C, .g=0xFC, .b=0x00},
KmzArgbColor__LEMON_CHIFFON = {.a=0, .r=0xFF, .g=0xFA, .b=0xCD},
KmzArgbColor__LIGHT_BLUE = {.a=0, .r=0xAD, .g=0xD8, .b=0xE6},
KmzArgbColor__LIGHT_CORAL = {.a=0, .r=0xF0, .g=0x80, .b=0x80},
KmzArgbColor__LIGHT_CYAN = {.a=0, .r=0xE0, .g=0xFF, .b=0xFF},
KmzArgbColor__LIGHT_GOLDENROD_YELLOW = {.a=0, .r=0xFA, .g=0xFA, .b=0xD2},
KmzArgbColor__LIGHT_GRAY = {.a=0, .r=0xD3, .g=0xD3, .b=0xD3},
KmzArgbColor__LIGHT_GREEN = {.a=0, .r=0x90, .g=0xEE, .b=0x90},
KmzArgbColor__LIGHT_PINK = {.a=0, .r=0xFF, .g=0xB6, .b=0xC1},
KmzArgbColor__LIGHT_SALMON = {.a=0, .r=0xFF, .g=0xA0, .b=0x7A},
KmzArgbColor__LIGHT_SEA_GREEN = {.a=0, .r=0x20, .g=0xB2, .b=0xAA},
KmzArgbColor__LIGHT_SKY_BLUE = {.a=0, .r=0x87, .g=0xCE, .b=0xFA},
KmzArgbColor__LIGHT_SLATE_GRAY = {.a=0, .r=0x77, .g=0x88, .b=0x99},
KmzArgbColor__LIGHT_STEEL_BLUE = {.a=0, .r=0xB0, .g=0xC4, .b=0xDE},
KmzArgbColor__LIGHT_YELLOW = {.a=0, .r=0xFF, .g=0xFF, .b=0xE0},
KmzArgbColor__LIME = {.a=0, .r=0x00, .g=0xFF, .b=0x00},
KmzArgbColor__LIME_GREEN = {.a=0, .r=0x32, .g=0xCD, .b=0x32},
KmzArgbColor__LINEN = {.a=0, .r=0xFA, .g=0xF0, .b=0xE6},
KmzArgbColor__MAGENTA = {.a=0, .r=0xFF, .g=0x00, .b=0xFF},
KmzArgbColor__MAROON = {.a=0, .r=0x80, .g=0x00, .b=0x00},
KmzArgbColor__MEDIUM_AQUAMARINE = {.a=0, .r=0x66, .g=0xCD, .b=0xAA},
KmzArgbColor__MEDIUM_BLUE = {.a=0, .r=0x00, .g=0x00, .b=0xCD},
KmzArgbColor__MEDIUM_ORCHID = {.a=0, .r=0xBA, .g=0x55, .b=0xD3},
KmzArgbColor__MEDIUM_PURPLE = {.a=0, .r=0x93, .g=0x70, .b=0xDB},
KmzArgbColor__MEDIUM_SEA_GREEN = {.a=0, .r=0x3C, .g=0xB3, .b=0x71},
KmzArgbColor__MEDIUM_SLATE_BLUE = {.a=0, .r=0x7B, .g=0x68, .b=0xEE},
KmzArgbColor__MEDIUM_SPRING_GREEN = {.a=0, .r=0x00, .g=0xFA, .b=0x9A},
KmzArgbColor__MEDIUM_TURQUOISE = {.a=0, .r=0x48, .g=0xD1, .b=0xCC},
KmzArgbColor__MEDIUM_VIOLET_RED = {.a=0, .r=0xC7, .g=0x15, .b=0x85},
KmzArgbColor__MIDNIGHT_BLUE = {.a=0, .r=0x19, .g=0x19, .b=0x70},
KmzArgbColor__MINT_CREAM = {.a=0, .r=0xF5, .g=0xFF, .b=0xFA},
KmzArgbColor__MISTY_ROSE = {.a=0, .r=0xFF, .g=0xE4, .b=0xE1},
KmzArgbColor__MOCCASIN = {.a=0, .r=0xFF, .g=0xE4, .b=0xB5},
KmzArgbColor__NAVAJO_WHITE = {.a=0, .r=0xFF, .g=0xDE, .b=0xAD},
KmzArgbColor__NAVY = {.a=0, .r=0x00, .g=0x00, .b=0x80},
KmzArgbColor__OLD_LACE = {.a=0, .r=0xFD, .g=0xF5, .b=0xE6},
KmzArgbColor__OLIVE = {.a=0, .r=0x80, .g=0x80, .b=0x00},
KmzArgbColor__OLIVE_DRAB = {.a=0, .r=0x6B, .g=0x8E, .b=0x23},
KmzArgbColor__ORANGE = {.a=0, .r=0xFF, .g=0xA5, .b=0x00},
KmzArgbColor__ORANGE_RED = {.a=0, .r=0xFF, .g=0x45, .b=0x00},
KmzArgbColor__ORCHID = {.a=0, .r=0xDA, .g=0x70, .b=0xD6},
KmzArgbColor__PALE_GOLDENROD = {.a=0, .r=0xEE, .g=0xE8, .b=0xAA},
KmzArgbColor__PALE_GREEN = {.a=0, .r=0x98, .g=0xFB, .b=0x98},
KmzArgbColor__PALE_TURQUOISE = {.a=0, .r=0xAF, .g=0xEE, .b=0xEE},
KmzArgbColor__PALE_VIOLET_RED = {.a=0, .r=0xDB, .g=0x70, .b=0x93},
KmzArgbColor__PAPAYA_WHIP = {.a=0, .r=0xFF, .g=0xEF, .b=0xD5},
KmzArgbColor__PEACH_PUFF = {.a=0, .r=0xFF, .g=0xDA, .b=0xB9},
KmzArgbColor__PERU = {.a=0, .r=0xCD, .g=0x85, .b=0x3F},
KmzArgbColor__PINK = {.a=0, .r=0xFF, .g=0xC0, .b=0xCB},
KmzArgbColor__PLUM = {.a=0, .r=0xDD, .g=0xA0, .b=0xDD},
KmzArgbColor__POWDER_BLUE = {.a=0, .r=0xB0, .g=0xE0, .b=0xE6},
KmzArgbColor__PURPLE = {.a=0, .r=0x80, .g=0x00, .b=0x80},
KmzArgbColor__RED = {.a=0, .r=0xFF, .g=0x00, .b=0x00},
KmzArgbColor__ROSY_BROWN = {.a=0, .r=0xBC, .g=0x8F, .b=0x8F},
KmzArgbColor__ROYAL_BLUE = {.a=0, .r=0x41, .g=0x69, .b=0xE1},
KmzArgbColor__SADDLE_BROWN = {.a=0, .r=0x8B, .g=0x45, .b=0x13},
KmzArgbColor__SALMON = {.a=0, .r=0xFA, .g=0x80, .b=0x72},
KmzArgbColor__SANDY_BROWN = {.a=0, .r=0xF4, .g=0xA4, .b=0x60},
KmzArgbColor__SEA_GREEN = {.a=0, .r=0x2E, .g=0x8B, .b=0x57},
KmzArgbColor__SEA_SHELL = {.a=0, .r=0xFF, .g=0xF5, .b=0xEE},
KmzArgbColor__SIENNA = {.a=0, .r=0xA0, .g=0x52, .b=0x2D},
KmzArgbColor__SILVER = {.a=0, .r=0xC0, .g=0xC0, .b=0xC0},
KmzArgbColor__SKY_BLUE = {.a=0, .r=0x87, .g=0xCE, .b=0xEB},
KmzArgbColor__SLATE_BLUE = {.a=0, .r=0x6A, .g=0x5A, .b=0xCD},
KmzArgbColor__SLATE_GRAY = {.a=0, .r=0x70, .g=0x80, .b=0x90},
KmzArgbColor__SNOW = {.a=0, .r=0xFF, .g=0xFA, .b=0xFA},
KmzArgbColor__SPRING_GREEN = {.a=0, .r=0x00, .g=0xFF, .b=0x7F},
KmzArgbColor__STEEL_BLUE = {.a=0, .r=0x46, .g=0x82, .b=0xB4},
KmzArgbColor__TAN = {.a=0, .r=0xD2, .g=0xB4, .b=0x8C},
KmzArgbColor__TEAL = {.a=0, .r=0x00, .g=0x80, .b=0x80},
KmzArgbColor__THISTLE = {.a=0, .r=0xD8, .g=0xBF, .b=0xD8},
KmzArgbColor__TOMATO = {.a=0, .r=0xFF, .g=0x63, .b=0x47},
KmzArgbColor__TURQUOISE = {.a=0, .r=0x40, .g=0xE0, .b=0xD0},
KmzArgbColor__VIOLET = {.a=0, .r=0xEE, .g=0x82, .b=0xEE},
KmzArgbColor__WHEAT = {.a=0, .r=0xF5, .g=0xDE, .b=0xB3},
KmzArgbColor__WHITE = {.a=0, .r=0xFF, .g=0xFF, .b=0xFF},
KmzArgbColor__WHITE_SMOKE = {.a=0, .r=0xF5, .g=0xF5, .b=0xF5},
KmzArgbColor__YELLOW = {.a=0, .r=0xFF, .g=0xFF, .b=0x00},
KmzArgbColor__YELLOW_GREEN = {.a=0, .r=0x9A, .g=0xCD, .b=0x32};
// endregion;

#endif /* kmz_color_h */
