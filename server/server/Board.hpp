// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "PlayerPtr.hpp"

#include <core/Grid.hpp>
#include <core/ScoredDictionary.hpp>

#include <unordered_map>

namespace server
{
// a board is needed to define a game
class Board
{
public:
    Board(core::Grid&& grid, core::ScoredDictionary&& dic, core::duration dur);
    ~Board();

    Board(const Board&) = delete;
    Board& operator=(const Board&) = delete;

    Board(Board&&) noexcept;
    Board& operator=(Board&&) noexcept;

    const core::Grid& grid() const { return m_grid; }
    const core::ScoredDictionary& dictionary() const { return m_dictionary; }

    core::duration remainingTime() const { return m_remainingTime; }
    bool expired() const { return m_remainingTime <= 0; }
    void tick(core::duration d) { m_remainingTime -= d; }

    void playerMove(const PlayerPtr& player, core::Word&& word);

    struct PlayerBoardData
    {
        core::score_t totalScore;
        std::vector<const core::ScoredWord*> scores;
    };
    using PlayerBoardDataMap = std::unordered_map<PlayerPtr, PlayerBoardData>;

    const PlayerBoardDataMap& playerDatas() const { return m_playerDatas; }

private:
    core::Grid m_grid;

    // words which are found in the grid of this board
    // this is NOT the complete game dictionary
    core::ScoredDictionary m_dictionary;

    core::duration m_remainingTime;

    PlayerBoardDataMap m_playerDatas;
};
}
