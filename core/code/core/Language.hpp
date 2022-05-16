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
    using HelperListView = itlib::span<std::reference_wrapper<const DictionaryWord>>;
    HelperListView shortWords() const { return m_shortWords; }
    HelperListView mediumWords() const { return m_mediumWords; }
    HelperListView longWords() const { return m_longWords; }
    HelperListView longerWords() const { return m_longerWords; }
    HelperListView superLongWords() const { return m_superLongWords; }

private:
    friend class LanguageBuilder;

    Alphabet m_alphabet;
    AlphabetFrequencyTable m_alphabetFrequencyTable;

    Specials m_specials;

    Dictionary m_dictionary;
    std::vector<char> m_dictionaryUtf8Buffer;

    // helper lists
    HelperList m_commonWordsByLength;
    HelperListView m_shortWords;
    HelperListView m_mediumWords;
    HelperListView m_longWords;
    HelperListView m_longerWords;
    HelperListView m_superLongWords;
};

} // namespace core
