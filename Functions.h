#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct record{
    char taskID[4];
    char taskName[200];
    char category[50];
    char status[20];
    char completedIncomplete[15];
    int dueDay;
    int dueMonth;
    int dueYear;  
}rec,check;

struct taskDays{
    char today[100];
    char due[100];
}viewdate;

int main();
void taskStatus(int dueDay, int dueMonth, int dueYear, char *status);
void sortTaskDate();
void viewDoneTasks();
void viewIncompleteTasks();
void addNewTask();
void updateTasks();
void deleteTasks();
void viewAllTasks();

#endif