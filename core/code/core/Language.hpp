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

#include <itlib/expected.hpp>

namespace core
{

class CORE_API Language
{
public:
    const std::string& displayName() const { return m_displayName; }

    enum class FromUtf8Error
    {
        TooShort,
        TooLong,
        InvalidUtf8
    };

    // convert a utf8 string to a word match sequence for this language
    // (namely make use on the conversion table)
    itlib::expected<WordMatchSequence, FromUtf8Error> getWordMatchSequenceFromUtf8(std::string_view str) const;

private:
    friend class LanguageBuilder;

    std::string m_displayName;

    Alphabet m_alphabet;

    LetterConversionTable m_conversionTable;

    Dictionary m_words;
    std::vector<char> m_dictionaryUtf8Buffer;
};

} // namespace core
