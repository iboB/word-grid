// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

// this functions should be rearranged better

#include "DictionaryWord.hpp"
#include "GridPath.hpp"
#include "Types.hpp"
#include "WordMatchSequence.hpp"

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
CORE_API GridPath testGridPattern(const Grid& grid, const WordMatchSequence& pattern);

// searches entire grid for words in dictionary and adds returns them along with paths
struct FindAllWord
{
    const DictionaryWord& word;
    GridPath path;
};
CORE_API std::vector<FindAllWord> findAllWordsInGrid(const Grid& grid, const Dictionary& dictionary);

} // namespace impl
} // namespace core
