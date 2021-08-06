// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
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

void ScoredDictionary::addWord(const Word& word, const GridPath& path)
{
    auto& newWord = m_words.emplace_back();
    newWord.word = word;
    newWord.path = path;
}

void ScoredDictionary::scoreWords(const Grid& g, const Scoring& s)
{
    for (auto& w : m_words)
    {
        s.score(w, g);
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
