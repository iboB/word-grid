#pragma once

namespace server
{

class ExecutorBase;

class ExecutionContext
{
public:
    // signal that the executor needs to be updated
    virtual void wakeUp(ExecutorBase& e) = 0;

    // called by an executor when it determines that it wants to be stopped
    virtual void stop(ExecutorBase& e) = 0;
protected:
    // intentionally not virtual
    ~ExecutionContext() = default;
};

}
