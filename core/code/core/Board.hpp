// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "Grid.hpp"
#include "ScoredDictionary.hpp"

#include <unordered_map>

namespace core
{
class Board
{
public:
    Board(Grid&& grid, ScoredDictionary&& dic);
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    Board(Board&&) noexcept;
    Board& operator=(Board&&) noexcept;

    const Grid& grid() const { return m_grid; }
    const ScoredDictionary& dictionary() const { return m_dictionary; }

private:
    Grid m_grid;

    // words which are found in the grid of this board
    // this is NOT the complete game dictionary
    ScoredDictionary m_dictionary;
};
}
