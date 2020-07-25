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

#include "kmz_color.h"

static const kmz_percent _KMZ_ONE_THIRD = (1.f / 3.f),
             _KMZ_TWO_THIRDS = (2.f / 3.f);

static inline const kmz_percent _kmz_hue2rgb(const kmz_percent part_1, const kmz_percent part_2, kmz_percent hue) {
    if (hue < 0.f) {
        hue = (1.f - fmodf(-hue, 1.f));
    } else if (hue > 1.f) {
        hue = fmodf(hue, 1.f);
    }

    if (1.f > (6.f * hue)) {
        return (part_1 + (part_2 - part_1) * 6.f * hue);
    } else if (1.f > (2.f * hue)) {
        return part_2;
    } else if (2.f > (3.f * hue)) {
        return (part_1 + (part_2 - part_1) * ((_KMZ_TWO_THIRDS - hue) * 6.f));
    }

    return part_1;
}

static inline const kmz_percent _kmz_rgb2delta(const kmz_percent max, const kmz_percent channel, const kmz_percent max_delta,
        const kmz_percent half_max_delta) {
    return ((((max - channel) / 6.f) + half_max_delta) / max_delta);
}

KmzArgbColor KmzArgbColor__from_hex(kmz_hex_string color) {
    return KmzArgbColor__from_color_32(kmz_color_32__from_hex(color));
}

KmzArgbColor KmzArgbColor__from_color_32(const kmz_color_32 color) {
    const kmz_channel * c = (kmz_channel*)&color;
    return KmzArgbColor__from_channels(c[3], c[2], c[1], c[0]);
}

KmzArgbColor KmzArgbColor__from_channels(const kmz_channel a, const kmz_channel r, const kmz_channel g, const kmz_channel b) {
    const KmzArgbColor c = {.a=a, .r=r, .g=g, .b=b};
    return c;
}

KmzArgbColor KmzArgbColor__from_ahsl_color(const KmzAhslColor color) {
    const kmz_channel a = color.a;
    kmz_channel r, g, b;

    if (0. == color.l) {
        r = g = b = 0;
    } else if (0. == color.s) {
        r = g = b = ((kmz_channel)round(color.l * 255.f));
    } else {
        kmz_percent part_1, part_2;

        if (0.5 > color.l) {
            part_2 = (color.l * (1.f + color.s));
        } else {
            part_2 = ((color.l + color.s) - (color.s * color.l));
        }

        part_1 = (2.f * color.l - part_2);

        r = ((kmz_channel)round(255.f * _kmz_hue2rgb(part_1, part_2, color.h + _KMZ_ONE_THIRD)));
        g = ((kmz_channel)round(255.f * _kmz_hue2rgb(part_1, part_2, color.h)));
        b = ((kmz_channel)round(255.f * _kmz_hue2rgb(part_1, part_2, color.h - _KMZ_ONE_THIRD)));
    }

    return KmzArgbColor__from_channels(a, r, g, b);
}

const KmzBool KmzArgbColor__equal_to(const KmzArgbColor me, const KmzArgbColor other) {
    return me.a == other.a && me.r == other.r && me.g == other.g && me.b == other.b;
}

KmzAhslColor KmzAhslColor__from_hex(kmz_hex_string color) {
    return KmzAhslColor__from_argb_color(KmzArgbColor__from_hex(color));
}

KmzAhslColor KmzAhslColor__from_color_32(const kmz_color_32 color) {
    return KmzAhslColor__from_argb_color(KmzArgbColor__from_color_32(color));
}

KmzAhslColor KmzAhslColor__from_channels(const kmz_channel a, const kmz_percent h, const kmz_percent s, const kmz_percent l) {
    const KmzAhslColor c = {.a=a, .h=h, .s=s, .l=l};
    return c;
}

KmzAhslColor KmzAhslColor__from_argb_color(KmzArgbColor color) {
    const kmz_channel a = color.a;
    kmz_percent h, s, l;

    if (0 == color.r && 0 == color.g && 0 == color.b) {
        h = s = l = 0.;
    } else if (color.r == color.g && color.g == color.b) {
        h = s = 0.;
        l = ((((kmz_percent)(color.r + color.g + color.b)) / 3.f) / 255.f);
    } else {
        const kmz_percent red = ((kmz_percent)color.r / 255.f),
              green = ((kmz_percent)color.g / 255.f),
              blue = ((kmz_percent)color.b / 255.f);

        const kmz_percent min = fminf(fminf(red, green), blue),
              max = fmaxf(fmaxf(red, green), blue);

        const kmz_percent max_delta = (max - min),
              min_max_sum = (min + max);

        l = (min_max_sum / 2.f);

        if (0.5f > l) {
            s = (max_delta / min_max_sum);
        } else {
            s = (max_delta / (2.f - max - min));
        }

        const kmz_percent half_max_delta = max_delta / 2.f;

        const kmz_percent red_delta = _kmz_rgb2delta(max, red, max_delta, half_max_delta),
              green_delta = _kmz_rgb2delta(max, green, max_delta, half_max_delta),
              blue_delta = _kmz_rgb2delta(max, blue, max_delta, half_max_delta);

        if (max == red) {
            h = (blue_delta - green_delta);
        } else if (max == green) {
            h = (_KMZ_ONE_THIRD + red_delta - blue_delta);
        } else if (max == blue) {
            h = (_KMZ_TWO_THIRDS + green_delta - red_delta);
        } else {
            h = 0.f;
        }

        if (h < 0.f) {
            h = (1.f - fmodf(-h, 1.f));
        } else if (h > 1.f) {
            h = fmodf(h, 1.f);
        }
    }

    return KmzAhslColor__from_channels(a, h, s, l);
}

const KmzBool KmzAhslColor__equal_to(const KmzAhslColor me, const KmzAhslColor other) {
    return me.a == other.a && me.h == other.h && me.s == other.s && me.l == other.l;
}

const kmz_color_32 kmz_color_32__from_argb_color(const KmzArgbColor color) {
    return (kmz_color_32)((color.a << 24u) | (color.r << 16u) | (color.g << 8u) | color.b);
}

const kmz_color_32 kmz_color_32__from_ahsl_color(const KmzAhslColor color) {
    return kmz_color_32__from_argb_color(KmzArgbColor__from_ahsl_color(color));
}

const kmz_color_32 kmz_color_32__from_hex(kmz_hex_string color) {
    switch (strlen(color)) {
        case 10:
        case 8:
            if ('0' == color[0] && ('x' == color[1] || 'X' == color[1])) {
                return (kmz_color_32)strtol(color, NULL, 0);
            }
            break;
        case 9:
        case 7:
            if ('#' == color[0]) {
                return (kmz_color_32)strtol(color + 1, NULL, 16);
            }
            break;
    }
    return 0;
}

const KmzBool kmz_color_32__equal_to(const kmz_color_32 me, const kmz_color_32 other) {
    return me == other;
}

const KmzArgbColor KmzArgbColor__ALICE_BLUE = {.a=0, .r=0xF0, .g=0xF8, .b=0xFF},
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
