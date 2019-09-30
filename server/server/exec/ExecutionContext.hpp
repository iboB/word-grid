// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
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
