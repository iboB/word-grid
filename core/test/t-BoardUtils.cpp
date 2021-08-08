// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/BoardUtils.hpp>
#include <core/Grid.hpp>
#include <core/Word.hpp>
#include <core/Dictionary.hpp>

#include "g-Grids.hpp"

using namespace core;
using namespace core::impl;
using namespace std;
using namespace itlib;

TEST_SUITE_BEGIN("BoardUtils");

TEST_CASE("matching")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    auto path = testGridPattern(grid, Word::fromAscii("dgjnk"));
    CHECK(path.size() == 5);
    CHECK(path[0] == GridCoord{ 3, 0 });
    CHECK(path[1] == GridCoord{ 2, 1 });
    CHECK(path[2] == GridCoord{ 1, 2 });
    CHECK(path[3] == GridCoord{ 1, 3 });
    CHECK(path[4] == GridCoord{ 2, 2 });

    path = testGridPattern(grid, Word::fromAscii("dgjnka"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("zz"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("p"));
    CHECK(path.size() == 1);
    CHECK(path[0] == GridCoord{ 3, 3 });

    grid = test::Grid_fancy();

    path = testGridPattern(grid, Word::fromAscii("dgjnk"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("dbeg-"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("dbeg"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("begd"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, Word::fromAscii("beg"));
    CHECK(path.size() == 1);

    path = testGridPattern(grid, Word::fromAscii("begfzy"));
    CHECK(path.size() == 3);

    path = testGridPattern(grid, Word::fromAscii("endo"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("oend"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, Word::fromAscii("o-end"));
    CHECK(path.size() == 2);

    path = testGridPattern(grid, Word::fromAscii("end"));
    CHECK(path.size() == 1);

    path = testGridPattern(grid, Word::fromAscii("-end"));
    CHECK(path.size() == 0);

    path = testGridPattern(grid, Word::fromAscii("begbzyjkend"));
    CHECK(path.size() == 6);

    path = testGridPattern(grid, Word::fromAscii("begbzy-jkend"));
    CHECK(path.size() == 6);
}

TEST_CASE("find all")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    const uint8_t d1[] = R"d1c(
zog
afe
pokl
abop
jiebcd
klij
efkl
jkkl
iijk
)d1c";
    auto dic = Dictionary::fromUtf8Buffer(itlib::make_memory_view(d1));


}

TEST_SUITE_END();
