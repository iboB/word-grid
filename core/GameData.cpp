#include "GameData.hpp"

namespace core
{
GameData::GameData() = default;
GameData::GameData(const std::string& id) : id(id) {}
GameData::~GameData() = default;
}