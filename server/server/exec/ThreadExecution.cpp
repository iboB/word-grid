// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "ThreadExecution.hpp"
#include "ExecutorBase.hpp"

#include <cassert>
#include <functional>

namespace server
{
namespace detail
{

ThreadExecutionContext::ThreadExecutionContext()
    : m_running(true)
    , m_hasWork(true)
{}

void ThreadExecutionContext::stop(ExecutorBase&)
{
    m_running = false;
    wakeUp();
}

void ThreadExecutionContext::wakeUp()
{
    std::lock_guard<std::mutex> lk(m_workMutex);
    m_hasWork = true;
    m_workCV.notify_one();
}

void ThreadExecutionContext::wakeUp(ExecutorBase&)
{
    wakeUp();
}

void ThreadExecutionContext::wait()
{
    std::unique_lock<std::mutex> lock(m_workMutex);
    m_workCV.wait(lock, [this](){ return m_hasWork; });
    m_hasWork = false;
    lock.unlock();
}

} // namespace detail

ThreadExecution::ThreadExecution(ExecutorBase& e)
    : m_executor(e)
{
    m_oldExecitionContext = m_executor.setExecutionContext(&m_execution);
}

ThreadExecution::~ThreadExecution()
{
    stopAndJoinThread();
    m_executor.setExecutionContext(m_oldExecitionContext);
}

void ThreadExecution::launchThread()
{
    assert(!m_thread.joinable()); // we have an active thread???
    m_thread = std::thread(std::bind(&ThreadExecution::thread, this));
}

void ThreadExecution::stopAndJoinThread()
{
    if (m_thread.joinable())
    {
        m_executor.stop();
        m_thread.join();
    }
}

void ThreadExecution::thread()
{
    while(m_execution.running())
    {
        m_execution.wait();
        m_executor.update();
    }
}

}