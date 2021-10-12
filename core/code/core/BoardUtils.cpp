// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "BoardUtils.hpp"

#include "BasicBoard.hpp"

#include <itlib/flat_map.hpp>

namespace core::impl
{

bool scheckAllCellsUsedTwice(const BasicBoard& bb)
{
    auto& dim = bb.grid.dim();
    auto area = dim.area();
    std::vector<int> uses(area, 0);
    uint32_t twiceUses = 0;
    for (auto& w : bb.words)
    {
        for (auto& c : w.path)
        {
            auto i = dim.indexOf(c);
            ++uses[i];
            if (uses[i] == 2) ++twiceUses;
            if (twiceUses == area) return true; // no need to loop more
        }
    }

    return false;
}

bool scheckDupWordsSameScore(const BasicBoard& bb)
{
    itlib::flat_map<LetterSequenceView, score_t> scoresPerWord;
    scoresPerWord.reserve(bb.words.size());

    for (auto& w : bb.words)
    {
        auto i = scoresPerWord.insert({w.word, w.score});
        if (!i.second)
        {
            // word already exists
            if (i.first->second != w.score) return false; // different score
        }
    }

    return true;
}

} // namespace core::impl
