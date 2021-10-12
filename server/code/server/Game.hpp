// word-grid
// Copyright (c) 2019-2021 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "API.h"

#include <memory>

namespace server
{

// a game has 4 states (as in state machine state), called phases, so as not to be confused with data-oriented state
// Idle - when there are no players. The game does nothing
// Rest - initiates board generation, waits for moves from previous round
// PreGame - calculates result previous round result. Collects generated board and sends it to players along with result from previous round
// InGame - when the game is actually played
class Game
{
public:

private:
    class Phase;
    Phase* m_curPhase = nullptr;

    class PhaseIdle;
    class PhaseRest;
    class PhasePreGame;
    class PhaseInGame;
};

}
