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