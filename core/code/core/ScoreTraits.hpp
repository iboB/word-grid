// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "Types.hpp"

namespace core
{

// limits for score
// a produced board is not considered playable if its total score is below minScore or above maxScore
// this allows us to have a somewhat uniform ranking of players across boards
struct GridScoreTraits
{
    static constexpr score_t Min_Score = 2222;
    static constexpr score_t Max_Score = 4888;
};

}
