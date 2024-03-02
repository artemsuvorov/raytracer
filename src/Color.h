#pragma once

#include "Precompiled.h"

namespace Core {

#define ToRgb(hex)                  \
    (((hex) & 0xFF000000u) >> 24u), \
    (((hex) & 0x00FF0000u) >> 16u), \
    (((hex) & 0x0000FF00u) >>  8u)  \

#define ToRgba(hex)                 \
    (((hex) & 0xFF000000u) >> 24u), \
    (((hex) & 0x00FF0000u) >> 16u), \
    (((hex) & 0x0000FF00u) >>  8u), \
    (((hex) & 0x000000FFu) >>  0u)  \

#define ToRgbNorm(hex)                       \
    (((hex) & 0xFF000000u) >> 24u) / 255.0f, \
    (((hex) & 0x00FF0000u) >> 16u) / 255.0f, \
    (((hex) & 0x0000FF00u) >>  8u) / 255.0f  \

#define ToRgbaNorm(hex)                      \
    (((hex) & 0xFF000000u) >> 24u) / 255.0f, \
    (((hex) & 0x00FF0000u) >> 16u) / 255.0f, \
    (((hex) & 0x0000FF00u) >>  8u) / 255.0f, \
    (((hex) & 0x000000FFu) >>  0u) / 255.0f  \

// 4-channel color in hex notation 0xRRGGBBAA.
union Color final
{
    // Helper.
    #define ToHex(r, g, b) (((r) & 0xFFu) << 16u) + (((g) & 0xFFu) << 8u) + ((b) & 0xFFu)

    enum PredefinedColors : uint32_t
    {
        Black = 0x000000FFu,
        White = 0xFFFFFFFFu,
        Red   = 0xFF0000FFu,
        Green = 0x00FF00FFu,
        Blue  = 0x0000FFFFu,
    };

    Color(uint32_t hex) : hex(hex) {}
    Color(uint32_t r, uint32_t g, uint32_t b) : hex(ToHex(r, g, b)) {}
    Color() : Color(Black) {}

    const uint32_t hex;

#if IS_BIG_ENDIAN
    struct { const uint8_t r, g, b, a; };
#else
    struct { const uint8_t a, b, g, r; };
#endif
};

}