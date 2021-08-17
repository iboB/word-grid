#include "Session.hpp"

namespace server
{

class Session::State
{
protected:
    ~State() = default

    virtual void onReceive(Session* s, itlib::memory_view<char> text) = 0;
};

namespace
{

void TransitionSessionTo_InitialState();

class InitialState final : public Session::State
{
public:
    virtual void onReceive(Session* s, itlib::memory_view<char> text) override
    {

    }
};

}

void Session::transitionToState(State* state)
{
    pushIOThreadTask([state]() {
        m_state = state;
    });
}

void Session::onReceive(itlib::memory_view<char> text)
{

}

}
