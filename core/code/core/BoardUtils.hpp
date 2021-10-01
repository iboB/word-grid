// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "GridPath.hpp"
#include "LetterSequence.hpp"
#include "Types.hpp"

#include <vector>

namespace core
{

class Grid;
class Dictionary;
struct ScoredWord;

namespace impl
{

// tests a pattern (word)
// return coordinates of elements of first occurance found on the grid or empty path if not found
CORE_API GridPath testGridPattern(const Grid& grid, LetterSequenceView pattern);

// searches entire grid for words in dictionary and adds returns them along with paths
// WARNING: will return a vector of incomplete ScoredWord-s
// score-related stuff won't be touched
CORE_API std::vector<ScoredWord> findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary);

} // namespace impl
} // namespace core
