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
    const LetterSequence<GridElementTraits::Max_Length>& letterSequence() const { return *this; }

    score_t score() const { return m_score; }
    void setScore(score_t s) { m_score = s; }

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
    struct CORE_API OptionIterator
    {
        GridElement::const_iterator srcFrom; // begin of span
        GridElement::const_iterator srcTo; // end of span
        GridElement::const_iterator srcEnd; // end of source sequence

        // srcFrom can be beyond end since we skip the delimeter
        bool isEnd() const { return srcFrom >= srcEnd; }

        void goToNext();
        LetterSequenceView getMatchSequence() const;
    };

    OptionIterator firstOption() const;

    // return whether the word in question can possibly be constructed with this grid element
    bool matchesWord(LetterSequenceView word) const;

    // overload to extend the lifetime of a temporary
    template <size_t N>
    bool matchesWord(const LetterSequence<N>& seq) const
    {
        return matchesWord(seq.getView());
    }

    bool operator==(const GridElement& other) const
    {
        return letterSequence() == letterSequence() && m_score == other.m_score;
    }

    bool operator!=(const GridElement& other) const
    {
        return letterSequence() != letterSequence() || m_score != other.m_score;
    }

private:
    score_t m_score = 0;
};
} // namespace core
