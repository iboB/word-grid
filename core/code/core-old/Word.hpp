// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "LetterSequence.hpp"
#include "WordTraits.hpp"

namespace core
{
class Word : public LetterSequence<WordTraits::Max_Length, Word> {};
}