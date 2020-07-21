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

#ifndef colors_h
#define colors_h

#include <libkempozer.h>
#include <libkempozer/color.h>

// TODO: Document color values

extern const KmzArgbColor
KmzArgbColor__ALICE_BLUE,
KmzArgbColor__ANTIQUE_WHITE,
KmzArgbColor__AQUA,
KmzArgbColor__AQUAMARINE,
KmzArgbColor__AZURE,
KmzArgbColor__BEIGE,
KmzArgbColor__BISQUE,
KmzArgbColor__BLACK,
KmzArgbColor__BLANCHED_ALMOND,
KmzArgbColor__BLUE,
KmzArgbColor__BLUE_VIOLET,
KmzArgbColor__BROWN,
KmzArgbColor__BURLY_WOOD,
KmzArgbColor__CADET_BLUE,
KmzArgbColor__CHARTREUSE,
KmzArgbColor__CHOCOLATE,
KmzArgbColor__CORAL,
KmzArgbColor__CORNFLOWER_BLUE,
KmzArgbColor__CORNSILK,
KmzArgbColor__CRIMSON,
KmzArgbColor__CYAN,
KmzArgbColor__DAR_KBLUE,
KmzArgbColor__DARK_CYAN,
KmzArgbColor__DARK_GOLDENROD,
KmzArgbColor__DARK_GRAY,
KmzArgbColor__DARK_GREEN,
KmzArgbColor__DARK_KHAKI,
KmzArgbColor__DARK_MAGENTA,
KmzArgbColor__DARK_OLIVE_GREEN,
KmzArgbColor__DARK_ORANGE,
KmzArgbColor__DARK_ORCHID,
KmzArgbColor__DARK_RED,
KmzArgbColor__DARK_SALMON,
KmzArgbColor__DARK_SEA_GREEN,
KmzArgbColor__DARK_SLATE_BLUE,
KmzArgbColor__DARK_SLATE_GRAY,
KmzArgbColor__DARK_TURQUOISE,
KmzArgbColor__DARK_VIOLET,
KmzArgbColor__DEEP_PINK,
KmzArgbColor__DEEP_SKY_BLUE,
KmzArgbColor__DIM_GRAY,
KmzArgbColor__DODGER_BLUE,
KmzArgbColor__FIREBRICK,
KmzArgbColor__FLORAL_WHITE,
KmzArgbColor__FOREST_GREEN,
KmzArgbColor__FUCHSIA,
KmzArgbColor__GAINSBORO,
KmzArgbColor__GHOST_WHITE,
KmzArgbColor__GOLD,
KmzArgbColor__GOLDENROD,
KmzArgbColor__GRAY,
KmzArgbColor__GREEN,
KmzArgbColor__GREEN_YELLOW,
KmzArgbColor__HONEYDEW,
KmzArgbColor__HOT_PINK,
KmzArgbColor__INDIAN_RED,
KmzArgbColor__INDIGO,
KmzArgbColor__IVORY,
KmzArgbColor__KHAKI,
KmzArgbColor__LAVENDER,
KmzArgbColor__LAVENDER_BLUSH,
KmzArgbColor__LAWN_GREEN,
KmzArgbColor__LEMON_CHIFFON,
KmzArgbColor__LIGHT_BLUE,
KmzArgbColor__LIGHT_CORAL,
KmzArgbColor__LIGHT_CYAN,
KmzArgbColor__LIGHT_GOLDENROD_YELLOW,
KmzArgbColor__LIGHT_GRAY,
KmzArgbColor__LIGHT_GREEN,
KmzArgbColor__LIGHT_PINK,
KmzArgbColor__LIGHT_SALMON,
KmzArgbColor__LIGHT_SEA_GREEN,
KmzArgbColor__LIGHT_SKY_BLUE,
KmzArgbColor__LIGHT_SLATE_GRAY,
KmzArgbColor__LIGHT_STEEL_BLUE,
KmzArgbColor__LIGHT_YELLOW,
KmzArgbColor__LIME,
KmzArgbColor__LIME_GREEN,
KmzArgbColor__LINEN,
KmzArgbColor__MAGENTA,
KmzArgbColor__MAROON,
KmzArgbColor__MEDIUM_AQUAMARINE,
KmzArgbColor__MEDIUM_BLUE,
KmzArgbColor__MEDIUM_ORCHID,
KmzArgbColor__MEDIUM_PURPLE,
KmzArgbColor__MEDIUM_SEA_GREEN,
KmzArgbColor__MEDIUM_SLATE_BLUE,
KmzArgbColor__MEDIUM_SPRING_GREEN,
KmzArgbColor__MEDIUM_TURQUOISE,
KmzArgbColor__MEDIUM_VIOLET_RED,
KmzArgbColor__MIDNIGHT_BLUE,
KmzArgbColor__MINT_CREAM,
KmzArgbColor__MISTY_ROSE,
KmzArgbColor__MOCCASIN,
KmzArgbColor__NAVAJO_WHITE,
KmzArgbColor__NAVY,
KmzArgbColor__OLD_LACE,
KmzArgbColor__OLIVE,
KmzArgbColor__OLIVE_DRAB,
KmzArgbColor__ORANGE,
KmzArgbColor__ORANGE_RED,
KmzArgbColor__ORCHID,
KmzArgbColor__PALE_GOLDENROD,
KmzArgbColor__PALE_GREEN,
KmzArgbColor__PALE_TURQUOISE,
KmzArgbColor__PALE_VIOLET_RED,
KmzArgbColor__PAPAYA_WHIP,
KmzArgbColor__PEACH_PUFF,
KmzArgbColor__PERU,
KmzArgbColor__PINK,
KmzArgbColor__PLUM,
KmzArgbColor__POWDER_BLUE,
KmzArgbColor__PURPLE,
KmzArgbColor__RED,
KmzArgbColor__ROSY_BROWN,
KmzArgbColor__ROYAL_BLUE,
KmzArgbColor__SADDLE_BROWN,
KmzArgbColor__SALMON,
KmzArgbColor__SANDY_BROWN,
KmzArgbColor__SEA_GREEN,
KmzArgbColor__SEA_SHELL,
KmzArgbColor__SIENNA,
KmzArgbColor__SILVER,
KmzArgbColor__SKY_BLUE,
KmzArgbColor__SLATE_BLUE,
KmzArgbColor__SLATE_GRAY,
KmzArgbColor__SNOW,
KmzArgbColor__SPRING_GREEN,
KmzArgbColor__STEEL_BLUE,
KmzArgbColor__TAN,
KmzArgbColor__TEAL,
KmzArgbColor__THISTLE,
KmzArgbColor__TOMATO,
KmzArgbColor__TURQUOISE,
KmzArgbColor__VIOLET,
KmzArgbColor__WHEAT,
KmzArgbColor__WHITE,
KmzArgbColor__WHITE_SMOKE,
KmzArgbColor__YELLOW,
KmzArgbColor__YELLOW_GREEN;

#endif /* colors_h */
