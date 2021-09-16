// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "WordMatchSequence.hpp"

#include <string_view>

namespace core
{

struct DictionaryWord
{
    WordMatchSequence letters;
    std::string_view displayString;

    // sort and compare by letters
    bool operator==(const DictionaryWord& other) const { return letters == other.letters; }
    bool operator<(const DictionaryWord& other) const { return letters < other.letters; }
};

} // namespace core
