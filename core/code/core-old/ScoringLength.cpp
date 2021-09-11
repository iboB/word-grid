// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "ScoringLength.hpp"

#include "ScoredWord.hpp"

#include <cmath>

namespace core
{

ScoringLength::ScoringLength(float lengthMultiplier)
    : m_lengthMultiplier(lengthMultiplier)
{}

score_t ScoringLength::score(const ScoredWord& word, const Grid&) const
{
    return score_t(std::round(word.word.length() * m_lengthMultiplier));
}

}
