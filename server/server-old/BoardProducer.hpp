// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

namespace server
{
class Board;
class Game;

class BoardProducer
{
public:
    virtual ~BoardProducer() {}

    virtual void addGame(Game& game) = 0;
    virtual Board getBoard(const Game* game) = 0;
};

}