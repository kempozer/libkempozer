#include "kmz_color.h"

// region Helpers:
static const kmz_percent _KMZ_ONE_THIRD = (1. / 3.),
                         _KMZ_TWO_THIRDS = (2. / 3.);

kmz_percent _kmz_hue2rgb(kmz_percent part_1, kmz_percent part_2, kmz_percent hue) {
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

kmz_percent _kmz_rgb2delta(kmz_percent max, kmz_percent channel, kmz_percent max_delta, kmz_percent half_max_delta) {
    return ((((max - channel) / 6.) + half_max_delta) / max_delta);
}
// endregion;

// region Funcions:
KmzArgbColor KmzArgbColor__from_hex(const char * color) {
    return KmzArgbColor__from_color_32(kmz_color_32__from_hex(color));
}

KmzArgbColor KmzArgbColor__from_color_32(kmz_color_32 color) {
    const kmz_channel * c = (kmz_channel*)&color;
    
    return KmzArgbColor__from_channels(c[3], c[2], c[1], c[0]);
}

KmzArgbColor KmzArgbColor__from_channels(kmz_channel a, kmz_channel r, kmz_channel g, kmz_channel b) {
    const KmzArgbColor c = {.a=a, .r=r, .g=g, .b=b};
    
    return c;
}

KmzArgbColor KmzArgbColor__from_ahsl_color(KmzAhslColor color) {
    kmz_channel a = color.a, r, g, b;
    
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

KmzAhslColor KmzAhslColor__from_hex(const char * color) {
    return KmzAhslColor__from_argb_color(KmzArgbColor__from_hex(color));
}

KmzAhslColor KmzAhslColor__from_color_32(kmz_color_32 color) {
    return KmzAhslColor__from_argb_color(KmzArgbColor__from_color_32(color));
}

KmzAhslColor KmzAhslColor__from_channels(kmz_channel a, kmz_percent h, kmz_percent s, kmz_percent l) {
    const KmzAhslColor c = {.a=a, .h=h, .s=s, .l=l};
    
    return c;
}

KmzAhslColor KmzAhslColor__from_argb_color(KmzArgbColor color) {
    kmz_channel a = color.a;
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

kmz_color_32 kmz_color_32__from_argb_color(KmzArgbColor color) {
    return ((color.a << 24u) | (color.r << 16u) | (color.g << 8u) | color.b);
}

kmz_color_32 kmz_color_32__from_ahsl_color(KmzAhslColor color) {
    return kmz_color_32__from_argb_color(KmzArgbColor__from_ahsl_color(color));
}

kmz_color_32 kmz_color_32__from_hex(const char * color) {
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


// endregion;
