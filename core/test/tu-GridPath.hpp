// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <core/GridPath.hpp>
#include <core/Grid.hpp>

namespace test
{

inline bool isValidGridPath(const core::GridPath& path, size_t width, size_t height)
{
    if (path.empty()) return true;

    for (auto& coord : path)
    {
        // out of bounds
        if (coord.x >= width || coord.y >= height) return false;
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
    return isValidGridPath(path, g.w(), g.h());
}

} // namespace test
