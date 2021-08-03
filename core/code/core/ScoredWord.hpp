// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"
#include "Word.hpp"
#include "GridCoord.hpp"

namespace core
{
struct ScoredWord
{
    Word word;
    itlib::static_vector<GridCoord, WordTraits::Max_Length> coords;
    score_t score;
};
}