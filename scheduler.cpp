#include <cmath>
#include <iostream>

#include "scheduler.h"
#include "task.h"

bool Scheduler::addTask(Task * taskToAdd)
{
    size_t numTotalTasks = mTasks.size() + 1U;
    double utilization = static_cast<double>(numTotalTasks) * 
        (std::pow(2.0, (1.0 / static_cast<double>(numTotalTasks))) - 1.0);

    double load = 0;
    for (size_t i = 0U; i < mTasks.size(); i++)
    {
        load += static_cast<double>(mTasks[i]->getTimeCost()) / 
            static_cast<double>(mTasks[i]->getTimePeriod());
    }
    load += static_cast<double>(taskToAdd->getTimeCost()) / 
        static_cast<double>(taskToAdd->getTimePeriod());
    
    std::cout << "Adding task will result in load of " << load * 100.0 << 
        "% and utilization of " << utilization * 100.0 << "%. ";

    if (load <= utilization)
    {
        std::cout << " Added task to schedule.\n";
        mTasks.push_back(taskToAdd);
        return true;
    }
    else
    {
        std::cout << " Did not add task to schedule.\n";
        return false;
    }
}

void Scheduler::clearTasks()
{
    mTasks.clear();
}

// TODO: Do better than just running tasks in series.
void Scheduler::runTasks(unsigned int cycles)
{
    for (unsigned int cycleNum = 0; cycleNum < cycles; cycleNum++)
    {
        for (size_t i = 0; i < mTasks.size(); i++)
        {
            std::cout << "Scheduler executing task " << i << "\n";
            mTasks[i]->execute();
        }
    }
}
