// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include "g-Grids.hpp"

#include <core/Scoring.hpp>

using namespace core;
using namespace std;
using namespace chobo;

TEST_SUITE_BEGIN("Scoring");

TEST_CASE("Flat")
{
    auto scoring = Scoring::flat(21);

    auto g = test::Grid_alphabetical(1, 1);
    CHECK(scoring.score({}) == 21);
    CHECK(scoring.score(g, {}) == 21);
}

TEST_CASE("Length")
{
    auto scoring = Scoring::length(2.5f);

    auto grid = test::Grid_alphabetical(4, 4);

    vector<GridCoord> coordsData(50);
    auto coords = make_memory_view(coordsData);
    auto wordData = Word::fromAscii("dgjnk");
    auto word = make_memory_view(wordData);
    auto len = grid.testPattern(word, coords);

    auto wcoords = make_memory_view(coords.data(), len);
    CHECK(scoring.score(grid, wcoords) == 12);

    vector<WordElement> elemWordData = {
        WordElement::fromAscii("d"),
        WordElement::fromAscii("g"),
        WordElement::fromAscii("j"),
        WordElement::fromAscii("n"),
        WordElement::fromAscii("k"),
    };
    auto elemWord = make_memory_view(elemWordData);
    CHECK(scoring.score(elemWord) == 12);

    grid = test::Grid_fancy();

    wordData = Word::fromAscii("begbzyjkend");
    word = make_memory_view(wordData);
    len = grid.testPattern(word, coords);
    wcoords = make_memory_view(coords.data(), len);
    CHECK(scoring.score(grid, wcoords) == 27);

    elemWordData.clear();
    for (size_t i = 0; i < len; ++i)
    {
        elemWordData.push_back(grid.at(coordsData[i]));
    }
    elemWord = make_memory_view(elemWordData);
    CHECK(scoring.score(elemWord) == 27);
}

TEST_SUITE_END();