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
#include <unordered_map>
#include <vector>

namespace core
{
class Word;
class Board;
struct ScoredWord;
}

namespace server
{
class BoardProducer;

class Game
{
public:
    Game(const std::string& id, core::duration restTime, BoardProducer& boardProducer);
    ~Game();

    const std::string& id() const { return m_id; }

    void playerJoin(const PlayerPtr& player);
    void playerMove(const PlayerPtr& player, core::Word&& word);

private:
    // game name
    std::string m_id;
    const core::duration m_restTime;
    core::duration m_currentRest = 0;

    BoardProducer& m_boardProducer;

    struct PlayerGameData
    {
        core::score_t totalScore;
        std::vector<const core::ScoredWord*> scores;
    };
    std::unordered_map<PlayerPtr, PlayerGameData> m_playerDatas;

    std::unique_ptr<core::Board> m_currentBoard;
    std::unique_ptr<core::Board> m_previousBoard;
};

}
