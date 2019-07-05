#pragma once

#include "PlayerPtr.hpp"

#include <string>
#include <vector>

namespace core
{
class GameData;
}

namespace server
{

class Universe;
class Game;

class Player : public std::enable_shared_from_this<Player>
{
public:
    Player();
    virtual ~Player();

    void setUniverse(Universe& u);

    const std::string& id() const { return m_id; }

    // protocol
    void onSetId(std::string&& id);
    void onChooseGame(std::string&& id);

    virtual void sendDatas(const std::vector<core::GameData>& datas) = 0;
    virtual void sendErrorBadId(std::string&& id) = 0;
    virtual void sendAcceptId(std::string&& id) = 0;

    virtual void sendFatalError(std::string&& message) = 0;

private:
    friend class Universe;
    Universe* m_universe = nullptr;

    std::string m_id;

    Game* m_game = nullptr;
};

}
