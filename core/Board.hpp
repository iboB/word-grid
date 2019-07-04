#pragma once

#include "Grid.hpp"
#include "Dictionary.hpp"
#include "Scoring.hpp"

namespace core
{
// a board is needed to define a game
class Board
{
public:
    Board(Grid&& grid, const Scoring& scoring, Dictionary&& dictionary);
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    Board(Board&&) noexcept;
    Board& operator=(Board&&) noexcept;

    const Grid& grid() const { return m_grid; }
    const Scoring& scoring() const { return m_scoring; }
    const Dictionary& dictionary() const { return m_dictionary; }

private:
    Grid m_grid;
    Scoring m_scoring;

    // words which are found in the grid of this board
    // this is NOT the complete game dictionary
    Dictionary m_dictionary;
};
}
