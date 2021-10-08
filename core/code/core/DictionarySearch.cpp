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

DictionarySearch::Range DictionarySearch::range() const
{
    if (m_ranges.empty()) return {m_dictionary.begin(), m_dictionary.end()};
    if (m_overflow) return {m_dictionary.end(), m_dictionary.end()};
    return m_ranges.back();
}

DictionarySearch::Result DictionarySearch::push(letter_t l)
{
    if (m_matchWord.size() == m_matchWord.capacity())
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

    m_matchWord.push_back(l + 1); // somewhat hacky +1 for lower bound of end

    // this temporary dictionary here is so we would type less for lower_bound below
    // it only cares about the letters anyway
    DictionaryWord tmp;
    tmp.letters = m_matchWord.getView();
    end = std::lower_bound(begin, end, tmp);
    m_matchWord.back() = l; // real back
    begin = std::lower_bound(begin, end, tmp);

    m_ranges.push_back({begin, end});

    if (begin == end) return Result::None;
    if (begin->letters == m_matchWord.getView()) return Result::Exact;
    return Result::Partial;
}

void DictionarySearch::pop()
{
    if (m_overflow)
    {
        --m_overflow;
        return;
    }
    assert(m_matchWord.size() > 0);
    assert(m_ranges.size() == m_matchWord.size());
    m_matchWord.pop_back();
    m_ranges.pop_back();
}

} // namespace core
