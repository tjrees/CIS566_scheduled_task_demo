// main.cpp
// Runs sample program to test scheduler
#include "scheduler.h"
#include "simpleTask.h"

int main()
{
    Scheduler scheduler;

    SimpleTask workOut(2, 24, "Going to the gym");
    SimpleTask eatFood(1, 6, "Eating a meal");
    SimpleTask takeNap(4, 12, "Taking a nap");

    scheduler.addTask(&workOut);
    scheduler.addTask(&eatFood);
    scheduler.addTask(&takeNap);

    scheduler.runTasks(1);

    return 0;
}