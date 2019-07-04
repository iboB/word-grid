#include "Game.hpp"

namespace server
{

Game::Game(const std::string& name, core::Dictionary&& dictionary)
    : m_name(name)
    , m_dictionary(std::move(dictionary))
{}

Game::~Game() = default;

}