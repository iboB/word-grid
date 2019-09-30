// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "PlayerPtr.hpp"
#include <unordered_set>

namespace server
{
using player_set = std::unordered_set<PlayerPtr>;
}
