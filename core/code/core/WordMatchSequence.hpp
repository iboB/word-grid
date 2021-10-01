// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Types.hpp"
#include "WordTraits.hpp"

#include "LetterSequence.hpp"

namespace core
{
using WordMatchSequence = LetterSequence<WordTraits::Max_Length>;
} // namespace core
