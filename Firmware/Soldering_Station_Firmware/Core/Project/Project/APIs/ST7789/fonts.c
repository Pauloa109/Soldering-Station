#include "fonts.h"

static FIL g_font_11x18_file;
static FIL g_font_16x26_file;

FontDef Font_11x18 =
{
    .width  = 11,
    .height = 18,
    .data   = 0,
    .path   = "Fonts/11x18.txt",
};

FontDef Font_16x26 =
{
    .width  = 16,
    .height = 26,
    .data   = 0,
    .path   = "Fonts/16x26.txt",
};
