// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "ScoreUtils.hpp"

#include "Grid.hpp"
#include "ScoredWord.hpp"
#include "WordLengthTraits.hpp"

namespace core::impl
{

score_t classicScore(const ScoredWord& sw, const Grid& grid)
{
    // sum element scores
    score_t ret = 0;
    for (auto& c : sw.path) ret += grid[c].score;

    const auto len = sw.word.size();
    if (len <= WordLengthTraits::Short_Max) return ret; // no bonus

    if (len <= WordLengthTraits::Medium_Max)
    {
        // 150%
        ret *= 3;
        ret /= 2;
    }
    else if (len <= WordLengthTraits::Long_Max)
    {
        // 200%
        ret *= 2;
    }
    else
    {
        // 250%
        ret *= 5;
        ret /= 2;
    }

    return ret;
}

} // namespace core::impl
