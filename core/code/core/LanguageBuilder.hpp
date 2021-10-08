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

namespace core
{

class CORE_API LanguageBuilder
{
public:
    LanguageBuilder& setDisplayName(std::string str);

    LanguageBuilder& setAlphabet(Alphabet alphabet);
    LanguageBuilder& setSpecials(Specials specials);

    LanguageBuilder& setMinWordLength(uint32_t length);

    LanguageBuilder& setConversionTable(LetterConversionTable table);

    LanguageBuilder& setDictionaryUtf8Buffer(std::vector<char> utf8Buffer);
    LanguageBuilder& setDictionaryUtf8Buffer(std::string_view constUtf8Buffer);

    LanguageBuilder& setMinScore(score_t score);
    LanguageBuilder& setMaxScore(score_t score);

    Language getLanguage();

private:
    Language m_language;
};

} // namespace core
