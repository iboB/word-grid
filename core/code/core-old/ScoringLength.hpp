// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

#include "Scoring.hpp"

namespace core
{

class Grid;
struct ScoredWord;

class CORE_API ScoringLength : public Scoring
{
public:
    ScoringLength(float lengthMultiplier = 2.7f);
    virtual score_t score(const ScoredWord& word, const Grid& grid) const override;
private:
    float m_lengthMultiplier;
};

}
