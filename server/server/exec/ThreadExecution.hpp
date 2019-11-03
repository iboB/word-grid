// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "ExecutionContext.hpp"

#include <mutex>
#include <atomic>
#include <condition_variable>
#include <thread>

namespace server
{
namespace internal
{

class ThreadExecutionContext final : public ExecutionContext
{
public:
    ThreadExecutionContext();

    // run status
    // both funcs are safe to call from any thread
    bool running() const { return m_running; }
    virtual void stop(ExecutorBase& e) override;

    // wakes up from waiting
    // safe to call from any thread
    // safe to call no matter if the executable is waiting or not
    void wakeUp();
    virtual void wakeUp(ExecutorBase& e) override;

    // call at the beginning of each frame
    // will block until woken up
    void wait();

private:
    std::atomic_bool m_running = false;

    // wait state
    bool m_hasWork = false;
    std::condition_variable m_workCV;
    std::mutex m_workMutex;
};

} // namespace internal

class ThreadExecution
{
public:
    // call the following on the main thread
    ThreadExecution(ExecutorBase& e);
    ~ThreadExecution();

    void launchThread();
    void stopAndJoinThread();

    std::thread::id threadId() const { return m_thread.get_id(); }
private:
    ExecutorBase& m_executor;
    internal::ThreadExecutionContext m_execution;
    ExecutionContext* m_oldExecitionContext;
    std::thread m_thread;

    // NOT MAIN THREAD
    void thread();
};

}
