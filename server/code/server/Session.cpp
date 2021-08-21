#include "Session.hpp"

namespace server
{

class Session::Mode
{
protected:
    ~Mode() = default;
public:
    virtual void onReceive(Session* s, itlib::memory_view<char> text) = 0;
};

namespace
{
//void TransitionSessionTo_InitialMode();
}

class Session::InitialMode final : public Session::Mode
{
public:
    virtual void onReceive(Session* s, itlib::memory_view<char> text) override
    {

    }
};

void Session::changeMode(Mode* mode)
{
    pushIOThreadTask([this, mode]() {
        m_mode = mode;
    });
}

void Session::onReceive(itlib::memory_view<char> text)
{

}

}
