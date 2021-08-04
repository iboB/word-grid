// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include <core/Grid.hpp>
#include <core/Word.hpp>

#include "g-Grids.hpp"

using namespace core;
using namespace std;
using namespace itlib;

TEST_SUITE_BEGIN("Grid");

TEST_CASE("matching")
{
    // abcd
    // efgh
    // ijkl
    // mnop
    auto grid = test::Grid_alphabetical();

    auto wordData = Word::fromAscii("dgjnk");
    auto word = make_memory_view(wordData);

    auto path = grid.testPattern(word);
    CHECK(path.size() == 5);
    CHECK(path[0] == GridCoord{ 3, 0 });
    CHECK(path[1] == GridCoord{ 2, 1 });
    CHECK(path[2] == GridCoord{ 1, 2 });
    CHECK(path[3] == GridCoord{ 1, 3 });
    CHECK(path[4] == GridCoord{ 2, 2 });

    wordData = Word::fromAscii("dgjnka");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("zz");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("p");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 1);
    CHECK(path[0] == GridCoord{ 3, 3 });

    grid = test::Grid_fancy();

    wordData = Word::fromAscii("dgjnk");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("dbeg-");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("dbeg");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("begd");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 2);

    wordData = Word::fromAscii("beg");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 1);

    wordData = Word::fromAscii("begfzy");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 3);

    wordData = Word::fromAscii("endo");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("oend");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 2);

    wordData = Word::fromAscii("o-end");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 2);

    wordData = Word::fromAscii("end");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 1);

    wordData = Word::fromAscii("-end");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 0);

    wordData = Word::fromAscii("begbzyjkend");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 6);

    wordData = Word::fromAscii("begbzy-jkend");
    word = make_memory_view(wordData);
    path = grid.testPattern(word);
    CHECK(path.size() == 6);
}

TEST_SUITE_END();
