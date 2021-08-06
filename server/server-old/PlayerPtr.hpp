// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <memory>

namespace server
{
class Player;
using PlayerPtr = std::shared_ptr<Player>;
using ConstPlayerPtr = std::shared_ptr<const Player>;
}