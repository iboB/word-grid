// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "DictionaryWord.hpp"

#include "LanguageTypes.hpp"

namespace core
{

class CORE_API Language
{
public:
    struct LetterData
    {
        score_t score;
    };

    const std::string& displayName() const { return m_displayName; }

private:
    friend class LanguageBuilder;

    std::string m_displayName;

    Alphabet m_alphabet;

    LetterConversionTable m_conversionTable;

    Dictionary m_words;
    std::vector<char> m_dictionaryUtf8Buffer;
};

} // namespace core
