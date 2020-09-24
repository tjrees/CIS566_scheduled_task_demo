// simpleTask.cpp
#include <iostream>
#include <unistd.h>

#include "simpleTask.h"

SimpleTask::SimpleTask(unsigned int timeCost_in, unsigned int timePeriod_in, std::string blurb_in)
: Task(timeCost_in, timePeriod_in), mBlurb(blurb_in) {}

void SimpleTask::execute(size_t startTime, size_t endTime)
{
    std::cout << "Task started: " << mBlurb << " from timestamp " << startTime << " to " << endTime << "\n";
    for(size_t i = startTime; i < endTime; i++)
    {
        this->trackProgress(i);
        sleep(1);
    }
    std::cout << "Returning to scheduler\n";
}
