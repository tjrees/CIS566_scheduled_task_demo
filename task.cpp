#include <stdexcept>
#include <iostream>

#include "task.h"

unsigned int Task::taskCounter = 0;

Task::Task(unsigned int timeCost_in, unsigned int timePeriod_in)
: mProgress(0), mRuns(0), mTimeCost(timeCost_in), mTimePeriod(timePeriod_in)
{
    mTaskId = taskCounter;
    taskCounter++;
}

unsigned int Task::getTimeCost() const
{
    return mTimeCost;
}
unsigned int Task::getTimePeriod() const
{
    return mTimePeriod;
}

// Private member functions
void Task::trackProgress(size_t timeStamp)
{
    // Checks to make sure the task has been executed the proper number of times
    if (mRuns < (timeStamp / mTimePeriod))
    {
        throw std::runtime_error("Task did not finish in its time period.");
    }
    mProgress++;
    std::cout << "Task with id " << mTaskId << " has progress " << mProgress << "\n";
    if (mProgress >= mTimeCost)
    {
        mRuns++;
        mProgress = 0;
        std::cout << "Task with id " << mTaskId << " has completed " << mRuns << " runs\n";
    }
}
