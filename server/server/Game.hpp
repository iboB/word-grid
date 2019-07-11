#pragma once

#include "PlayerSet.hpp"

#include <string>

namespace core
{
class Word;
}

namespace server
{
class Round;
class BoardProducer;

class Game
{
public:
    Game(const std::string& id, BoardProducer& boardProducer);
    ~Game();

    const std::string& id() const { return m_id; }

    void playerJoin(const PlayerPtr& player);
    void playerLeave(const PlayerPtr& player);
    void playerMove(const PlayerPtr& player, core::Word&& word);

private:
    // game name
    std::string m_id;

    BoardProducer& m_boardProducer;

    player_set m_players;

    std::unique_ptr<Round> m_currentRound;
};

}
