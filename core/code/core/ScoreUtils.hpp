// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "Types.hpp"

#include <vector>

// these functions should be rearranged better

namespace core
{

struct ScoredWord;
class Grid;

namespace impl
{

// calculate a classic score for a word (based on grid elem scores and length bonus)
CORE_API score_t classicScore(const ScoredWord& word, const Grid& grid);

} // namespace impl
} // namespace core
