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

#include <memory>
#include <vector>

namespace server
{
class Game;

class Universe
{
public:
    Universe();
    ~Universe();

    void addGame(Game&& game);
    Game* getGame(const std::string& id);

    void onNewPlayer(const PlayerPtr& player);
    void playerSetId(const PlayerPtr& player, std::string&& id);

private:
    std::vector<Game> m_games;

    player_set m_players;
};

}