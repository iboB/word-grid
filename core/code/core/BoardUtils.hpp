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
#include "GridPath.hpp"

#include <vector>

namespace core
{

class Grid;
class Word;
class Dictionary;
struct ScoredWord;

namespace impl
{

// tests a pattern (word)
// return coordinates of elements of first occurance found on the grid or empty path if not found
CORE_API GridPath testGridPattern(const Grid& grid, const Word& pattern);

// searches entire grid for words in dictionary and adds returns them along with paths
// WARNING: will return scored words with UNINITIALIZED score!
CORE_API std::vector<ScoredWord> findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary);

}
}
