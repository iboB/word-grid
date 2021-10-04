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

struct GridCoord
{
    uint8_t x;
    uint8_t y;
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
