#include <stdexcept>

#include "task.h"

Task::Task(unsigned int timeCost_in, unsigned int timePeriod_in)
: mTimeCost(timeCost_in), mTimePeriod(timePeriod_in)
{}

unsigned int Task::getTimeCost()
{
    return mTimeCost;
}
unsigned int Task::getTimePeriod()
{
    return mTimePeriod;
}