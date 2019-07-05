#pragma once

#include "PlayerPtr.hpp"
#include "PlayerSet.hpp"

#include <core/Board.hpp>

namespace server
{

class Round
{
public:
private:
    core::Board m_board;
    player_set m_players;
};

}
