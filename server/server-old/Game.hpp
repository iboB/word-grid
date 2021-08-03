// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "PlayerSet.hpp"
#include "BoardProducerPtr.hpp"

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

class Game
{
public:
    Game(const std::string& id, core::duration restTime, const BoardProducerPtr& boardProducer);
    ~Game();

    Game(const Game&) = delete;
    Game& operator=(const Game&) = delete;

    Game(Game&&) noexcept;
    Game& operator=(Game&&) noexcept = delete;

    const std::string& id() const { return m_id; }
    size_t numPlayers() const { return m_players.size(); }

    void playerJoin(const PlayerPtr& player);
    void playerMove(const PlayerPtr& player, core::Word&& word);
    void playerLeave(const PlayerPtr& player);

    void tick(core::duration d);

private:
    void newBoard();

    // game name
    std::string m_id;
    const core::duration m_restTime;
    BoardProducerPtr m_boardProducer;

    core::duration m_currentRest = 0;

    player_set m_players;

    std::unique_ptr<Board> m_currentBoard;
    std::unique_ptr<Board> m_previousBoard;
};

}
