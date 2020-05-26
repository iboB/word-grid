// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#include "TaskExecutor.hpp"

#include <cassert>
#include <atomic>

namespace server
{

namespace
{
std::atomic_uint64_t currentTaskId = {};
uint64_t getNextTaskId()
{
    return currentTaskId.fetch_add(1, std::memory_order_relaxed);
}
}

void TaskExecutor::update()
{
    m_tasksMutex.lock();
    std::vector<TaskWithId> tasks;
    tasks.swap(m_taskQueue);
    m_tasksMutex.unlock();

    for (auto& task : tasks)
    {
        task.task();
    }
}

void TaskExecutor::lockTasks()
{
    m_tasksMutex.lock();
    m_tasksLocked = true;
}

void TaskExecutor::unlockTasks()
{
    m_tasksLocked = false;
    m_tasksMutex.unlock();
    wakeUp(); // assuming something has changed
}

uint64_t TaskExecutor::pushTaskL(Task task)
{
    assert(m_tasksLocked);
    auto& newTask = m_taskQueue.emplace_back();
    newTask.task = std::move(task);
    newTask.id = getNextTaskId();
    return newTask.id;
}

bool TaskExecutor::cancelTask(uint64_t id)
{
    std::lock_guard<std::mutex> l(m_tasksMutex);

    for (auto taskIter = m_taskQueue.cbegin(); taskIter != m_taskQueue.cend(); ++taskIter)
    {
        if (taskIter->id == id)
        {
            m_taskQueue.erase(taskIter);
            return true;
        }
    }

    return false;
}

void TaskExecutor::finalize()
{
    if (m_finishTasksOnExit)
    {
        // since tasks can add other tasks, we need to loop mulitple times until we're done
        while (true)
        {
            m_tasksMutex.lock();
            std::vector<TaskWithId> tasks;
            tasks.swap(m_taskQueue);
            m_tasksMutex.unlock();

            if (tasks.empty()) break;

            for (auto& task : tasks)
            {
                task.task();
            }
        }
    }
}

}
