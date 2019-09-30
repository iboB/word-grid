
#include "TaskExecutor.hpp"

#include <cassert>

namespace server {

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

}
