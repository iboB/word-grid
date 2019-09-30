// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "GameData.hpp"

namespace core
{
GameData::GameData() = default;
GameData::GameData(const std::string& id) : id(id) {}
GameData::~GameData() = default;
}