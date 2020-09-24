#ifndef __SIMPLE_TASK_H__
#define __SIMPLE_TASK_H__
#include <string>

#include "task.h"

class SimpleTask : public Task
{
private:
    std::string mBlurb;

public:
    SimpleTask(unsigned int timeCost_in, unsigned int timePeriod_in, std::string blurb_in);
    virtual void execute(size_t startTime, size_t endTime);

};

#endif // __SIMPLE_TASK_H__