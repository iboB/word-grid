// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include <chrono>

namespace server
{

class ExecutionContext;

class ExecutorBase
{
public:
    ExecutorBase();
    ExecutorBase(ExecutionContext& context);
    virtual ~ExecutorBase();

    virtual void update() = 0;

    // optionally called before destruction to finalize all remaining execution
    virtual void finalize() {}

    // returns the previously set execution context
    ExecutionContext& setExecutionContext(ExecutionContext& context);

    ExecutionContext& executionContext() const { return *m_executionContext; }

    void wakeUpNow();
    void scheduleNextWakeUp(std::chrono::milliseconds timeFromNow);
    void unscheduleNextWakeUp();
    void stop();
private:
    ExecutionContext* m_executionContext;
};

}
