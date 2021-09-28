// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "Dictionary.hpp"
#include "WordMatchSequence.hpp"

namespace core
{

class CORE_API DictionarySearch
{
public:
    DictionarySearch(const Dictionary& dictionary);

    const WordMatchSequence& curMatch() const { return m_matchWord.letters; }

    bool empty() const { return m_matchWord.letters.empty(); }

    enum class Result
    {
        None,
        Partial,
        Exact,
    };
    // push a letter into member match sequence and return a match within
    Result push(letter_t l);

    // pop the last item
    void pop();

private:
    const Dictionary& m_dictionary;

    // we don't really need a word here a WordMatchSequence would do
    // but it's much easier to use this for the binary searches inside
    // its previewString member is ignored throughout
    DictionaryWord m_matchWord;

    // range per each letter of the current match sequence
    struct Range
    {
        Dictionary::const_iterator begin;
        Dictionary::const_iterator end;
    };
    itlib::static_vector<Range, WordTraits::Max_Length> m_ranges;

    uint32_t m_overflow = 0; // pushes beyond Max_Length
};

} // namespace core
