// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "LetterSequence.hpp"
#include "lib/UnicodeCharFromUtf8.hpp"

namespace core
{

// convert string to letter sequence
// will work around errors:
// * invalid utf8 characters - stop processing
// * string longer than N - trimmed
// returns false if any kind of error was encountered and true otherwise
template <size_t N>
bool LetterSequence_FromUtf8(LetterSequence<N>& seq, std::string_view str)
{
    auto p = str.data();
    const auto end = p + str.length();
    while (p < end)
    {
        if (seq.size() == seq.capacity()) return false;

        letter_t letter;
        auto len = UnicodeCharFromUtf8(&letter, p, end);
        if (!len) return false;

        p += len;
        seq.push_back(letter);
    }

    return true;
}

template <typename LS>
LS LetterSequence_FromUtf8(std::string_view str)
{
    LS ret;
    LetterSequence_FromUtf8(ret, str);
    return ret;
}

} // namespace core
