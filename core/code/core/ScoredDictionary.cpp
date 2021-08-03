// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "ScoredDictionary.hpp"

#include "Scoring.hpp"

namespace core
{

ScoredDictionary::ScoredDictionary() = default;
ScoredDictionary::~ScoredDictionary() = default;

ScoredDictionary::ScoredDictionary(ScoredDictionary&&) noexcept = default;
ScoredDictionary& ScoredDictionary::operator=(ScoredDictionary&&) noexcept = default;

void ScoredDictionary::clear()
{
    m_words.clear();
}

void ScoredDictionary::addWord(const Word& word, itlib::const_memory_view<GridCoord> coords)
{
    m_words.emplace_back();
    m_words.back().word = word;
    for (auto& c : coords)
    {
        m_words.back().path.emplace_back(c);
    }
}

void ScoredDictionary::scoreWords(const Grid& g, const Scoring& s)
{
    for (auto& w : m_words)
    {
        w.score = s.score(g, itlib::make_memory_view(w.coords));
    }
}

const ScoredWord* ScoredDictionary::getWord(const Word& word) const
{
    for (auto& w : m_words)
    {
        if (w.word == word)
        {
            return &w;
        }
    }

    return nullptr;
}

}
