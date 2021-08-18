#pragma once
#include "API.h"

#include <itlib/memory_view.hpp>

#include <memory>
#include <functional>

namespace server {

class SessionState;

class SERVER_API Session : public std::enable_shared_from_this<Session>
{
    class State;
public:
    void transitionToState(State* state);

protected:
    Session();
    // intentionally not virtual. Objects are not owned through this, but instead through shared pointers
    ~Session();

    void onReceive(itlib::memory_view<char> text);

    virtual void send() = 0;
    virtual void pushIOThreadTask(std::function<void()> task) = 0;

private:
    State* m_state;
};

}
