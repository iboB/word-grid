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
    m_universe->onNewPlayer(shared_from_this());
}

void Player::onSetId(std::string&& id)
{
    m_universe->playerSetId(shared_from_this(), std::move(id));
}

void Player::onChooseGame(std::string&& id)
{
    if (m_game)
    {
        m_game->playerLeave(shared_from_this());
    }
    m_game = m_universe->getGame(id);
    if (!m_game)
    {
        sendFatalError(std::string("No such game ") + id);
        return;
    }

    m_game->playerJoin(shared_from_this());
}

}