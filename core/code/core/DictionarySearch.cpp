// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "DictionarySearch.hpp"

#include <algorithm>

namespace core
{

DictionarySearch::DictionarySearch(const Dictionary& dictionary)
    : m_dictionary(dictionary)
{}

DictionarySearch::Result DictionarySearch::push(letter_t l)
{
    auto& match = m_matchWord.letters;
    if (match.size() == match.capacity())
    {
        ++m_overflow;
        return Result::None;
    }

    auto begin = m_dictionary.begin();
    auto end = m_dictionary.end();

    if (!m_ranges.empty())
    {
        begin = m_ranges.back().begin;
        end = m_ranges.back().end;
    }

    match.push_back(l + 1); // somewhat hacky +1 for lower bound of end
    end = std::lower_bound(begin, end, m_matchWord);
    match.back() = l; // real back
    begin = std::lower_bound(begin, end, m_matchWord);

    m_ranges.push_back({begin, end});

    if (begin == end) return Result::None;
    if (begin->letters == match) return Result::Exact;
    return Result::Partial;
}

void DictionarySearch::pop()
{
    if (m_overflow)
    {
        --m_overflow;
        return;
    }
    auto& match = m_matchWord.letters;
    assert(match.size() > 0);
    assert(m_ranges.size() == match.size());
    match.pop_back();
    m_ranges.pop_back();
}

} // namespace core
