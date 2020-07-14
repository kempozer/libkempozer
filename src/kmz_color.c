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

// region Helpers:
static const kmz_percent _KMZ_ONE_THIRD = (1. / 3.),
                         _KMZ_TWO_THIRDS = (2. / 3.);

static inline const kmz_percent _kmz_hue2rgb(const kmz_percent part_1, const kmz_percent part_2, kmz_percent hue) {
    if (hue < 0.) {
        hue = (1. - fmodf(-hue, 1.));
    } else if (hue > 1.) {
        hue = fmodf(hue, 1.);
    }
    
    if (1. > (6. * hue)) {
        return (part_1 + (part_2 - part_1) * 6. * hue);
    } else if (1. > (2. * hue)) {
        return part_2;
    } else if (2. > (3. * hue)) {
        return (part_1 + (part_2 - part_1) * ((_KMZ_TWO_THIRDS - hue) * 6.));
    }
    
    return part_1;
}

static inline const kmz_percent _kmz_rgb2delta(const kmz_percent max, const kmz_percent channel, const kmz_percent max_delta,
                                               const kmz_percent half_max_delta) {
    return ((((max - channel) / 6.) + half_max_delta) / max_delta);
}
    
// endregion;

// region Funcions:
KmzArgbColor KmzArgbColor__from_hex(const char * color) {
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
        r = g = b = ((kmz_channel)round(color.l * 255.));
    } else {
        kmz_percent part_1, part_2;
        
        if (0.5 > color.l) {
            part_2 = (color.l * (1. + color.s));
        } else {
            part_2 = ((color.l + color.s) - (color.s * color.l));
        }
        
        part_1 = (2. * color.l - part_2);
        
        r = ((kmz_channel)round(255. * _kmz_hue2rgb(part_1, part_2, color.h + _KMZ_ONE_THIRD)));
        g = ((kmz_channel)round(255. * _kmz_hue2rgb(part_1, part_2, color.h)));
        b = ((kmz_channel)round(255. * _kmz_hue2rgb(part_1, part_2, color.h - _KMZ_ONE_THIRD)));
    }
    
    return KmzArgbColor__from_channels(a, r, g, b);
}

const KmzBool KmzArgbColor__equal_to(const KmzArgbColor me, const KmzArgbColor other) {
    return me.a == other.a && me.r == other.r && me.g == other.g && me.b == other.b;
}

KmzAhslColor KmzAhslColor__from_hex(const char * color) {
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
        l = ((((kmz_percent)(color.r + color.g + color.b)) / 3.) / 255.);
    } else {
        const kmz_percent red = ((kmz_percent)color.r / 255.),
                          green = ((kmz_percent)color.g / 255.),
                          blue = ((kmz_percent)color.b / 255.);
                          
        const kmz_percent min = fmin(fmin(red, green), blue),
                          max = fmax(fmax(red, green), blue);
                          
        const kmz_percent max_delta = (max - min),
                          min_max_sum = (min + max);
                          
        l = (min_max_sum / 2.);
                          
        if (0.5 > l) {
            s = (max_delta / min_max_sum);
        } else {
            s = (max_delta / (2. - max - min));
        }

        
        const kmz_percent half_max_delta = max_delta / 2.;
        
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
            h = 0.;
        }
                          
        if (h < 0.) {
            h = (1. - fmodf(-h, 1.));
        } else if (h > 1.) {
            h = fmodf(h, 1.);
        }
    }
    
    return KmzAhslColor__from_channels(a, h, s, l);
}

const KmzBool KmzAhslColor__equal_to(const KmzAhslColor me, const KmzAhslColor other) {
    return me.a == other.a && me.h == other.h && me.s == other.s && me.l == other.l;
}

const kmz_color_32 kmz_color_32__from_argb_color(const KmzArgbColor color) {
    return ((color.a << 24u) | (color.r << 16u) | (color.g << 8u) | color.b);
}

const kmz_color_32 kmz_color_32__from_ahsl_color(const KmzAhslColor color) {
    return kmz_color_32__from_argb_color(KmzArgbColor__from_ahsl_color(color));
}

const kmz_color_32 kmz_color_32__from_hex(const char * color) {
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
// endregion;
