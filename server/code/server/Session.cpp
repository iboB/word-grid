#include "Session.hpp"

namespace server
{

class Session::Mode
{
protected:
    ~Mode() = default;
public:
    virtual void onReceive(Session* s, itlib::span<char> text) = 0;
};

namespace
{
//void TransitionSessionTo_InitialMode();
}

class Session::InitialMode final : public Session::Mode
{
public:
    virtual void onReceive(Session* s, itlib::span<char> text) override
    {

    }
};

void Session::changeMode(Mode* mode)
{
    pushIOThreadTask([this, mode]() {
        m_mode = mode;
    });
}

void Session::onReceive(itlib::span<char> text)
{

}

}
