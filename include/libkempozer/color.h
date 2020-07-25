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

#ifndef libkempozer_color_h
#define libkempozer_color_h

#include <stdlib.h>
#include <stdint.h>
#include <libkempozer.h>

/**
 * Defines a single channel of an AHSL color.
 */
typedef float kmz_percent;

/**
 * Defines a single channel of an abstract color.
 */
typedef uint8_t kmz_channel;

/**
 * Defines a 4 channel ARGB color stored in a single 32-bit integer.
 */
typedef uint32_t kmz_color_32;

/**
 * Defines a null terminated string that contains a hex color in the format of `0xXXXXXX`, `#XXXXXX`, `0xXXXXXXXX`, or `#XXXXXXXX`.
 */
typedef const char * const kmz_hex_string;

/**
 * Defines the structure of an ARGB color that is separated into its appropriate channels.
 */
struct kmz_argb_color_t {
    kmz_channel a;
    kmz_channel r;
    kmz_channel g;
    kmz_channel b;
};
typedef struct kmz_argb_color_t KmzArgbColor;

/**
 * Defines the structure of an AHSL color.
 */
struct kmz_ahsl_color_t {
    kmz_channel a;
    kmz_percent h;
    kmz_percent s;
    kmz_percent l;
};
typedef struct kmz_ahsl_color_t KmzAhslColor;


/**
 * Creates an ARGB structure from the provided, single value ARGB.
 *
 * @param color A color stored as 4 8-bit channels in the format of ARGB.
 * @return A {@link KmzArgbColor} structure that represents the provided ARGB value.
 */
KmzArgbColor KmzArgbColor__from_color_32(const kmz_color_32 color);

/**
 * Creates an ARGB structure from the provided ARGB channels.
 *
 * @param a The 8-bit alpha channel of the ARGB color where 0 is opaque and 127 is transparent.
 * @param r The 8-bit red channel of the ARGB color.
 * @param g The 8-bit green channel of the ARGB color.
 * @param b The 8-bit blue channel of the ARGB color.
 * @return A {@link KmzArgbColor} structure that represents the provided ARGB values.
 */
KmzArgbColor KmzArgbColor__from_channels(const kmz_channel a,
        const kmz_channel r,
        const kmz_channel g,
        const kmz_channel b);

/**
 * Creates an ARGB structure from the provided AHSL structure.
 *
 * @param color A color stored as an {@link KmzAhslColor} structure that represents an AHSL color.
 * @return A {@link KmzArgbColor} structure that represents the provided AHSL structure.
 */
KmzArgbColor KmzArgbColor__from_ahsl_color(const KmzAhslColor color);

/**
 * Creates an ARGB structure from the provided null terminated hex string.
 *
 * @param color A color stored as a null terminated string containing a hex color formatted as 0xXXXXXX, #XXXXXX, 0xXXXXXXXX, or #XXXXXXXX.
 * @return A {@link KmzArgbColor} structure that represents the provided {@link kmz_hex_string}.
 */
KmzArgbColor KmzArgbColor__from_hex(kmz_hex_string color);



/**
 * Creates an AHSL structure from the provided, single value ARGB.
 *
 * @param color A color stored as 4 8-bit channels in the format of ARGB.
 * @return A {@link KmzAhslColor} structure that represents the provided ARGB value.
 */
KmzAhslColor KmzAhslColor__from_color_32(const kmz_color_32 color);

/**
 * Creates an AHSL structure from the provided AHSL channels.
 *
 * @param a The 8-bit alpha channel of the AHSL color where 0 is opaque and 127 is transparent.
 * @param h The float hue channel of the AHSL color.
 * @param s The float saturation channel of the AHSL color.
 * @param l The float luminosity channel of the AHSL color.
 * @return A {@link KmzAhslColor} structure that represents the provided AHSL values.
 */
KmzAhslColor KmzAhslColor__from_channels(const kmz_channel a,
        const kmz_percent h,
        const kmz_percent s,
        const kmz_percent l);

/**
 * Creates an AHSL structure from the provided ARGB structure.
 *
 * @param color A color stored as an {@link KmzArgbColor} structure that represents an ARGB color.
 * @return A {@link KmzAhslColor} structure that represents the provided ARGB structure.
 */
KmzAhslColor KmzAhslColor__from_argb_color(const KmzArgbColor color);

/**
 * Creates an AHSL structure from the provided null terminated hex string.
 *
 * @param color A color stored as a null terminated string containing a hex color formatted as 0xXXXXXX, #XXXXXX, 0xXXXXXXXX, or #XXXXXXXX.
 * @return A {@link KmzAhslColor} structure that represents the provided {@link kmz_hex_string}.
 */
KmzAhslColor KmzAhslColor__from_hex(kmz_hex_string color);



/**
 * Creates a single ARGB value from the provided ARGB structure.
 *
 * @param color The {@link KmzArgbColor} structure to convert to a single {@link kmz_color_32} value.
 * @return A single {@link kmz_color_32} value that represents the provided {@link KmzArgbColor} structure.
 */
const kmz_color_32 kmz_color_32__from_argb_color(const KmzArgbColor color);

/**
 * Creates a single ARGB value from the provided AHSL structure.
 *
 * @param color The {@link KmzAhslColor} structure to convert to a single {@link kmz_color_32} value.
 * @return A single {@link kmz_color_32} value that represents the provided {@link KmzAhslColor} structure.
 */
const kmz_color_32 kmz_color_32__from_ahsl_color(const KmzAhslColor color);

/**
 * Creates a single ARGB value from the provided null terminated hex string.
 *
 * @param color A color stored as a null terminated string containing a hex color formatted as 0xXXXXXX, #XXXXXX, 0xXXXXXXXX, or #XXXXXXXX.
 * @return A single {@link kmz_color_32} value that represents the provided {@link kmz_hex_string}.
 */
const kmz_color_32 kmz_color_32__from_hex(kmz_hex_string color);

#endif /* libkempozer_color_h */
