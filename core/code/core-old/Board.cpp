// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Board.hpp"

namespace core
{

Board::Board(Grid&& grid)
    : m_grid(std::move(grid))
{}

Board::~Board() = default;

Board::Board(Board&& other) noexcept = default;
Board& Board::operator=(Board&&) noexcept = default;

}
