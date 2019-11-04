// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Game.hpp"
#include "BoardProducer.hpp"
#include "Board.hpp"
#include "Player.hpp"

namespace server
{

Game::Game(const std::string& id, core::duration restTime, BoardProducer& boardProducer)
    : m_id(id)
    , m_restTime(restTime)
    , m_boardProducer(boardProducer)
{}

Game::~Game() = default;

void Game::playerJoin(const PlayerPtr& player)
{
    m_players.insert(player);

    if (!m_currentBoard)
    {
        newBoard();
    }
    else
    {
        // no point in sending the previous board if we're not in a rest
        Board* prevBoard = nullptr;
        if (m_currentRest)
        {
            prevBoard = m_previousBoard.get();
        }

        player->sendRound(*m_currentBoard, m_currentRest, prevBoard);
    }
}

void Game::playerMove(const PlayerPtr& player, core::Word&& word)
{
    if (!m_currentBoard)
    {
        player->sendFatalError("There is no current round");
        return;
    }

    if (m_currentRest)
    {
        player->sendPlayWordResponse(Player::PlayWordResponse::Error, word, 0);
        return;
    }

    m_currentBoard->playerMove(player, std::move(word));
}

void Game::playerLeave(const PlayerPtr& player)
{
    m_players.erase(player);
}

void Game::tick(core::duration d)
{
    if (m_currentRest)
    {
        m_currentRest -= d;

        if (m_currentRest <= 0)
        {
            m_currentBoard->tick(-m_currentRest);
            m_currentRest = 0;
        }

        return;
    }

    m_currentBoard->tick(d);

    if (m_currentBoard->expired())
    {
        m_currentRest = m_restTime;
        newBoard();
    }
}

void Game::newBoard()
{
    m_previousBoard.reset(m_currentBoard.release());
    m_currentBoard.reset(new Board(m_boardProducer.getBoard(this)));

    for (auto& player : m_players)
    {
        player->sendRound(*m_currentBoard, m_currentRest, m_previousBoard.get());
    }
}

}