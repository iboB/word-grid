// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include <doctest/doctest.h>

#include "g-Grids.hpp"

#include <core/ScoringFlat.hpp>
#include <core/ScoringLength.hpp>
#include <core/ScoredWord.hpp>

using namespace core;
using namespace std;
using namespace itlib;

TEST_SUITE_BEGIN("Scoring");

TEST_CASE("Flat")
{
    ScoringFlat scoring(21);
    auto g = test::Grid_alphabetical(1, 1);
    CHECK(scoring.score({}, g) == 21);
}

TEST_CASE("Length")
{
    ScoringLength scoring(2.5f);

    auto grid = test::Grid_alphabetical(4, 4);

    ScoredWord w;
    w.word = Word::fromAscii("dgjnk");
    CHECK(scoring.score(w, grid) == 13);

    w.word = Word::fromAscii("begbzyjkend");
    CHECK(scoring.score(w, grid) == 28);
}

TEST_SUITE_END();
