#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int front = 0;

int num_idle = 0;

int frontQueue = -1, rearQueue = -1;

int num_process = 0;

int done_k = 0;

struct processes
{

    char name[5];

    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int rem_burst_time;

    bool executed;
};
struct processes *process[20], temp, *queue[20];

void enqueueReady(struct processes *p)
{

    if (frontQueue == -1 && rearQueue == -1)
    {

        frontQueue = 0;
        rearQueue = 0;
    }
    else
    {
        rearQueue = (rearQueue + 1) % num_process;
    }

    queue[rearQueue] = p;
}

struct processes *dequeueReady()
{

    if (frontQueue == -1 && rearQueue == -1)
    {
        return NULL;
    }
    else
    {
        int temp = frontQueue;

        frontQueue = (frontQueue + 1) % num_process;

        return queue[temp];
    }
}

struct done_process
{

    char name[5];

    int starting_time;
    int completion_time;
};
struct done_process *done[20];

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

struct processes *get_process(int i)
{

    if (front < num_process)
    {    if (process[front]->arrival_time <= i)
        {

            return process[front++];
        }
    }

    return NULL;
}

bool executed() {

    for (int i = 0; i < num_process; i++) {
        if (process[i] -> executed == false)
            return true;
    }

    return false;
}

void processTable()
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

void ganttChart()
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


int main()
{

    bool idle = false;

    printf("\nEnter the time quantum:");
    int time_quantum;
    scanf("%d", &time_quantum);

    printf("\nEnter the no. of processes:");
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

        process[i] -> rem_burst_time = process[i] -> burst_time;
    }

    int i = 0;

    for (i = 0;;i++)
    {
        struct processes *p_get = get_process(i);

        if (p_get != NULL) {
            enqueueReady(p_get);
            break;
        }
    }
    while (executed())
    {


        struct processes *p_dq = dequeueReady();

        // struct processes *p_get = get_process(i);

        // if (p_get != NULL)
        // {
        //     enqueueReady(p_get);
        // }

        if (p_dq != NULL)
        {

            if (idle) {

                done[done_k] -> completion_time = i;

                idle = false;

                done_k += 1;
            }

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            done[done_k]->starting_time = i;

            strcpy(done[done_k] -> name, p_dq -> name);

            if (p_dq->rem_burst_time <= time_quantum)
            {
                done[done_k]->completion_time = i + p_dq->rem_burst_time;

                p_dq->executed = true;
            }
            else
            {
                done[done_k] -> completion_time = i + time_quantum;

                p_dq -> rem_burst_time -= time_quantum;

                enqueueReady(p_dq);
            }

            i = done[done_k]->completion_time;

            done_k += 1;

            printf("Hey");
        }
        else if (idle == false)
        {
            done[done_k] = (struct done_process*)malloc(sizeof(struct done_process));

            strcpy(done[done_k] -> name, "idle");

            done[done_k] -> starting_time = i;

            num_idle += 1;

            printf("Hey1");
        }
        else
        {
            i += 1;
            printf("Hey1");

        }

        struct processes *p_get = get_process(i);

        if (p_get != NULL)
        {
            enqueueReady(p_get);
        }

    }

    processTable();

    ganttChart();

    return 0;
}