// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "ExecutorBase.hpp"

#include <acme/ufunction.hpp>

#include <memory>
#include <mutex>
#include <vector>

namespace server
{

class TaskExecutor : public ExecutorBase
{
public:
    virtual void update() override;
    virtual void finalize() override;

    void setFinishTasksOnExit(bool b) { m_finishTasksOnExit = b; }

    // tasks
    // tasks are pushed from various threads
    // tasks are executed on update
    using Task = acme::ufunction<void()>;

    class TaskLocker
    {
    public:
        explicit TaskLocker(TaskExecutor* e) : m_executor(e)
        {
            e->lockTasks();
        }
        TaskLocker(const TaskLocker&) = delete;
        TaskLocker& operator=(const TaskLocker&) = delete;
        TaskLocker(TaskLocker&& other) noexcept : m_executor(other.m_executor)
        {
            other.m_executor = nullptr;
        }
        TaskLocker& operator=(TaskLocker&& other) noexcept = delete;
        ~TaskLocker()
        {
            if (m_executor) m_executor->unlockTasks();
        }
        uint64_t pushTask(Task task)
        {
            return m_executor->pushTaskL(std::move(task));
        }
    private:
        TaskExecutor* m_executor;
    };
    TaskLocker taskLocker() { return TaskLocker(this); }

    uint64_t pushTask(Task task)
    {
        return taskLocker().pushTask(std::move(task));
    }

    // task locking
    // you need to lock the tasks with these functions or a locker before adding tasks
    void lockTasks();
    void unlockTasks();

    // only valid on any thread when tasks are locked
    uint64_t pushTaskL(Task task);

    // will cancel the task successfully and return true if the task queue containing
    // the task hasn't started executing.
    // returns whether the task was removed from the pending tasks
    // WARNING if this returns false one of three things might be true:
    // * The task was never added (bad id)
    // * The task is currently executing
    // * The task has finished executing
    bool cancelTask(uint64_t id);
private:
    bool m_tasksLocked = false;  // a silly defence but should work most of the time
    bool m_finishTasksOnExit = false;
    std::mutex m_tasksMutex;

    struct TaskWithId
    {
        Task task;
        uint64_t id;
    };
    std::vector<TaskWithId> m_taskQueue;
};

}
