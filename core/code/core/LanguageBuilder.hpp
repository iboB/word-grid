// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "Language.hpp"

#include <itlib/expected.hpp>

#include <bitset>

namespace core
{

class CORE_API LanguageBuilder
{
public:
    LanguageBuilder();

    enum RequiredLanguageFields
    {
        Lang_DisplayName,
        Lang_Alphabet,
        Lang_Dictionary,
        Num_RequiredLanguageFields
    };
    using MissingFields = std::bitset<Num_RequiredLanguageFields>;

    const MissingFields& missingRequiredFields() const { return m_missingFields; }

    LanguageBuilder& setDisplayName(std::string str);

    LanguageBuilder& setAlphabet(Alphabet alphabet);
    LanguageBuilder& setSpecials(Specials specials);

    LanguageBuilder& setMinWordLength(uint32_t length);

    LanguageBuilder& setConversionTable(LetterConversionTable table);

    // add all words from a single buffer
    // will look for a the separator and interpret all words after the separtor as uncommon
    static inline constexpr std::string_view Uncommon_Separator = "----------------";
    LanguageBuilder& setDictionaryUtf8Buffer(std::vector<char> utf8Buffer);
    LanguageBuilder& setDictionaryUtf8Buffer(std::string_view constUtf8Buffer);

    LanguageBuilder& setMinScore(score_t score);
    LanguageBuilder& setMaxScore(score_t score);

    std::vector<std::string> getWarnings();

    // if this function succeeds it will clear all warnings and missing fields
    // essenially making the builder reusable to build another language
    itlib::expected<Language, MissingFields> getLanguage();

private:
    void tryAddWord(std::vector<DictionaryWord>& words, std::string_view utf8Word, bool uncommon);

    Language m_language;
    MissingFields m_missingFields;
    std::vector<std::string> m_warnings;
};

} // namespace core
