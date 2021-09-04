// this is an implementation of fcfs scheduling algorithm

#include <stdio.h>
#include <string.h>

struct process
{
    char process_name[10];
    int arrival_time;
    int burst_time;
    int waiting_time;
    int turnaround_time;
    int status;
} temp;

struct done_process
{
    char process_name[10];
    int starting_time;
    int completion_time;
};

int main()
{

    int idle;

    printf("\nEnter the no. of processes:");
    int num_process;
    scanf("%d", &num_process);

    struct process processess[num_process];
    struct done_process done[num_process];

    //reading all processes
    for (int i = 0; i < num_process; i++)
    {

        printf("\n\nEnter the name of the process:");
        scanf("%s", processess[i].process_name);

        printf("Enter the arrival time of %s: ", processess[i].process_name);
        scanf("%d", &processess[i].arrival_time);

        printf("Enter the burst time of %s: ", processess[i].process_name);
        scanf("%d", &processess[i].burst_time);

        processess[i].status = 0;
    }

    // sorting based on arrival time
    for (int i = 0; i < num_process; i++)
    {

        for (int j = 0; j < num_process - i - 1; j++)
        {

            if (processess[j].arrival_time > processess[j + 1].arrival_time)
            {

                temp = processess[j];
                processess[j] = processess[j + 1];
                processess[j + 1] = temp;
            }
        }
    }

    idle = 0;

    for (int i = 0, k = 0, num = 0; k < num_process;)
    {
        if (processess[k].arrival_time <= i && processess[k].status == 0)
        {

            if (idle == 1)
            {
                done[num].completion_time = i;
                num += 1;
            }

            strcpy(done[num].process_name, processess[k].process_name);

            done[num].starting_time = i;
            done[num].completion_time = i + processess[k].burst_time;

            processess[k].waiting_time = done[num].starting_time - processess[k].arrival_time;
            processess[k].turnaround_time = processess[k].waiting_time + processess[k].burst_time;

            i = done[num].completion_time;

            processess[k].status = 1;

            k += 1;
            num += 1;

            idle = 0;
        }
        else if (idle == 0)
        {

            strcpy(done[num].process_name, "idle");

            done[num].starting_time = i;

            i += 1;

            idle = 1;

            num_process += 1;
        }
        else
        {

            i += 1;
        }
    }

    printf("\nThe Gantt Chart of the process is as follows:\n");

    for (int i = 0; i < (16 * num_process) + 1; i++)
        printf("-");

    printf("\n");

    for (int i = 0; i < num_process; i++)
    {

        printf("|\t%s\t", done[i].process_name);
    }

    printf("|");

    printf("\n");

    for (int i = 0; i < (16 * num_process) + 1; i++)
        printf("-");

    printf("\n0");

    for (int i = 0; i < num_process; i++)
        printf(" \t \t%d", done[i].completion_time);

    return 0;
}