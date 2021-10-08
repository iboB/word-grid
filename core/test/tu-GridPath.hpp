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

inline bool isValidGridPath(const core::GridPath& path, const core::Grid& g)
{
    return path.valid(g.dim());
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
