#pragma once

#include <core/Dictionary.hpp>

#include <string>

namespace server
{
class Player;
class Round;

class Game
{
public:
    Game(const std::string& name, core::Dictionary&& dictionary);
    ~Game();

    const std::string& name() const { return m_name; }

private:
    // game name
    std::string m_name;

    // master dictionary for the game
    core::Dictionary m_dictionary;

    std::unique_ptr<Round> m_currentRound;
    std::vector<std::unique_ptr<Round>> m_pendingRounds;
};

}
