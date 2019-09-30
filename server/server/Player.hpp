// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "PlayerPtr.hpp"

#include <core/Types.hpp>

#include <string>
#include <vector>

namespace core
{
class GameData;
class Board;
class Word;
}

namespace server
{
class Universe;
class Game;

class Player : public std::enable_shared_from_this<Player>
{
public:
    Player();
    virtual ~Player();

    void setUniverse(Universe& u);
    Universe* universe() const { return m_universe; }

    const std::string& id() const { return m_id; }

    // protocol
    void onSetId(std::string&& id);
    void onChooseGame(std::string&& id);
    void onPlayWord(core::Word&& w);

    virtual void sendDatas(const std::vector<core::GameData>& datas) = 0;
    virtual void sendErrorBadId(std::string&& id) = 0;
    virtual void sendAcceptId(std::string&& id) = 0;

    enum class PlayWordResponse
    {
        Accept, NoSuchWord, AlreadyPlayed, Error
    };
    virtual void sendPlayWordResponse(PlayWordResponse r, const core::Word& w, core::score_t score) = 0;

    // prev board can be null
    virtual void sendRound(const core::Board& curBoard, core::duration rest, const core::Board* prevBoard) = 0;

    //virtual void sendApproveWord()

    virtual void sendFatalError(std::string&& message) = 0;

private:
    friend class Universe;
    Universe* m_universe = nullptr;

    std::string m_id;

    Game* m_game = nullptr;
};

}
