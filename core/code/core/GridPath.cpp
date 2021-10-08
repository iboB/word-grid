// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "GridPath.hpp"

#include "GridDimensions.hpp"

namespace core
{

bool GridPath::valid(const GridDimensions& dim) const
{
    if (empty()) return true;

    for (auto& coord : *this)
    {
        // out of bounds
        if (coord.x >= dim.w || coord.y >= dim.h) return false;
    }

    for (size_t i = 0; i < size() - 1; ++i)
    {
        auto& prev = at(i);
        for (size_t j = i + 1; j < size(); ++j)
        {
            if (prev == at(j)) return false; // duplicate elements
        }

        auto& cur = at(i + 1);
        auto dx = std::abs(int(cur.x) - int(prev.x));
        auto dy = std::abs(int(cur.y) - int(prev.y));
        if (dx > 1 || dy > 1) return false; // element doesn't followe previous one
    }
    return true;
}

} // namespace core
