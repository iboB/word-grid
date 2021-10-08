// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "DictionaryWord.hpp"

#include <itlib/flat_set.hpp>

namespace core
{
class Dictionary : public itlib::flat_set<DictionaryWord>
// this could've been a map<MatchSequence, string_view>, but instead of using first/second everywhere
// it's much more readable to use letters/displayString

// perhaps this could be made into a trie in the future for even faster searches
// no apparent need for now besides the coolness factor :)
{
public:
    using itlib::flat_set<DictionaryWord>::flat_set;
};
} // namespace core
