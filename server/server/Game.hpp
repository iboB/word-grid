#pragma once

#include "PlayerSet.hpp"

#include <core/Dictionary.hpp>

#include <string>

namespace server
{
class Player;
class Round;

class Game
{
public:
    Game(const std::string& id, core::Dictionary&& dictionary);
    ~Game();

    void playerJoin(const PlayerPtr& player);
    void playerLeave(const PlayerPtr& player);

    const std::string& id() const { return m_id; }

private:
    // game name
    std::string m_id;

    // master dictionary for the game
    core::Dictionary m_dictionary;

    player_set m_players;

    std::unique_ptr<Round> m_currentRound;
    std::vector<std::unique_ptr<Round>> m_pendingRounds;
};

}
