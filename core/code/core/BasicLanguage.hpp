// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "WordMatchSequence.hpp"

#include <itlib/expected.hpp>
#include <itlib/flat_map.hpp>

#include <string>

namespace core
{

using LetterConversionTarget = LetterSequence<3>;
using LetterConversionTable = itlib::flat_map<letter_t, LetterConversionTarget>;

// The basic language contains information which is enough for players of a game
class CORE_API BasicLanguage
{
public:
    BasicLanguage();
    ~BasicLanguage();

    BasicLanguage(const BasicLanguage&) = delete;
    BasicLanguage& operator=(const BasicLanguage&) = delete;

    BasicLanguage(BasicLanguage&&) noexcept;
    BasicLanguage& operator=(BasicLanguage&&) noexcept;

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

    uint32_t minWordLength() const { return m_minWordLength; }

protected:
    std::string m_displayName;

    LetterConversionTable m_conversionTable;

    uint32_t m_minWordLength = 1;
};

} // namespace core
