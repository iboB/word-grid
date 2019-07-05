#include "Game.hpp"
#include "Round.hpp"

namespace server
{

Game::Game(const std::string& id, core::Dictionary&& dictionary)
    : m_id(id)
    , m_dictionary(std::move(dictionary))
{}

Game::~Game() = default;

void Game::playerJoin(const PlayerPtr& player)
{
    m_players.insert(player);
}

void Game::playerLeave(const PlayerPtr& player)
{
    m_players.erase(player);
}

}