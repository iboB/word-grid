// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "BasicLanguage.hpp"
#include "Dictionary.hpp"
#include "LanguageTypes.hpp"

#include <limits>

namespace core
{

class CORE_API Language : public BasicLanguage
{
public:
    Language();
    ~Language();

    Language(const Language&) = delete;
    Language& operator=(const Language&) = delete;

    Language(Language&&) noexcept;
    Language& operator=(Language&&) noexcept;

    const Alphabet& alphabet() const { return m_alphabet; }

    // an array with repeated values per letter, such that taking a random element from it
    // will produce an alphabet item with probablity inverse to the score
    // if the score of an item is non-positive the probability is equal calculated as if the item's score is
    // equal to the item with the highest positive score positive score + the provided score
    using AlphabetFrequencyTable = std::vector<std::reference_wrapper<const GridElement>>;
    const AlphabetFrequencyTable& alphabetFrequencyTable() const { return m_alphabetFrequencyTable; }

    const Dictionary& dictionary() const { return m_dictionary; }

    using HelperList = std::vector<std::reference_wrapper<const DictionaryWord>>;
    const HelperList& commonWordsByLength() const { return m_commonWordsByLength; }

    // limits for score
    // a produced board is not considered playable if its total score is below minScore or above maxScore
    // this allows us to have a somewhat uniform ranking of players across boards in the same language
    score_t minScore() const { return m_minScore; }
    score_t maxScore() const { return m_maxScore; }

private:
    friend class LanguageBuilder;

    Alphabet m_alphabet;
    AlphabetFrequencyTable m_alphabetFrequencyTable;

    Specials m_specials;

    Dictionary m_dictionary;
    std::vector<char> m_dictionaryUtf8Buffer;

    // helper lists
    HelperList m_commonWordsByLength;

    score_t m_minScore = 0;
    score_t m_maxScore = std::numeric_limits<score_t>::max();
};

} // namespace core
