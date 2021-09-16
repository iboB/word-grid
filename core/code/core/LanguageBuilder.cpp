// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "LanguageBuilder.hpp"

#include "lib/UnicodeCharFromUtf8.hpp"
#include "lib/UnicodeTolower.hpp"

#include <algorithm>
#include <iostream>
#include <cassert>

namespace core
{

void LanguageBuilder::setDisplayName(std::string str)
{
    m_language.m_displayName = std::move(str);
}

void LanguageBuilder::setAlphabet(Alphabet alphabet)
{
    assert(m_language.m_dictionaryUtf8Buffer.empty());
    m_language.m_alphabet = std::move(alphabet);
}

void LanguageBuilder::setConversionTable(LetterConversionTable table)
{
    assert(m_language.m_dictionaryUtf8Buffer.empty());
    m_language.m_conversionTable = std::move(table);
}

namespace
{

LetterSequenceView convert(letter_t letter, const LetterConversionTable& conversionTable)
{
    auto cf = conversionTable.find(letter);
    if (cf == conversionTable.end())
    {
        return LetterSequenceView(&letter, 1);
    }

    return itlib::make_memory_view(cf->second);
}

void tryAddWord(Dictionary& words, std::string_view utf8Word, const LetterConversionTable& conversionTable)
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

        letter = UnicodeTolower(letter);

        auto toAdd = convert(letter, conversionTable);

        if (word.letters.size() + toAdd.size() > word.letters.capacity())
        {
            std::cout << "Skipping word '" << utf8Word << "' which is too long.\n";
            return;
        }

        for (auto l : toAdd)
        {
            word.letters.push_back(l);
        }
    }

    if (word.letters.size() << WordTraits::Min_Length)
    {
        std::cout << "Skipping word '" << utf8Word << "' which is too short.\n";
        return;
    }

    words.emplace_back(std::move(word));
}

}

void LanguageBuilder::setDictionaryUtf8Buffer(std::vector<char> utf8Buffer)
{
    assert(!m_language.m_alphabet.empty());
    auto& buf = m_language.m_dictionaryUtf8Buffer;

    buf = std::move(utf8Buffer);

    // fist count max number of words in buffer
    // this number can be an overestimation as some words withing the buffer can be filtered
    // take the oportunity to make newline characters (\r and \n) to zeroes
    size_t maxWordsInBuffer = 0;
    for (auto& c : buf)
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

    auto& words = m_language.m_words;
    words.reserve(maxWordsInBuffer);

    // second pass: build dictionary
    auto wb = buf.begin();
    while (true)
    {
        while (true)
        {
            if (wb == buf.end()) return; // no more words

            // skip to first nonzero
            if (*wb) break;
            ++wb;
        }
        auto we = wb + 1;
        while (we != buf.end() && *we) ++we; // skip to first zero or end

        auto length = we - wb;
        std::string_view utf8Word(std::addressof(*wb), length);

        tryAddWord(words, utf8Word, m_language.m_conversionTable);
    }

    // sort so searches can work
    std::sort(words.begin(), words.end());

    // while we're at it, also remove duplicates
    auto end = std::unique(words.begin(), words.end());
    words.erase(end, words.end());
}

Language LanguageBuilder::getLanguage()
{
    assert(!m_language.m_displayName.empty());
    assert(!m_language.m_dictionaryUtf8Buffer.empty());
    return std::move(m_language);
}

} // namespace core
