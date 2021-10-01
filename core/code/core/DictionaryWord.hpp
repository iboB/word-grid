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

    // The utf8 display string for the word. It it not necessarily the same as the letters
    // It may have capitalization (which is ignored in letters)
    // It may contain characters which are not present in letters (dont = don't)
    // It may be subject to letter conversions
    // WARNING: this is a string view. It needs to have data a carrier somewhere
    // Languages have their own dictionary utf8 buffer
    // Boards may optionally cary one in case they are not in the same address space as the language
    // MIND THIS
    std::string_view displayString;

    // sort and compare by letters
    bool operator==(const DictionaryWord& other) const { return letters == other.letters; }
    bool operator<(const DictionaryWord& other) const { return letters < other.letters; }
};

} // namespace core
