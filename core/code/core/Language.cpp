// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Language.hpp"

#include "lib/UnicodeCharFromUtf8.hpp"
#include "lib/UnicodeTolower.hpp"

namespace core
{

namespace
{

LetterSequenceView convert(letter_t letter, const LetterConversionTable& conversionTable)
{
    auto cf = conversionTable.find(letter);
    if (cf == conversionTable.end()) return LetterSequenceView(&letter, 1);
    return cf->second.getView();
}

} // namespace

itlib::expected<WordMatchSequence, Language::FromUtf8Error> Language::getWordMatchSequenceFromUtf8(std::string_view utf8String) const
{
    auto p = utf8String.data();
    const auto end = p + utf8String.length();

    WordMatchSequence ret;

    while (p < end)
    {
        letter_t letter;
        auto len = UnicodeCharFromUtf8(&letter, p, end);

        if (!len) return itlib::unexpected(FromUtf8Error::InvalidUtf8);

        p += len;

        letter = UnicodeTolower(letter);

        auto toAdd = convert(letter, m_conversionTable);

        if (ret.size() + toAdd.size() > ret.capacity()) return itlib::unexpected(FromUtf8Error::TooLong);

        for (auto l : toAdd) ret.push_back(l);
    }

    if (ret.size() < WordTraits::Min_Length) return itlib::unexpected(FromUtf8Error::TooShort);

    return ret;
}

} // namespace core
