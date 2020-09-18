#ifndef __TASK_H__
#define __TASK_H__

class Task
{
protected:
    unsigned int mTimeCost;
    unsigned int mTimePeriod;

public:
    Task(unsigned int timeCost_in, unsigned int timePeriod_in);

    unsigned int getTimeCost();
    unsigned int getTimePeriod();

    virtual void execute() = 0;

};

#endif // __TASK_H__
