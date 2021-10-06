// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <cstdint>
#include <cstdlib>

namespace core
{

struct GridCoord
{
    uint8_t x;
    uint8_t y;

    static GridCoord fromIndex(uint32_t i, uint32_t width)
    {
        auto dm = std::div(int(i), int(width));
        return {uint8_t(dm.rem), uint8_t(dm.quot)};
    }

    uint32_t toIndex(uint32_t width) const
    {
        return width * y + x;
    }
};

inline bool operator==(const GridCoord& a, const GridCoord& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(const GridCoord& a, const GridCoord& b)
{
    return a.x != b.x || a.y != b.y;
}


} // namespace core
