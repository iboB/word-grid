// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "LanguageBuilder.hpp"

#include <algorithm>
#include <iostream>

namespace core
{

void LanguageBuilder::setDisplayName(std::string str)
{
    m_language.m_displayName = std::move(str);
}

void LanguageBuilder::setAlphabet(Alphabet alphabet)
{
    m_language.m_alphabet = std::move(alphabet);
}

void LanguageBuilder::setConversionTable(LetterConversionTable table)
{
    assert(m_language.m_dictionaryUtf8Buffer.empty());
    m_language.m_conversionTable = std::move(table);
}

namespace
{

void tryAddWord(Dictionary& words, std::string_view utf8Word, const Language& language)
{
    auto converted = language.getWordMatchSequenceFromUtf8(utf8Word);

    if (converted)
    {
        auto& word = words.emplace_back();
        word.displayString = utf8Word;
        word.letters = *converted;
        return;
    }

    auto errMsg = [&]() -> std::string_view {
        switch (converted.error())
        {
        case Language::FromUtf8Error::InvalidUtf8:
            return "invalid utf8 characters";
        case Language::FromUtf8Error::TooLong:
            return "too long";
        case Language::FromUtf8Error::TooShort:
            return "too short";
        }
        return {};
    }();

    std::cout << "Skipping word '" << utf8Word << "'. Reason: " << errMsg;
}

} // namespace

void LanguageBuilder::setDictionaryUtf8Buffer(std::vector<char> utf8Buffer)
{
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

        tryAddWord(words, utf8Word, m_language);

        wb = we;
    }

    // sort so searches can work
    std::sort(words.begin(), words.end());

    // while we're at it, also remove duplicates
    auto end = std::unique(words.begin(), words.end());
    words.erase(end, words.end());
}

void LanguageBuilder::setDictionaryUtf8Buffer(std::string_view constUtf8Buffer)
{
    std::vector<char> buf(constUtf8Buffer.begin(), constUtf8Buffer.end());
    setDictionaryUtf8Buffer(std::move(buf));
}

Language LanguageBuilder::getLanguage()
{
    return std::move(m_language);
}

} // namespace core
