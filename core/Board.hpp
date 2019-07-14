#pragma once

#include "Grid.hpp"
#include "ScoredDictionary.hpp"

namespace core
{
// a board is needed to define a game
class Board
{
public:
    Board(Grid&& grid, ScoredDictionary&& dic, duration dur);
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    Board(Board&&) noexcept;
    Board& operator=(Board&&) noexcept;

    const Grid& grid() const { return m_grid; }
    const ScoredDictionary& dictionary() const { return m_dictionary; }

    duration remainingTime() const { return m_remainingTime; }
    bool expired() const { return m_remainingTime <= 0; }
    void tick(duration d) { m_remainingTime -= d; }

private:
    Grid m_grid;

    duration m_remainingTime;

    // words which are found in the grid of this board
    // this is NOT the complete game dictionary
    ScoredDictionary m_dictionary;
};
}
