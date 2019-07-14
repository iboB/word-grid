#include "Dictionary.hpp"

#include "Word.hpp"
#include "DictionarySearch.hpp"

#include "lib/UnicodeCharFromUtf8.hpp"

#include <algorithm>

namespace core
{

Dictionary::Dictionary() = default;
Dictionary::~Dictionary() = default;

Dictionary::Dictionary(Dictionary&&) noexcept = default;
Dictionary& Dictionary::operator=(Dictionary&&) noexcept = default;

Dictionary Dictionary::fromUtf8Buffer(chobo::const_memory_view<uint8_t> buffer)
{
    Dictionary d;
    auto begin = reinterpret_cast<const char*>(buffer.data());
    auto end = begin + buffer.size();

    Word cur;
    bool isWordValid = true;

    auto addCurWord = [&]()
    {
        if (isWordValid && cur.length() >= WordTraits::Min_Length)
        {
            d.m_words.emplace_back(cur);
        }
        cur.clear();
        isWordValid = true;
    };

    while (begin < end)
    {
        letter l;
        auto len = UnicodeCharFromUtf8(&l, begin, end);

        if (!len)
        {
            // TODO: log error
            isWordValid = false;
            break; // invalid utf8
        }

        begin += len;

        if (l == '\n' || l == '\r')
        {
            addCurWord();
            continue;
        }

        if (cur.length() == WordTraits::Max_Length)
        {
            // TODO: log error
            isWordValid = false;
        }

        if (isWordValid)
        {
            cur.emplace_back(l);
        }
    }

    addCurWord(); // add last word

    d.sortWords();
    return d;
}

Dictionary Dictionary::fromVector(std::vector<Word>&& words)
{
    Dictionary d;
    d.m_words = std::move(words);
    d.sortWords();
    return d;
}

void Dictionary::sortWords()
{
    if (!std::is_sorted(m_words.begin(), m_words.end()))
    {
        std::sort(m_words.begin(), m_words.end());
    }
    // remove duplicates
    auto end = std::unique(m_words.begin(), m_words.end());
    m_words.erase(end, m_words.end());
}

bool Dictionary::hasWord(const Word& w) const
{
    return std::binary_search(m_words.begin(), m_words.end(), w);
}

Dictionary::SearchResult Dictionary::search(DictionarySearch& inoutSearch, letter l) const
{
    auto& word = inoutSearch.m_word;
    word.emplace_back(l + 1);

    auto begin = m_words.begin();
    auto end = m_words.end();

    if (!inoutSearch.m_ranges.empty())
    {
        begin = inoutSearch.m_ranges.back().begin;
        end = inoutSearch.m_ranges.back().end;
    }

    end = std::lower_bound(begin, end, word);
    word.back() = l;
    begin = std::lower_bound(begin, end, word);

    inoutSearch.m_ranges.push_back({ begin, end });

    if (begin == end) return SearchResult::None;
    if (*begin == word) return SearchResult::Exact;
    return SearchResult::Partial;
}

}