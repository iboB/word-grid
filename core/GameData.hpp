#pragma once

#include <string>

namespace core
{
class GameData
{
public:
    GameData();
    GameData(const std::string& id);
    ~GameData();
    std::string id;
    size_t numPlayers = 0;
};
}