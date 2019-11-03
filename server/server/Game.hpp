// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "PlayerSet.hpp"

#include <core/Types.hpp>

#include <string>
#include <vector>

namespace core
{
class Word;
}

namespace server
{
class Board;
class BoardProducer;

class Game
{
public:
    Game(const std::string& id, core::duration restTime, BoardProducer& boardProducer);
    ~Game();

    const std::string& id() const { return m_id; }

    void playerJoin(const PlayerPtr& player);
    void playerMove(const PlayerPtr& player, core::Word&& word);
    void playerLeave(const PlayerPtr& player);

    void tick(core::duration d);

private:
    void newBoard();

    // game name
    std::string m_id;
    const core::duration m_restTime;
    core::duration m_currentRest = 0;

    BoardProducer& m_boardProducer;

    player_set m_players;

    std::unique_ptr<Board> m_currentBoard;
    std::unique_ptr<Board> m_previousBoard;
};

}
