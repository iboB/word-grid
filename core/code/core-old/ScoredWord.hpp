// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"
#include "Word.hpp"
#include "GridPath.hpp"

namespace core
{
struct ScoredWord
{
    Word word;
    GridPath path;
    score_t score;
    bool special = 0; // word with a special bonus
};
}
