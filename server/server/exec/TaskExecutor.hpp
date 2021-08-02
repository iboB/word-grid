// word-grid
// Copyright (c) 2019 Borislav Stanimirov
//
// Distributed under the MIT Software License
// See accompanying file LICENSE.txt or copy at
// https://opensource.org/licenses/MIT
//
#pragma once

#include "ExecutorBase.hpp"

#include <itlib/ufunction.hpp>

#include <mutex>
#include <vector>
#include <queue>

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
    using Task = itlib::ufunction<void()>;
    using task_id = uint64_t;

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
        task_id pushTask(Task task)
        {
            return m_executor->pushTaskL(std::move(task));
        }
        task_id scheduleTask(std::chrono::milliseconds timeFromNow, Task task)
        {
            return m_executor->scheduleTaskL(timeFromNow, std::move(task));
        }
    private:
        TaskExecutor* m_executor;
    };
    TaskLocker taskLocker() { return TaskLocker(this); }

    task_id pushTask(Task task)
    {
        return taskLocker().pushTask(std::move(task));
    }

    // task locking
    // you need to lock the tasks with these functions or a locker before adding tasks
    void lockTasks();
    void unlockTasks();

    // only valid on any thread when tasks are locked
    task_id pushTaskL(Task task);
    task_id scheduleTaskL(std::chrono::milliseconds timeFromNow, Task task);

    // will cancel the task successfully and return true if the task queue containing
    // the task hasn't started executing.
    // returns whether the task was removed from the pending tasks
    // WARNING if this returns false one of three things might be true:
    // * The task was never added (bad id)
    // * The task is currently executing
    // * The task has finished executing
    bool cancelTask(task_id id);
private:
    bool m_tasksLocked = false;  // a silly defence but should work most of the time
    bool m_finishTasksOnExit = false;
    std::mutex m_tasksMutex;

    struct TaskWithId
    {
        Task task;
        task_id id;
    };
    std::vector<TaskWithId> m_taskQueue;

    struct TimedTaskWithId
    {
        Task task;
        task_id id;
        std::chrono::steady_clock::time_point time;
        struct Later
        {
            bool operator()(const TimedTaskWithId& a, const TimedTaskWithId& b)
            {
                return a.time > b.time;
            }
        };
    };

    // adapt more so we can erase tasks
    struct TimedTaskQueue
        : public std::priority_queue<TimedTaskWithId, std::vector<TimedTaskWithId>, TimedTaskWithId::Later>
    {
        bool tryEraseId(task_id id);
        TimedTaskWithId topAndPop();
    };
    TimedTaskQueue m_timedTasks;
};

}
