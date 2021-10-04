// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/BoardUtils.hpp>
#include <core/Dictionary.hpp>
#include <core/Grid.hpp>
#include <core/WordMatchSequence.hpp>

#include "g-Grids.hpp"

using namespace core;
using namespace core::impl;

TEST_SUITE_BEGIN("BoardUtils");

WordMatchSequence wms(std::string_view str)
{
    return LetterSequence_FromUtf8<WordMatchSequence>(str);
}

TEST_CASE("matching")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    auto path = testGridPattern(grid, wms("r"));
    CHECK(path.empty());

    path = testGridPattern(grid, wms("a"));
    REQUIRE(path.size() == 1);

    path = testGridPattern(grid, wms("dgjnk"));
    CHECK(path.size() == 5);
    CHECK(path[0] == GridCoord{3, 0});
    CHECK(path[1] == GridCoord{2, 1});
    CHECK(path[2] == GridCoord{1, 2});
    CHECK(path[3] == GridCoord{1, 3});
    CHECK(path[4] == GridCoord{2, 2});

    path = testGridPattern(grid, wms("dgjnka"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("aa"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("zz"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("p"));
    CHECK(path.size() == 1);
    CHECK(path[0] == GridCoord{3, 3});

    // a  b  c    d
    // zy b  beg- h
    // i  j  a/l  l
    // m  n  o    -end
    grid = test::Grid_fancy();

    path = testGridPattern(grid, wms("dgjnk"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("dbeg"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("beg-d"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("begd"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, wms("beg"));
    CHECK(path.size() == 1);

    path = testGridPattern(grid, wms("be"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("oen"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("begbb"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("begend"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("bbcc"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("bbc"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("endo"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("oend"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, wms("o-end"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("end"));
    CHECK(path.size() == 1);

    path = testGridPattern(grid, wms("-end"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, wms("beglend"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("begaend"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, wms("zyjllend"));
    CHECK(path.size() == 5);
}

