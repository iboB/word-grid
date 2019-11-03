// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "TaskExecutor.hpp"

#include <cassert>

namespace server
{

void TaskExecutorBase::update()
{
    m_tasksMutex.lock();
    auto tasks = std::move(m_taskQueue);
    m_tasksMutex.unlock();

    for (auto& task : tasks)
    {
        task->execute(*this);
    }
}

void TaskExecutorBase::lockTasks()
{
    m_tasksMutex.lock();
    m_tasksLocked = true;
}

void TaskExecutorBase::unlockTasks()
{
    m_tasksLocked = false;
    m_tasksMutex.unlock();
    wakeUp(); // assuming something has changed
}

void TaskExecutorBase::pushTask(TaskBasePtr task)
{
    assert(m_tasksLocked);
    m_taskQueue.emplace_back(std::move(task));
}

void TaskExecutorBase::finalize()
{
    if (!m_finishTasksOnExit) return; // abandon unfinished tasks

    // loop multiple times as the execution of some tasks can spawn yet more tasks
    while (true)
    {
        m_tasksMutex.lock();
        auto tasks = std::move(m_taskQueue);
        m_tasksMutex.unlock();

        if (tasks.empty()) break;

        for (auto& task : tasks)
        {
            task->execute(*this);
        }
    }
}

}
