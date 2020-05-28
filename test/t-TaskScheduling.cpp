#include <doctest/doctest.h>
#include <server/exec/TaskExecutor.hpp>
#include <server/exec/ThreadExecution.hpp>

#include <atomic>

TEST_SUITE_BEGIN("TaskScheduling");

class Executor : public server::TaskExecutor
{
public:
    Executor() : e(*this) {
        e.launchThread();
    }

    virtual void update() override
    {
        server::TaskExecutor::update();
        ++numUpdates;
    }

    int numUpdates = 0;
    server::ThreadExecution e;
};

struct TaskStatus
{
    int32_t t1 = 0;
    int32_t t2 = 0;
    std::atomic_int32_t t3 = 0;
};

struct Task
{
    Task(TaskStatus& s) : status(s) {}
    TaskStatus& status;
};

struct Task1 : public Task
{
    using Task::Task;
    void operator()()
    {
        ++status.t1;
    }
};

struct Task2 : public Task
{
    using Task::Task;
    void operator()()
    {
        ++status.t2;
    }
};

struct Task3 : public Task
{
    using Task::Task;
    void operator()()
    {
        ++status.t3;
    }
};

TEST_CASE("Too late")
{
    Executor exec;
    TaskStatus status;
    exec.setFinishTasksOnExit(true);
    {
        auto t = exec.taskLocker();
        t.pushTask(Task1(status));
        t.scheduleTask(std::chrono::milliseconds(1), Task2(status));
        t.scheduleTask(std::chrono::seconds(100), Task3(status));
    }
    exec.e.stopAndJoinThread();

    CHECK(status.t1 == 1);
    CHECK(status.t2 == 1);
    CHECK(status.t3 == 0);
}

TEST_CASE("Execute")
{
    Executor exec;
    TaskStatus status;
    exec.setFinishTasksOnExit(true);
    {
        auto t = exec.taskLocker();
        t.pushTask(Task1(status));
        t.scheduleTask(std::chrono::milliseconds(50), Task3(status));
        t.scheduleTask(std::chrono::milliseconds(40), [&status] {
            CHECK(status.t1 == 1);
            CHECK(status.t2 == 1);
            CHECK(status.t3 == 0);
            ++status.t2;
        });
        t.scheduleTask(std::chrono::milliseconds(30), Task2(status));
    }
    while(status.t3 == 0) std::this_thread::yield();
    exec.e.stopAndJoinThread();

    CHECK(status.t1 == 1);
    CHECK(status.t2 == 2);
    CHECK(status.t3 == 1);
}
