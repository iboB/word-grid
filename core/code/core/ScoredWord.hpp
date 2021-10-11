// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "GridPath.hpp"
#include "LetterSequence.hpp"

#include <string_view>

namespace core
{
struct ScoredWord
{
    // WARNING: much like in the case of DictionaryWord
    // here both of bottom members are views and require a carrier
    // typically this is the dictionary but reincarnated boards may optionally carry them
    // MIND THIS
    LetterSequenceView word;
    std::string_view displayString;

    // path in the associated grid
    GridPath path;

    score_t score = 0; // total score

    bool uncommon = false; // uncommon word

    bool special = 0; // word is a bonus word (score is not necessarily simply aggregated over path)
};
} // namespace core
