// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "LetterSequence.hpp"

#include <itlib/flat_map.hpp>

namespace core
{

struct AlphabetLetterData
{
    score_t score;
};
using Alphabet = itlib::flat_map<letter_t, AlphabetLetterData>;

using LetterConversionTarget = LetterSequence<3>;
using LetterConversionTable = itlib::flat_map<letter_t, LetterConversionTarget>;

} // namespace core
