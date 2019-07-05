#pragma once

#include "PlayerSet.hpp"

#include <memory>
#include <vector>

namespace core
{
class GameData;
}

namespace server
{
class Game;

class Universe
{
public:
    Universe();
    ~Universe();

    void addGame(std::unique_ptr<Game>&& game);
    Game* getGame(const std::string& id);

    void onNewPlayer(const PlayerPtr& player);
    void playerSetId(const PlayerPtr& player, std::string&& id);

private:
    std::vector<std::unique_ptr<Game>> m_games;
    std::vector<core::GameData> m_gameDatas;

    player_set m_players;
};

}