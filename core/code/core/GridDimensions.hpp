// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "GridCoord.hpp"

#include <cstdint>

namespace core
{

struct GridDimensions
{
    uint32_t w;
    uint32_t h;

    uint32_t area() const
    {
        return w * h;
    }

    GridCoord coordOf(uint32_t i) const
    {
        auto dm = std::div(int(i), int(w));
        return {uint8_t(dm.rem), uint8_t(dm.quot)};
    }

    uint32_t indexOf(GridCoord gc) const
    {
        return w * gc.y + gc.x;
    }
};

}
