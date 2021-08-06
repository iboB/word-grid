// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Player.hpp"

#include "Universe.hpp"
#include "Game.hpp"

#include <cassert>

namespace server
{
Player::Player() = default;
Player::~Player() = default;

void Player::setUniverse(Universe& u)
{
    assert(!m_universe);
    m_universe = &u;
}

void Player::onSetId(std::string&& id)
{
    m_universe->playerSetId(shared_from_this(), std::move(id));
}

void Player::onChooseGame(std::string&& id)
{
    auto self = shared_from_this();

    if (m_game)
    {
        if (m_game->id() == id)
        {
            return; // we're already in that game
        }

        m_game->playerLeave(self);
    }

    m_game = m_universe->getGame(id);
    if (!m_game)
    {
        sendFatalError(std::string("No such game ") + id);
        return;
    }

    m_game->playerJoin(self);
}

void Player::onPlayWord(core::Word&& w)
{
    if (!m_game)
    {
        sendFatalError("Not in a game");
        return;
    }

    m_game->playerMove(shared_from_this(), std::move(w));
}

}