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
    void setDisplayName(std::string str);

    void setAlphabet(Alphabet alphabet);

    void setConversionTable(LetterConversionTable table);

    void setDictionaryUtf8Buffer(std::vector<char> utf8Buffer);
    void setDictionaryUtf8Buffer(std::string_view constUtf8Buffer);

    Language getLanguage();

private:
    Language m_language;
};

} // namespace core
