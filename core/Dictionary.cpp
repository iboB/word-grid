#include "Dictionary.hpp"

#include "Word.hpp"

#include "lib/UnicodeCharFromUtf8.hpp"

#include <algorithm>

namespace core
{

Dictionary::Dictionary() = default;
Dictionary::~Dictionary() = default;

void Dictionary::loadFromUtf8Buffer(chobo::const_memory_view<uint8_t> buffer)
{
    auto begin = reinterpret_cast<const char*>(buffer.data());
    auto end = begin + buffer.size();

    Word cur;
    bool isWordValid = true;

    auto addCurWord = [&]()
    {
        if (isWordValid && cur.length() >= WordTraits::Min_Length)
        {
            m_words.emplace_back(cur);
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

    if (!std::is_sorted(m_words.begin(), m_words.end()))
    {
        std::sort(m_words.begin(), m_words.end());
    }
}

}