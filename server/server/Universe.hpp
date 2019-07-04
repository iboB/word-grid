#pragma once

#include <memory>
#include <vector>

namespace server
{
class Game;

class Universe
{
public:
    Universe();
    ~Universe();

    void addGame(std::unique_ptr<Game>&& game);

private:
    std::vector<std::unique_ptr<Game>> m_games;
};

}