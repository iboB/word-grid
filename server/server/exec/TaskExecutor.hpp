// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "ExecutorBase.hpp"
#include <memory>
#include <mutex>
#include <vector>

namespace server
{

class TaskExecutorBase : public ExecutorBase
{
public:
    virtual void update() override;

    // tasks
    // tasks are pushed from various threads
    // tasks are executed on update
    class TaskBase
    {
    public:
        virtual ~TaskBase() = default;
        virtual void execute(TaskExecutorBase& e) = 0;
    };
    using TaskBasePtr = std::unique_ptr<TaskBase>;

    // task locking
    // you need to lock the tasks with these functions or a locker before adding tasks
    void lockTasks();
    void unlockTasks();

    // only valid on any thread when tasks are locked
    void pushTask(TaskBasePtr task);
private:
    bool m_tasksLocked = false;  // a silly defence but should work most of the time
    std::mutex m_tasksMutex;
    std::vector<TaskBasePtr> m_taskQueue;
};

// a strong-typed class so one doesn't accidentally push tasks from one type to another executor
template <typename Child>
class TaskExecutor : public TaskExecutorBase
{
public:
    class Task : public TaskExecutorBase::TaskBase
    {
        virtual void execute(TaskExecutorBase& e) final override
        {
            auto& c = static_cast<Child&>(e);
            execute(c);
        }
        virtual void execute(Child& c) = 0;
    };
    using TaskPtr = std::unique_ptr<Task>;

    class TaskLocker {
    public:
        TaskLocker(TaskExecutor& e)
            : m_executor(&e)
        {
            e->lockTasks();
        }
        TaskLocker(const TaskLocker&) = delete;
        TaskLocker& operator=(const TaskLocker&) = delete;
        TaskLocker(TaskLocker&& other) noexcept
            : m_executor(other.m_executor)
        {
            other.m_executor = nullptr;
        }
        TaskLocker& operator=(TaskLocker&& other) noexcept = delete;
        ~TaskLocker()
        {
            if (m_executor) m_executor->unlockTasks();
        }
        void pushTask(TaskPtr task)
        {
            return pushTask(std::move(task));
        }
    private:
        TaskExecutor* m_executor;
    };
    TaskLocker taskLocker() { return TaskLocker(*this); }

    // intentionally hiding functions from parent
    void pushTask(TaskPtr task)
    {
        return TaskExecutorBase::pushTask(std::move(task));
    }
};

}