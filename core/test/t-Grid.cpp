// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/Grid.hpp>

#include "g-Grids.hpp"

using namespace core;

TEST_SUITE_BEGIN("Grid");

template <typename G>
void check_7x12()
{
    G g(7, 12);
    CHECK(g.w() == 7);
    CHECK(g.h() == 12);
    CHECK(g.elements().size() == 84);
    CHECK(g.coordOf(1) == GridCoord{1, 0});
    CHECK(g.indexOf(GridCoord{1, 0}) == 1);
    CHECK(g.indexOf(GridCoord{0, 1}) == 7);
    CHECK(g.coordOf(18) == GridCoord{4, 2});
    CHECK(g.indexOf(GridCoord{4, 2}) == 18);
    CHECK(g.row(0).size() == 7);
    CHECK(&g.row(0)[0] == g.elements().data());
    CHECK(&g.row(0)[1] == &g[GridCoord{1, 0}]);
    CHECK(&g.row(11)[5] == &g[82]);
}

TEST_CASE("Basic")
{
    check_7x12<Grid>();
    check_7x12<const Grid>();
}

TEST_CASE("alphabetical")
{
    const auto g = test::Grid_alphabetical();
    CHECK(g.w() == 4);
    CHECK(g.h() == 4);
    core::letter_t l = 'a';
    for (auto& e : g.elements())
    {
        CHECK(e.size() == 1);
        CHECK(e[0] == l++);
    }
    CHECK(g.at({1, 2})[0] == 'j');
    CHECK(g.coordOf(11) == GridCoord{3, 2});
}

TEST_CASE("fancy")
{
    auto g = test::Grid_fancy();
    auto ms = g[GridCoord{0, 1}].firstOption().getMatchSequence();
    CHECK(ms.size() == 2);
}
