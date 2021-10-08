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
#include "LanguageTypes.hpp"
#include "WordMatchSequence.hpp"

#include <itlib/expected.hpp>

#include <limits>

namespace core
{

class CORE_API Language
{
public:
    Language();
    ~Language();

    Language(const Language&) = delete;
    Language& operator=(const Language&) = delete;

    Language(Language&&) noexcept;
    Language& operator=(Language&&) noexcept;

    const std::string& displayName() const { return m_displayName; }

    const Alphabet& alphabet() const { return m_alphabet; }

    // an array with repeated values per letter, such that taking a random element from it
    // will produce an alphabet item with probablity inverse to the score
    // if the score of an item is non-positive the probability is equal calculated as if the item's score is
    // equal to the item with the highest positive score positive score + the provided score
    using AlphabetFrequencyTable = std::vector<std::reference_wrapper<const GridElement>>;
    const AlphabetFrequencyTable& alphabetFrequencyTable() const { return m_alphabetFrequencyTable; }

    enum class FromUtf8Error
    {
        TooShort,
        TooLong,
        InvalidUtf8
    };

    // convert a utf8 string to a word match sequence for this language
    // (namely make use on the conversion table)
    itlib::expected<WordMatchSequence, FromUtf8Error> getWordMatchSequenceFromUtf8(std::string_view str) const;

    uint32_t minWordLength() const { return m_minWordLength; }

    const Dictionary& dictionary() const { return m_dictionary; }

    // limits for score
    // a produced board is not considered playable if its total score is below minScore or above maxScore
    // this allows us to have a somewhat uniform ranking of players across boards in the same language
    score_t minScore() const { return m_minScore; }
    score_t maxScore() const { return m_maxScore; }

private:
    friend class LanguageBuilder;

    std::string m_displayName;

    Alphabet m_alphabet;
    AlphabetFrequencyTable m_alphabetFrequencyTable;

    Specials m_specials;

    LetterConversionTable m_conversionTable;

    uint32_t m_minWordLength = 1;
    Dictionary m_dictionary;
    std::vector<char> m_dictionaryUtf8Buffer;
    std::vector<letter_t> m_dictionaryLetterBuffer;

    score_t m_minScore = 0;
    score_t m_maxScore = std::numeric_limits<score_t>::max();
};

} // namespace core
