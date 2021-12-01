#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

int done_k = 0;

int front = 0;

int num_idle = 0;

struct processes
{
    char name[5];

    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int rem_bt;

    bool executed;
    bool in_q;
};
struct processes *process[20], temp, *queue[20];

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

void processTable(int num_process)
{

    printf("\n");

    for (int j = 0; j < 43; j++)
        printf("-");

    printf("\n| Process  |  Arrival Time  |  Burst Time |\n");

    for (int j = 0; j < 43; j++)
        printf("-");

    printf("\n");

    for (int i = 0; i < num_process; i++)
    {
        printf("|  %s      |       %d        |      %d      |\n", process[i]->name, process[i]->arrival_time, process[i]->burst_time);
    }

    for (int j = 0; j < 43; j++)
        printf("-");
    printf("\n");
}

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

int q_front = -1, q_rear = -1;

void enqueue(struct processes *pr, int num_process)
{
    if (q_front != ((q_rear + 1) % num_process))
    {
        if (q_front == -1 && q_rear == -1)
        {
            q_front = 0;
            q_rear = 0;
            queue[q_rear] = pr;
        }
        else
        {
            q_rear = ((q_rear + 1) % num_process);
            queue[q_rear] = pr;
        }
    }
}

struct processes *dequeue(int num_process)
{

    if (q_front == -1 && q_rear == -1)
    {
        return NULL;
    }
    else
    {
        struct processes *item = queue[q_front];
        if (q_front == q_rear)
        {
            q_front = -1;
            q_rear = -1;
        }
        else
        {
            q_front = ((q_front + 1) % num_process);
        }

        return item;
    }
}

struct processes *get_process(int i, int num_process)
{
    struct processes *to_return = dequeue(num_process);

    if (to_return != NULL)
    {
        return to_return;
    }

    return NULL;
}

bool all_executed(int num_process)
{
    for (int i = 0; i < num_process; i++)
    {
        if (!process[i]->executed)
            return false;
    }

    return true;
}

int main()
{

    bool idle = false;

    printf("Enter the no. of processes:");
    int num_process;
    scanf("%d", &num_process);

    int tq;
    printf("\nEnter the time quantum:");
    scanf("%d", &tq);

    for (int i = 0; i < num_process; i++)
    {

        process[i] = (struct processes *)malloc(sizeof(struct processes));

        printf("\nEnter the name of the process:");
        scanf("%s", process[i]->name);

        printf("Enter the arrival time:");
        scanf("%d", &process[i]->arrival_time);

        printf("Enter the burst time:");
        scanf("%d", &process[i]->burst_time);

        process[i]->rem_bt = process[i]->burst_time;
        process[i]->in_q = false;
    }

    processTable(num_process);

    sortByArrivalTime(num_process);

    int i = 0, n = 0;

    struct processes *current = NULL;

    while (!all_executed(num_process))
    {

        for (int g = 0; g < num_process; g++)
        {
            if (process[g]->arrival_time <= i && !process[g]->in_q)
            {
                enqueue(process[g], num_process);
                process[g]->in_q = true;
            }
        }

        if (current != NULL)
        {
            enqueue(current, num_process);
        }

        struct processes *p = get_process(i, num_process);

        current = p;

        if (p != NULL)
        {

            if (idle == true)
            {

                done[done_k]->completion_time = i;

                idle = false;

                done_k += 1;
            }

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            strcpy(done[done_k]->name, p->name);
            done[done_k]->starting_time = i;

            if (p->rem_bt <= tq)
            {
                done[done_k]->completion_time = i + p->rem_bt;
                p->rem_bt = 0;

                p->executed = true;

                n += 1;

                current = NULL;

                p->turnaround_time = done[done_k]->completion_time - p->arrival_time;
                p->waiting_time = p->turnaround_time - p->burst_time;
            }
            else
            {
                done[done_k]->completion_time = i + tq;

                p->rem_bt -= tq;
            }

            i = done[done_k]->completion_time;

            done_k += 1;

            front += 1;
        }
        else if (idle == false)
        {

            idle = true;

            num_idle += 1;

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            strcpy(done[done_k]->name, "idle");
            done[done_k]->starting_time = i;

            i += 1;
        }
        else
        {
            i += 1;
        }
    }

    ganttChart(num_process);
    printf("\n");

    averageTimes(num_process);

    return 0;
}
