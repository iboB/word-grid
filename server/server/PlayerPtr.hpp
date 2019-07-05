#pragma once

#include <memory>

namespace server
{
class Player;
using PlayerPtr = std::shared_ptr<Player>;
using ConstPlayerPtr = std::shared_ptr<const Player>;
}