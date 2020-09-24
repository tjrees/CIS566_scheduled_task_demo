#include <cmath>
#include <iostream>
#include <queue>
#include <unistd.h>

#include "scheduler.h"
#include "task.h"
#include "taskComparator.h"

// HELPER FUNCTIONS //

// Recursive helper to find greatest common denominator
static int gcd(int a, int b)
{
    if (b == 0)
    {
        return a;
    }
    if (a == 0)
    {
        return b;
    }
    if (a == b)
    {
        return a;
    }
    return gcd(b, a % b);
}

// Helper to find least common multiple, calls gcd
static int lcm(int a, int b)
{
    return (a * b) / gcd(a, b);
}

// PUBLIC MEMBER FUNCTIONS //
bool Scheduler::addTask(Task * taskToAdd)
{
    size_t numTotalTasks = mTasks.size() + 1;
    double utilization = static_cast<double>(numTotalTasks) * 
        (std::pow(2.0, (1.0 / static_cast<double>(numTotalTasks))) - 1.0);

    double load = 0;
    for (size_t i = 0; i < mTasks.size(); i++)
    {
        if (mTasks[i] == taskToAdd)
        {
            throw std::runtime_error("Cannot schedule the same task twice");
        }
        load += static_cast<double>(mTasks[i]->getTimeCost()) / 
            static_cast<double>(mTasks[i]->getTimePeriod());
    }
    load += static_cast<double>(taskToAdd->getTimeCost()) / 
        static_cast<double>(taskToAdd->getTimePeriod());
    
    std::cout << "Adding task will result in load of " << load * 100.0 << 
        "% and utilization of " << utilization * 100.0 << "%. ";

    if (load <= utilization)
    {
        std::cout << " Added task to list.\n";
        mTasks.push_back(taskToAdd);
        return true;
    }
    else
    {
        std::cout << " Did not add task to list.\n";
        return false;
    }
}

void Scheduler::clearTasks()
{
    mTasks.clear();
}

void Scheduler::runTasks(unsigned int cycles)
{
    // No need to do anything if there are no tasks
    if (mTasks.empty())
    {
        return;
    }
    // First, schedule tasks.
    createSchedule();

    for (unsigned int cycleNum = 0; cycleNum < cycles; cycleNum++)
    {
        size_t timeOffset = mSchedule.size() * cycleNum;
        size_t timeStamp = 0;
        while (timeStamp < mSchedule.size())
        {
            Task * toRun = mSchedule[timeStamp];
            size_t startTime = timeStamp;
            if (toRun != nullptr)
            {
                while (timeStamp < mSchedule.size())
                {
                    if (mSchedule[timeStamp] != toRun)
                    {
                        break;
                    }
                    timeStamp++;
                }
                toRun->execute(startTime + timeOffset, timeStamp + timeOffset);
            }
            else
            {
                // Increment past any null time slices without running anything
                // For simulation, sleep for a second.
                timeStamp++;
                std::cout << "No task scheduled at timestamp " << timeStamp + timeOffset << " - sleeping\n";
                sleep(1);
            }
        }
    }
}

// PRIVATE MEMBER FUNCTIONS //

void Scheduler::printSchedule() const
{
    std::cout << "| ";
    for (size_t i = 0; i < mSchedule.size(); i++)
    {
        if (mSchedule[i] == nullptr)
        {
            std::cout << "NULL | ";
        }
        else
        {
            std::cout << static_cast<void*>(mSchedule[i]) << " | ";
        }
    }
    std::cout << "\n";
}

// Assumes there is at least one task to schedule
void Scheduler::createSchedule()
{
    int scheduleSize = mTasks[0]->getTimePeriod();
    // Find LCM of time period across all tasks
    for (size_t i = 1; i < mTasks.size(); i++)
    {
        scheduleSize = lcm(scheduleSize, mTasks[i]->getTimePeriod());
    }
    mSchedule.resize(scheduleSize, nullptr);

    std::priority_queue<Task *, std::vector<Task *>, TaskComparator> taskQueue;
    for (size_t i = 0; i < mTasks.size(); i++)
    {
        taskQueue.push(mTasks[i]);
    }

    while (!taskQueue.empty())
    {
        Task * toSchedule = taskQueue.top();
        std::cout << "Attempting to schedule task: " << static_cast<void*>(toSchedule) << "\n";

        // Since the schedule is of size LCM, we need to schedule each task exactly (LCM / timePeriod) times.
        for (int period = 0; period < (scheduleSize / toSchedule->getTimePeriod()); period++)
        {
            int slicesAllotted = 0;
            // Try to start scheduling at the very beginning of this task's time period.
            for (int slice = (toSchedule->getTimePeriod() * period); 
                 slice < (toSchedule->getTimePeriod() * (period + 1));
                 slice++)
            {
                if (mSchedule[slice] == nullptr)
                {
                    mSchedule[slice] = toSchedule;
                    slicesAllotted++;
                    if (slicesAllotted >= toSchedule->getTimeCost())
                    {
                        break;
                    }
                }
            }
            if (slicesAllotted < toSchedule->getTimeCost())
            {
                // The calculation done while adding tasks should ensure that this does not happen
                throw std::runtime_error("Could not schedule task - not enough time slices");
            }
        }
        // Pop and move to the next task, or finish.
        //printSchedule();
        taskQueue.pop();
    }
}
