// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Grid.hpp"
#include "ScoredWord.hpp"

#include <vector>

namespace core
{

// a basic board holds a grid and an list of scored words for that grid
// ScoredWords are a view so there needs to be a holder of the data!
// The holder is determined by the users of this helper
class BasicBoard
{
public:
    Grid grid;
    std::vector<ScoredWord> words;
};

}
