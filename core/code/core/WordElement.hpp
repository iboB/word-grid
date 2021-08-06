// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "LetterSequence.hpp"
#include "WordElementTraits.hpp"

#include <itlib/memory_view.hpp>

namespace core
{
// a word element constists of one or more letters plus optional special characters
// letters with no special characters match themeselves
// "-xxx" - must end with "xxx"
// "xxx-" - must begin with "xxx"
class CORE_API WordElement : public LetterSequence<WordElementTraits::Max_Length, WordElement>
{
public:
    // checks whether the element matches the pattern
    // we have numPrevMatches as an argument to help check whether this is the beginning of the pattern
    // if it's 0, we assume a beginning
    bool matches(const itlib::const_memory_view<letter_t>& pattern) const;

    bool frontOnly() const { return back() == '-'; }
    bool backOnly() const { return front() == '-'; }

    // how many letters of the input does this sequence match
    size_t matchLength() const;

    // returns begin of relevant letters
    const_iterator lbegin() const;
};
}
