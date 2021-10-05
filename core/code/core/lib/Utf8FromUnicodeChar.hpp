// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <cstdint>

namespace core
{

int Utf8LengthOfUnicodeChar(uint32_t cp)
{
    if (cp <= 0x7f) return 1;
    if (cp <= 0x7ff) return 2;
    if (cp <= 0xffff) return 3;

    return 4;
}

// assumes there is enough room for the conversion
// returns number of bytes writte to out_utf8
int Utf8FromUnicodeChar(char* out_utf8, uint32_t cp)
{
    if (cp <= 0x7f)
    {
        *out_utf8 = char(cp);
        return 1;
    }
    if (cp <= 0x7ff)
    {
        *out_utf8++ = 0xc0 | (cp >> 6);
        *out_utf8++ = 0x80 | (cp & 0x3f);
        return 2;
    }
    if (cp <= 0xffff)
    {
        *out_utf8++ = 0xe0 | (cp >> 12);
        *out_utf8++ = 0x80 | ((cp >> 6) & 0x3f);
        *out_utf8++ = 0x80 | (cp & 0x3f);
        return 3;
    }
    else
    {
        *out_utf8++ = 0xf0 | (cp >> 18);
        *out_utf8++ = 0x80 | ((cp >> 12) & 0x3f);
        *out_utf8++ = 0x80 | ((cp >> 6) & 0x3f);
        *out_utf8++ = 0x80 | (cp & 0x3f);
        return 4;
    }
}

} // namespace core
