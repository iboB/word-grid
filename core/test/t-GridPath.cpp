// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/GridDimensions.hpp>
#include <core/GridPath.hpp>

using namespace core;

TEST_SUITE_BEGIN("GridPath");

using core::GridPath;

TEST_CASE("Basic")
{
    GridPath e;
    CHECK(e.empty());
    CHECK(e.valid({1, 1}));

    GridPath a = {{1, 2}, {1, 3}, {2, 3}};
    CHECK(a.valid({4, 4}));
    CHECK(!a.valid({3, 3}));

    CHECK(a.contains({1, 2}));
    CHECK(a.contains({1, 3}));
    CHECK(a.contains({2, 3}));

    CHECK(!a.contains({1, 1}));
    CHECK(!a.contains({3, 3}));
}

TEST_CASE("Invalid")
{
    core::GridDimensions d = {100, 100};
    CHECK_FALSE(GridPath{{100, 100}}.valid(d)); // out of range
    CHECK_FALSE(GridPath{{1, 2}, {1, 3}, {3, 3}}.valid(d)); // disjoint
    CHECK_FALSE(GridPath{{1, 2}, {1, 3}, {1, 3}}.valid(d)); // dupes
}