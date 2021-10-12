// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "LanguageBuilder.hpp"

#include "WordLengthTraits.hpp"

#include <numeric>

namespace core
{

LanguageBuilder::LanguageBuilder()
{
    m_missingFields.set();
}

LanguageBuilder& LanguageBuilder::setDisplayName(std::string str)
{
    m_language.m_displayName = std::move(str);
    m_missingFields[Lang_DisplayName] = false;
    return *this;
}

LanguageBuilder& LanguageBuilder::setAlphabet(Alphabet alphabet)
{
    score_t highestScore = 0; // highest score within the alphabet
    for (auto& l : alphabet)
    {
        if (l.empty())
        {
            m_warnings.push_back("Rejecting alphabet with empty items");
            return *this;
        }
        if (l.score() > highestScore) highestScore = l.score();
    }
    if (highestScore == 0)
    {
        m_warnings.push_back("Rejecting alphabet with no positive scores");
        return *this;
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

    m_missingFields[Lang_Alphabet] = false;
    return *this;
}

LanguageBuilder& LanguageBuilder::setSpecials(Specials specials)
{
    m_language.m_specials = std::move(specials);
    return *this;
}

LanguageBuilder& LanguageBuilder::setMinWordLength(uint32_t length)
{
    // conversion table must be set before dictionary
    assert(m_language.m_dictionaryUtf8Buffer.empty());

    if (length < 1)
    {
        m_warnings.push_back("Rejecting zero min word length");
        return *this;
    }

    m_language.m_minWordLength = length;
    return *this;
}

LanguageBuilder& LanguageBuilder::setConversionTable(LetterConversionTable table)
{
    // conversion table, if present, must be set before dictionary
    assert(m_language.m_dictionaryUtf8Buffer.empty());
    m_language.m_conversionTable = std::move(table);
    return *this;
}

void LanguageBuilder::tryAddWord(std::vector<DictionaryWord>& words, std::string_view utf8Word, bool uncommon)
{
    auto converted = m_language.getWordMatchSequenceFromUtf8(utf8Word);

    if (converted)
    {
        auto& word = words.emplace_back();
        word.displayString = utf8Word;
        word.letters = *converted;
        word.uncommon = uncommon;
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

    auto& warning = m_warnings.emplace_back();
    warning += "Skipping word '";
    warning += utf8Word;
    warning += "'. Reason: ";
    warning += errMsg;
}

LanguageBuilder& LanguageBuilder::setDictionaryUtf8Buffer(std::vector<char> utf8Buffer)
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
    bool foundUncommonSeparator = false;
    size_t maxCommonWordsInfBuffer = 0;
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

        wb = we;

        if (utf8Word == Uncommon_Separator)
        {
            foundUncommonSeparator = true;
            continue;
        }

        maxCommonWordsInfBuffer += !foundUncommonSeparator;

        // add if anything else remains
        if (!utf8Word.empty()) tryAddWord(words, utf8Word, foundUncommonSeparator);
    }
end:

    m_language.m_dictionary = Dictionary(std::move(words));

    // build helper lists
    {
        auto& cw = m_language.m_commonWordsByLength;
        cw.reserve(maxCommonWordsInfBuffer);
        for (auto& w : m_language.m_dictionary)
        {
            if (!w.uncommon) cw.push_back(w);
        }
        std::stable_sort(cw.begin(), cw.end(),
            [](const DictionaryWord& a, const DictionaryWord& b) { return a.letters.size() < b.letters.size(); });

        auto p = cw.data();
        auto subListStart = cw.data();
        const auto pend = cw.data() + cw.size();

        auto fillView = [&](Language::HelperListView& view, size_t length) {
            for (; p != pend; ++p)
            {
                if (p->get().letters.size() > length) break;
            }
            view.reset(subListStart, p - subListStart);
            subListStart = p;
        };
        fillView(m_language.m_shortWords, WordLengthTraits::Short_Max);
        fillView(m_language.m_mediumWords, WordLengthTraits::Medium_Max);
        fillView(m_language.m_longWords, WordLengthTraits::Long_Max);
        fillView(m_language.m_longerWords, WordLengthTraits::Longer_Max);
        m_language.m_superLongWords.reset(subListStart, pend - subListStart);
    }

    m_missingFields[Lang_Dictionary] = false;
    return *this;
}

LanguageBuilder& LanguageBuilder::setDictionaryUtf8Buffer(std::string_view constUtf8Buffer)
{
    std::vector<char> buf(constUtf8Buffer.begin(), constUtf8Buffer.end());
    setDictionaryUtf8Buffer(std::move(buf));
    return *this;
}

LanguageBuilder& LanguageBuilder::setMinScore(score_t score)
{
    m_language.m_minScore = score;
    return *this;
}

LanguageBuilder& LanguageBuilder::setMaxScore(score_t score)
{
    m_language.m_maxScore = score;
    return *this;
}

std::vector<std::string> LanguageBuilder::getWarnings()
{
    std::vector<std::string> ret;
    m_warnings.swap(ret);
    return ret;
}

itlib::expected<Language, LanguageBuilder::MissingFields> LanguageBuilder::getLanguage()
{
    if (!m_missingFields.none()) return itlib::unexpected(m_missingFields);

    m_missingFields.reset();
    m_warnings.clear();

    Language ret;
    std::swap(m_language, ret);
    return ret;
}

} // namespace core
