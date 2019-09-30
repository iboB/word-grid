// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

namespace core
{
class Board;
}

namespace server
{
class Game;

class BoardProducer
{
public:
    virtual ~BoardProducer() {}

    virtual void addGame(Game& game) = 0;
    virtual core::Board getBoard(const Game* game) = 0;
};

}