// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Grid.hpp"
#include "GridElement.hpp"
#include "GridPath.hpp"

namespace core::impl
{

template <typename Visitor>
bool visitGridR(const Grid& g, Visitor& v, GridPath& path);

template <typename Visitor>
bool visitGridCoord(const Grid& g, const GridCoord& c, Visitor& v, GridPath& path)
{
    auto& gridElem = g[c];

    if (gridElem.frontOnly() && !path.empty()) return false;

    for (auto option = gridElem.firstOption(); !option.isEnd(); option.goToNext())
    {
        auto seq = option.getMatchSequence();

        if (!v.push(seq, c)) continue;
        path.push_back(c);
        if (v.done()) return true;

        if (!gridElem.backOnly())
        {
            // only recurse if this is not a back-only grid elem
            if (visitGridR(g, v, path)) return true;
        }

        v.pop(seq);
        path.pop_back();
    }

    return false;
}

template <typename Visitor>
bool visitGridR(const Grid& g, Visitor& v, GridPath& path)
{
    const auto& base = path.back();

    for (int y = -1; y <= 1; ++y)
    {
        GridCoord c;
        c.y = base.y + y;
        if (c.y >= g.dim().h) continue;
        for (int x = -1; x <= 1; ++x)
        {
            if (x == 0 && y == 0) continue;
            c.x = base.x + x;
            if (c.x >= g.dim().w) continue;

            if (path.contains(c)) continue;

            if (visitGridCoord(g, c, v, path)) return true;
        }
    }

    return false;
}

// visits grid while following legal paths
// uses a visitor which has the following methods
// * bool push(LetterSequenceView, const GridCoord&)
//        will receive an incarnated element (as match sequence) and position
//        return true to stop current path or false to continue deeper
// * bool done()
//        will be called after each push to check whether to stop traversal altogether
// * void pop(LetterSequenceView)
//        will be calleda fter a successful push (but not after false ones) with the same
//        match seuqence as push
template <typename Visitor>
GridPath visitGrid(const Grid& g, Visitor& v)
{
    GridPath path;
    GridCoord c;
    for (c.y = 0; c.y < g.dim().h; ++c.y)
    {
        for (c.x = 0; c.x < g.dim().w; ++c.x)
        {
            if (visitGridCoord(g, c, v, path)) return path;
        }
    }
    return path;
}

} // namespace core::impl
