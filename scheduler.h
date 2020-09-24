#ifndef __SCHEDULER_H__
#define __SCHEDULER_H__
#include <vector>

class Task;

class Scheduler
{
private:
    std::vector<Task *> mTasks;
    std::vector<Task *> mSchedule;

    void printSchedule() const;
    void createSchedule();

public:
    bool addTask(Task * taskToAdd);
    void clearTasks();

    void runTasks(unsigned int cycles);
};

#endif // __SCHEDULER_H__
