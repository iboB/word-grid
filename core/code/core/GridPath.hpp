// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "GridCoord.hpp"
#include "WordTraits.hpp"

#include <itlib/static_vector.hpp>

namespace core
{

struct GridDimensions;

using B_GridPath = itlib::static_vector<GridCoord, WordTraits::Max_Length>;
class CORE_API GridPath : public B_GridPath
{
public:
    using B_GridPath::static_vector;

    // returns whether this is a valid grid path for the given dims
    // check positions, checks if each element follows the previous one
    bool valid(const GridDimensions& dim) const;

    // check if path contains coord
    bool contains(GridCoord coord) const
    {
        for (auto& c : *this)
        {
            if (c == coord) return true;
        }
        return false;
    }
};

} // namespace core
