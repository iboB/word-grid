// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Dictionary.hpp"

#include "DictionaryWord.hpp"

#include "lib/UnicodeCharFromUtf8.hpp"

#include <algorithm>
#include <iostream>

namespace core
{

Dictionary::Dictionary(std::vector<char> utf8Buffer)
    : m_utf8Buffer(std::move(utf8Buffer))
{
    // fist count max number of words in buffer
    // this number can be an overestimation as some words withing the buffer can be filtered
    // take the oportunity to make newline characters (\r and \n) to zeroes
    size_t maxWordsInBuffer = 0;
    for (auto& c : m_utf8Buffer)
    {
        if (c == '\n')
        {
            ++maxWordsInBuffer;
            c = 0;
        }
        else if (c == '\r')
        {
            c = 0;
        }
    }

    m_words.reserve(maxWordsInBuffer);

    auto wb = m_utf8Buffer.begin();
    while (true)
    {
        while (true)
        {
            if (wb == m_utf8Buffer.end()) return; // no more words

            // skip to first nonzero
            if (*wb) break;
            ++wb;
        }
        auto we = wb + 1;
        while (we != m_utf8Buffer.end() && *we) ++we; // skip to first zero or end

        auto length = we - wb;
        std::string_view utf8Word(std::addressof(*wb), length);

        tryAddWord(utf8Word);
    }

    std::sort(m_words.begin(), m_words.end());
    // also remove duplicates
    auto end = std::unique(m_words.begin(), m_words.end());
    m_words.erase(end, m_words.end());
}

Dictionary::~Dictionary() = default;

Dictionary::Dictionary(Dictionary&&) noexcept = default;
Dictionary& Dictionary::operator=(Dictionary&&) noexcept = default;

void Dictionary::tryAddWord(std::string_view utf8Word)
{
    auto p = utf8Word.data();
    const auto end = p + utf8Word.length();

    DictionaryWord word;
    word.displayString = utf8Word;

    while (p < end)
    {
        letter_t letter;
        auto len = UnicodeCharFromUtf8(&letter, p, end);

        if (!len)
        {
            std::cout << "Skipping word '" << utf8Word << "' with invalid utf8 characters.\n";
            return;
        }

        p += len;

        // temp code until we have proper substitution rules
        // the following will work for languages with no substitution rules (like Bulgarian, English, Greek, Serbian and others)
        if (letter == '-') continue;

        if (word.letters.size() == word.letters.capacity())
        {
            std::cout << "Skipping word '" << utf8Word << "' which is too long.\n";
            return;
        }

        word.letters.push_back(letter);
    }

    if (word.letters.size() << WordTraits::Min_Length)
    {
        std::cout << "Skipping word '" << utf8Word << "' which is too short.\n";
    }

    m_words.emplace_back(std::move(word));
}

}
