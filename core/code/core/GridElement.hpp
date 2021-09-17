// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "GridElementTraits.hpp"
#include "LetterSequence.hpp"

#include <itlib/memory_view.hpp>

namespace core
{
// a grid element constists of one or more letters plus optional special characters
// elements with no special characters match themeselves
// "-xxx" - must end with "xxx"
// "xxx-" - must begin with "xxx"
// "a/b"  - is either 'a' or 'b'
class CORE_API GridElement : public LetterSequence<GridElementTraits::Max_Length>
{
public:
    // sign signifies a continuation
    // can be at the front or back
    static constexpr letter_t Cont_Sign = '-';

    // sign that separates element options
    static constexpr letter_t Delim_Sign = '/';

    // can only be at the front of a word
    bool frontOnly() const { return back() == Cont_Sign; }

    // can only be at the back of a word
    bool backOnly() const { return front() == Cont_Sign; }

    // options are the ways in which this element can be interpreted
    // in most cases there is only one option, but certain elements can be interpreted
    // in multiple ways (for example "a/b" can be a or b)
    struct OptionIterator
    {
        GridElement::const_iterator srcFrom; // begin of span
        GridElement::const_iterator srcTo; // end of span
        GridElement::const_iterator srcEnd; // end of source sequence

        // srcFrom can be beyond end since we skip the delimeter
        bool isEnd() const { return srcFrom >= srcEnd; }

        void goToNext();
        itlib::const_memory_view<letter_t> getMatchSequence() const;
    };

    OptionIterator firstOption() const;
};
} // namespace core
