// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <core/Grid.hpp>
#include <core/GridPath.hpp>

namespace test
{

inline bool isValidGridPath(const core::GridPath& path, const core::GridDimensions& dim)
{
    if (path.empty()) return true;

    for (auto& coord : path)
    {
        // out of bounds
        if (coord.x >= dim.w || coord.y >= dim.h) return false;
    }

    for (size_t i = 0; i < path.size() - 1; ++i)
    {
        auto& coord = path[i];
        for (size_t j = i + 1; j < path.size(); ++j)
        {
            // duplicate elements
            if (coord == path[j]) return false;
        }
    }

    return true;
}

inline bool isValidGridPath(const core::GridPath& path, const core::Grid& g)
{
    return isValidGridPath(path, g.dim());
}

inline bool isEmptyGridPath(const core::GridPath& path, const core::Grid& g)
{
    if (!isValidGridPath(path, g)) return false;

    for (auto& c : path)
    {
        if (!g[c].empty()) return false;
    }

    return true;
}

} // namespace test
