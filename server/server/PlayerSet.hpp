#pragma once

#include "PlayerPtr.hpp"
#include <unordered_set>

namespace server
{
using player_set = std::unordered_set<PlayerPtr>;
}
