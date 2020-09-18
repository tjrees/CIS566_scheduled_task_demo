#ifndef __SIMPLE_TASK_H__
#define __SIMPLE_TASK_H__
#include "task.h"

class SimpleTask : public Task
{
private:

public:
    SimpleTask(unsigned int timeCost_in, unsigned int timePeriod_in);
    virtual void execute();

};

#endif // __SIMPLE_TASK_H__