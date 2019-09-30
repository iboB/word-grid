// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
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