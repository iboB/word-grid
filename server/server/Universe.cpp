#include "Universe.hpp"

#include "Game.hpp"

namespace server
{

Universe::Universe() = default;
Universe::~Universe() = default;

void Universe::addGame(std::unique_ptr<Game>&& game) {
    m_games.emplace_back(std::move(game));
}

}
