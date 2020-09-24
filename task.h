#ifndef __TASK_H__
#define __TASK_H__

class Task
{
private:
    static unsigned int taskCounter;

    unsigned int mProgress;
    unsigned int mRuns;

protected:
    unsigned int mTimeCost;
    unsigned int mTimePeriod;

    unsigned int mTaskId;

    void trackProgress(size_t timeStamp);

public:
    Task(unsigned int timeCost_in, unsigned int timePeriod_in);

    unsigned int getTimeCost() const;
    unsigned int getTimePeriod() const;

    virtual void execute(size_t startTime, size_t endTime) = 0;

};

#endif // __TASK_H__
