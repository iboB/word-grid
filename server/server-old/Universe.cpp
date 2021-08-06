// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Universe.hpp"

#include "Game.hpp"
#include "Player.hpp"

namespace server
{

Universe::Universe() = default;
Universe::~Universe() = default;

void Universe::addGame(Game&& game)
{
    m_games.emplace_back(std::move(game));
}

Game* Universe::getGame(const std::string& id)
{
    for (auto& game : m_games)
    {
        if (game.id() == id)
        {
            return &game;
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
        player->sendGames(m_games);
    }

    player->m_id = std::move(id);
}

}
