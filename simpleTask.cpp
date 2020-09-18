// simpleTask.cpp
#include <iostream>
#include <unistd.h>

#include "simpleTask.h"

SimpleTask::SimpleTask(unsigned int timeCost_in, unsigned int timePeriod_in)
: Task(timeCost_in, timePeriod_in) {}

void SimpleTask::execute()
{
    std::cout << "Simple task starting\n";
    for (unsigned int i = 0; i < mTimeCost - 1; i++)
    {
        std::cout << "Simple task executing " << i << "\n";
        sleep(1);
    }
    std::cout << "Simple task ending\n";
}
