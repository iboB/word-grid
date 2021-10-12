// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once
#include "API.h"

// these functions should be rearranged better

namespace core
{

class BasicBoard;

namespace impl
{

// suitability checks

// check that all grid cells are used at least twice
CORE_API bool scheckAllCellsUsedTwice(const BasicBoard& bb);

// check that duplicate instances of a word have the same score
CORE_API bool scheckDupWordsSameScore(const BasicBoard& bb);

}
}
