#include "Universe.hpp"

#include "Game.hpp"
#include "Player.hpp"

#include <core/GameData.hpp>

namespace server
{

Universe::Universe() = default;
Universe::~Universe() = default;

void Universe::addGame(std::unique_ptr<Game>&& game)
{
    m_gameDatas.emplace_back(game->id());
    m_games.emplace_back(std::move(game));
}

Game* Universe::getGame(const std::string& id)
{
    for (auto& game : m_games)
    {
        if (game->id() == id)
        {
            return game.get();
        }
    }

    return nullptr;
}

void Universe::onNewPlayer(const PlayerPtr& player)
{
    m_players.insert(player);
}

void Universe::playerSetId(const PlayerPtr& player, std::string&& id)
{
    for (auto& p : m_players)
    {
        if (p->id() == id)
        {
            player->sendErrorBadId(std::move(id));
            return;
        }
    }

    if (player->id().empty())
    {
        std::string copyId = id;
        player->sendAcceptId(std::move(copyId));
        player->sendDatas(m_gameDatas);
    }

    player->m_id = std::move(id);
}

}
