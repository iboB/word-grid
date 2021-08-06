// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
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
using namespace itlib;

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

    auto wordData = Word::fromAscii("dgjnk");
    auto word = make_memory_view(wordData);
    auto path = grid.testPattern(word);

    CHECK(scoring.score(grid, path) == 12);

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
    path = grid.testPattern(word);
    CHECK(scoring.score(grid, path) == 27);

    elemWordData.clear();
    for (auto c : path)
    {
        elemWordData.push_back(grid.at(c));
    }
    elemWord = make_memory_view(elemWordData);
    CHECK(scoring.score(elemWord) == 27);
}

TEST_SUITE_END();