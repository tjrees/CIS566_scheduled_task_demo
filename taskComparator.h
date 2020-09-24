#ifndef __TASK_COMPARATOR_H__
#define __TASK_COMPARATOR_H__
#include "task.h"

struct TaskComparator
{
    // Greater-than operator
    // Used with std::priority_queue, it will become a min queue.
    bool operator () (const Task * lhs, const Task * rhs)
    {
        return lhs->getTimePeriod() > rhs->getTimePeriod();
    }
};

#endif // __TASK_COMPARATOR_H__
