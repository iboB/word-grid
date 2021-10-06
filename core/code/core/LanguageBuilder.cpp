// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "LanguageBuilder.hpp"

#include <iostream>
#include <numeric>

namespace core
{

void LanguageBuilder::setDisplayName(std::string str)
{
    m_language.m_displayName = std::move(str);
}

void LanguageBuilder::setAlphabet(Alphabet alphabet)
{
    score_t highestScore = 0; // highest score within the alphabet
    for (auto& l : alphabet)
    {
        if (l.score() > highestScore) highestScore = l.score();
    }
    if (highestScore == 0)
    {
        std::cout << "Rejecting alphabet with no positive scores\n";
        return;
    }

    m_language.m_alphabet = std::move(alphabet);

    // prepare frequency table
    const auto& ab = m_language.m_alphabet;
    auto& ft = m_language.m_alphabetFrequencyTable;
    ft.clear();

    auto scoreFor = [highestScore](const GridElement& item) {
        // score if positive, otherwise highest + abs
        return item.score() > 0 ? item.score() : highestScore + std::abs(item.score());
    };

    auto ftLcm = 1;
    for (auto& l : ab)
    {
        const auto score = scoreFor(l);
        ftLcm = std::lcm(ftLcm, score);
    }

    // we could make another loop to calculate a size to reserver here, but why bother

    for (auto& l : ab)
    {
        const auto score = scoreFor(l);
        auto freq = ftLcm / score;
        while (freq-- > 0) // "freq --> 0" looks cooler, but we'll live without it for clang-format's sake
        {
            ft.emplace_back(l);
        }
    }
}

void LanguageBuilder::setSpecials(Specials specials)
{
    m_language.m_specials = std::move(specials);
}

void LanguageBuilder::setConversionTable(LetterConversionTable table)
{
    assert(m_language.m_dictionaryUtf8Buffer.empty());
    m_language.m_conversionTable = std::move(table);
}

namespace
{

void tryAddWord(std::vector<DictionaryWord>& words, std::string_view utf8Word, const Language& language)
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
        case Language::FromUtf8Error::InvalidUtf8: return "invalid utf8 characters";
        case Language::FromUtf8Error::TooLong: return "too long";
        case Language::FromUtf8Error::TooShort: return "too short";
        }
        return {};
    }();

    std::cout << "Skipping word '" << utf8Word << "'. Reason: " << errMsg << '\n';
}

} // namespace

void LanguageBuilder::setDictionaryUtf8Buffer(std::vector<char> utf8Buffer)
{
    auto& buf = m_language.m_dictionaryUtf8Buffer;

    buf = std::move(utf8Buffer);

    // fist count max number of words in buffer
    // this number can be an overestimation as some words withing the buffer can be filtered
    // take the oportunity to set newline and tab characters (\r \n \t) to zeroes (separators)
    size_t maxWordsInBuffer = 0;
    for (auto& c : buf)
    {
        if (c == '\n')
        {
            ++maxWordsInBuffer;
            c = 0;
        }
        else if (c == '\r' || c == '\t')
        {
            c = 0;
        }
    }

    std::vector<DictionaryWord> words;
    words.reserve(maxWordsInBuffer);

    // second pass: build dictionary
    auto wb = buf.begin();
    while (true)
    {
        while (true)
        {
            if (wb == buf.end())
            {
                // no more words.
                goto end; // lazy double loop exit with goto
            }

            // skip to first nonzero
            if (*wb) break;
            ++wb;
        }
        auto we = wb + 1;
        while (we != buf.end() && *we) ++we; // skip to first zero or end

        auto length = we - wb;
        std::string_view utf8Word(std::addressof(*wb), length);

        // strip spaces from front and back (but keep ones inside)
        while (!utf8Word.empty() && utf8Word.front() == ' ') utf8Word.remove_prefix(1);
        while (!utf8Word.empty() && utf8Word.back() == ' ') utf8Word.remove_suffix(1);

        // add if anything else remains
        if (!utf8Word.empty()) tryAddWord(words, utf8Word, m_language);

        wb = we;
    }
end:

    m_language.m_dictionary = Dictionary(std::move(words));
}

void LanguageBuilder::setDictionaryUtf8Buffer(std::string_view constUtf8Buffer)
{
    std::vector<char> buf(constUtf8Buffer.begin(), constUtf8Buffer.end());
    setDictionaryUtf8Buffer(std::move(buf));
}

void LanguageBuilder::setMinScore(score_t score)
{
    m_language.m_minScore = score;
}

void LanguageBuilder::setMaxScore(score_t score)
{
    m_language.m_maxScore = score;
}

Language LanguageBuilder::getLanguage()
{
    return std::move(m_language);
}

} // namespace core
