#include "Game.hpp"
#include "BoardProducer.hpp"
#include "Player.hpp"

#include <core/Board.hpp>

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
    m_playerDatas[player];

    if (!m_currentBoard)
    {
        m_currentBoard = std::make_unique<core::Board>(m_boardProducer.getBoard(this));
    }

    // no point in sending the previous board if we're not in a rest
    core::Board* prevBoard = nullptr;
    if (m_currentRest)
    {
        prevBoard = m_previousBoard.get();
    }

    player->sendRound(*m_currentBoard, m_currentRest, prevBoard);
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

    auto f = m_playerDatas.find(player);
    if (f == m_playerDatas.end())
    {
        player->sendFatalError("Player is not in this game");
        return;
    }

    auto& data = f->second;
    for (auto& sw : data.scores)
    {
        if (sw->word == word)
        {
            player->sendPlayWordResponse(Player::PlayWordResponse::AlreadyPlayed, word, 0);
            return;
        }
    }

    auto sw = m_currentBoard->dictionary().getWord(word);
    if (!sw)
    {
        player->sendPlayWordResponse(Player::PlayWordResponse::NoSuchWord, word, 0);
        return;
    }

    data.totalScore += sw->score;
    data.scores.push_back(sw);
    player->sendPlayWordResponse(Player::PlayWordResponse::Accept, word, sw->score);
}

}