// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "ScoringFlat.hpp"

namespace core
{

ScoringFlat::ScoringFlat(score_t flatScore)
    : m_flatScore(flatScore)
{}

score_t ScoringFlat::score(const ScoredWord&, const Grid&) const
{
    return m_flatScore;
}

}
