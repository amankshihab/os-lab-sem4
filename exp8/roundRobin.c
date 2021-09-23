#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int front = 0;

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

    if (process[front]->arrival_time <= i)
    {

        return process[front++];
    }

    return NULL;
}

int main()
{

    bool idle = false;

    int done_k = 0;

    printf("\nEnter the no. of processes:");
    int num_process;
    scanf("%d", &num_process);

    printf("\nEnter the time quantum:");
    int time_quantum;
    scanf("%d", &time_quantum);

    for (int i = 0; i < num_process; i++)
    {

        process[i] = (struct processes *)malloc(sizeof(struct processes));

        printf("\nEnter the name of process:");
        scanf("%s", process[i]->name);

        printf("\nEnter the arrival time:");
        scanf("%d", &process[i]->arrival_time);

        printf("\nEnter the burst time:");
        scanf("%d", &process[i]->burst_time);

        process[i]->rem_burst_time = process[i]->burst_time;
        process[i]->executed = false;
    }

    sortByArrivalTime(num_process);

    int i = 0;

    while (front != num_process - 1)
    {

        struct processes *p_get = get_process(i);

        if (p_get != NULL)
        {

            enqueueReady(p_get);
        }

        struct processes *p_dq = dequeueReady();

        if (p_dq != NULL)
        {
            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            strcpy(done[done_k]->name, p_dq->name);
            done[done_k]->starting_time = i;

            if (p_dq->rem_burst_time <= time_quantum)
            {

                done[done_k]->completion_time = i + p_dq->rem_burst_time;
                p_dq->rem_burst_time = 0;
                p_dq->executed = true;

                // calculate remaining times of p_dq
            }
            else
            {

                done[done_k]->completion_time = p_dq->rem_burst_time - time_quantum;
                p_dq->rem_burst_time -= time_quantum;
            }

            done_k += 1;
        }
        else if (idle == false)
        {

            done[done_k] = (struct done_process *)malloc(sizeof(struct done_process));

            strcpy(done[done_k]->name, "idle");

            done[done_k]->starting_time = i;
        }
        else
        {
            i += 1;
        }
    }

    return 0;
}