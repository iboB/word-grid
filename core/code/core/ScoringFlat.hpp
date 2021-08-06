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
#include "Types.hpp"

namespace core
{

class Grid;
struct ScoredWord;

class CORE_API ScoringFlat : public Scoring
{
public:
    ScoringFlat(score_t flatScore = 13);
    virtual score_t score(const ScoredWord& word, const Grid& grid) const override;
private:
    score_t m_flatScore;
};

}
