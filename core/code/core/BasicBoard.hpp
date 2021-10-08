// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "ScoredWord.hpp"
#include "WordMatchSequence.hpp"

#include <vector>

namespace core
{

// a basic board holds a grid and an list of scored words for that grid
// it may optionally (depending on construction) own buffers for the letters and display strings of the words
// For example, if it's in the same address space as the langauge, it does not need to own the buffers too
// the language will do this job for us
class BasicBoard
{
public:
    Grid grid;
    std::vector<ScoredWord> words;

private:
    std::vector<char> m_displayStringBuffer;
    std::vector<WordMatchSequence> m_wordBuffer;
};

}
