// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "Board.hpp"
#include "Player.hpp"

namespace server
{

Board::Board(core::Grid&& grid, core::ScoredDictionary&& dictionary, core::duration dur)
    : m_grid(std::move(grid))
    , m_dictionary(std::move(dictionary))
    , m_remainingTime(dur)
{}

Board::~Board() = default;

// stupid msvc 2017 can't auto define this as noexcept...
Board::Board(Board&& other) noexcept
    : m_grid(std::move(other.m_grid))
    , m_dictionary(std::move(other.m_dictionary))
    , m_remainingTime(other.m_remainingTime)
    , m_playerDatas(std::move(other.m_playerDatas))
{}

Board& Board::operator=(Board&&) noexcept = default;

void Board::playerMove(const PlayerPtr& player, core::Word&& word)
{
    auto& data = m_playerDatas[player];
    for (auto& sw : data.scores)
    {
        if (sw->word == word)
        {
            player->sendPlayWordResponse(Player::PlayWordResponse::AlreadyPlayed, word, 0);
            return;
        }
    }

    auto sw = m_dictionary.getWord(word);
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