#include "Game.hpp"
#include "Round.hpp"
#include "BoardProducer.hpp"
#include "Player.hpp"

namespace server
{

Game::Game(const std::string& id, BoardProducer& boardProducer)
    : m_id(id)
    , m_boardProducer(boardProducer)
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

void Game::playerMove(const PlayerPtr& player, core::Word&& word)
{
    if (!m_currentRound)
    {
        player->sendFatalError("There is no current round");
    }
}

}