// This a program which prints the times taken by processes
// when they are scheduled based on their priority

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int done_k = 0;
int num_idle = 0;

// represents the processes
struct processes
{
    char name[5];

    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int priority;

    bool executed;
};
struct processes *process[20], temp, *highestPriority;

// This structure is used to represent
// processes that have completed execution
struct done_process
{
    char name[5];
    int starting_time;
    int completion_time;
};
struct done_process *done[20];

// sorts all the process based on it's arrival time
void sortByArrivalTime(int num_process)
{

    for (int i = 0; i < num_process; i++)
    {

        for (int j = 0; j < num_process - i - 1; j++)
        {

            if (process[j]->arrival_time > process[j + 1]->arrival_time)
            {

                temp = *process[j];
                *process[j] = *process[j + 1];
                *process[j + 1] = temp;
            }
        }
    }
}

// prints the average waiting and turnaround time
// made it as a function to keep main function readable
void averageTimes(int num_process)
{

    int avgWT = 0, avgTT = 0;

    for (int i = 0; i < num_process; i++)
    {

        avgWT += process[i]->waiting_time;
    }

    for (int i = 0; i < num_process; i++)
    {

        avgTT += process[i]->turnaround_time;
    }

    printf("\nAverage Waiting Time: %f\nAverage Turnaround Time:%f\n", ((float)avgWT / num_process), ((float)avgTT / num_process));
}

// prints information about all the processes in a table
void processTable(int num_process)
{

    for (int i = 0; i < 105; i++)
        printf("-");

    printf("\n");
    printf("| Name | Arrival Time | Burst Time | Waiting Time | Turn Around Time | Starting Time | Completion Time |\n");
    for (int i = 0; i < 105; i++)
        printf("-");
    printf("\n");

    // int j = 0;

    for (int i = 0, j = 0; i < num_process + num_idle; i++)
    {

        if (strcmp(done[i]->name, "idle") != 0)
        {

            printf("|   %s         %d             %d              %d              %d                %d                 %d        |\n", process[j]->name, process[j]->arrival_time, process[j]->burst_time, process[j]->waiting_time, process[j]->turnaround_time, done[i]->starting_time, done[i]->completion_time);
            j += 1;
        }
    }
    for (int i = 0; i < 105; i++)
        printf("-");
}

// prints the gantt chart of all the processes
void ganttChart(int num_process)
{

    printf("\nThe Gantt Chart of the process is as follows:\n");

    for (int i = 0; i < (16 * done_k) + 1; i++)
        printf("-");

    printf("\n");

    for (int i = 0; i < done_k; i++)
    {

        printf("|\t%s\t", done[i]->name);
    }

    printf("|");

    printf("\n");

    for (int i = 0; i < (16 * done_k) + 1; i++)
        printf("-");

    printf("\n0");

    for (int i = 0; i < done_k; i++)
        printf(" \t \t%d", done[i]->completion_time);
}

// returns the process of highest priority
struct processes *get_process(int i, int num_process)
{

    highestPriority = NULL;

    for (int j = 0; j < num_process; j++)
    {

        if (process[j]->arrival_time <= i && process[j]->executed == false)
        {

            highestPriority = process[j];

            for (int k = 0; k < num_process; k++)
            {

                if (process[j]->arrival_time == process[k]->arrival_time && process[k]->executed == false)
                {

                    if (process[k]->priority > process[j]->priority)
                        highestPriority = process[k];
                }
            }
        }
    }

    return highestPriority;
}

int main()
{

    bool idle = false;

    printf("Enter the no. of processes:");
    int num_process;
    scanf("%d", &num_process);

    for (int i = 0; i < num_process; i++)
    {

        process[i] = (struct processes *)malloc(sizeof(struct processes));

        printf("\nEnter the name of the process:");
        scanf("%s", process[i]->name);

        printf("Enter the arrival time:");
        scanf("%d", &process[i]->arrival_time);

        printf("Enter the burst time:");
        scanf("%d", &process[i]->burst_time);

        printf("Enter the priority:");
        scanf("%d", &process[i]->priority);

        process[i]->executed = false;
    }

    sortByArrivalTime(num_process);

    for (int i = 0, j = 0; j < num_process + num_idle;)
    {

        struct processes *p = get_process(i, num_process);

        if (p != NULL)
        {

            if (idle == true)
            {

                done[done_k]->completion_time = i;

                idle = false;

                done_k += 1;
            }

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            p->executed = true;

            strcpy(done[done_k]->name, p->name);
            done[done_k]->starting_time = i;
            done[done_k]->completion_time = i + p->burst_time;

            p->waiting_time = i - p->arrival_time;
            p->turnaround_time = p->waiting_time + p->burst_time;

            i = done[done_k]->completion_time;

            done_k += 1;

            j += 1;
        }
        else if (idle == false)
        {

            idle = true;

            num_idle += 1;

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            strcpy(done[done_k]->name, "idle");
            done[done_k]->starting_time = i;

            i += 1;

            j += 1;
        }
        else
        {
            i += 1;
        }
    }

    processTable(num_process);

    ganttChart(num_process);
    printf("\n");

    averageTimes(num_process);

    return 0;
}