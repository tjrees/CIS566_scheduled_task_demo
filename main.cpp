// main.cpp
// Runs sample program to test scheduler
#include "scheduler.h"
#include "simpleTask.h"

int main()
{
    Scheduler scheduler;

    SimpleTask A(3, 20);
    SimpleTask B(2, 5);
    SimpleTask C(2, 10);

    scheduler.addTask(&A);
    scheduler.addTask(&B);
    scheduler.addTask(&C);

    scheduler.runTasks(1);

    return 0;
}