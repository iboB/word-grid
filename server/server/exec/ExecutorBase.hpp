#pragma once

namespace server
{

class ExecutionContext;

class ExecutorBase
{
protected:
    ExecutorBase();
public:
    virtual ~ExecutorBase();

    virtual void update() = 0;

    // returns the previously set execution context
    ExecutionContext* setExecutionContext(ExecutionContext* context);

    ExecutionContext* executionContext() const { return m_executionContext; }

    void wakeUp();
    void stop();
private:
    ExecutionContext* m_executionContext;
};

}