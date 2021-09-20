#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// available is the total amount of resources available
// reamianing available is the amt of resources available after initial allocation
int available[10], remaining_available[10];

struct processes
{

    char name[5];

    int allocation[10]; // initial allocation
    int max_need[10]; // max amount of resources needed
    int remaining_need[10]; // remaining amt of resources needed

    bool executed;
};
struct processes *process[10];

bool isDeadlock(int num_process, int num_resources, int remaining_available[]) {

    bool flag = false;

    int num = 0;

    for (int i = 0; i < num_process; i++) {

        if (process[i] -> executed == false) {

            for (int j = 0; j < num_resources; j++) {

                if (process[i] -> remaining_need[j] > remaining_available[j]) {
                    num += 1;
                    break;
                }
            }
        }
    }

    if (num == num_process)
        return true;
    return false;
}

int main()
{

    int num_executed = 0;

    printf("\nEnter the no. of resources:");
    int num_resources;
    scanf("%d", &num_resources);

    int total_allocated[10];

    for (int i = 0; i < num_resources; i++) {
        total_allocated[i] = 0;
    }

    printf("\n");

    for (int i = 0; i < num_resources; i++)
    {

        printf("Enter the availability of resource %d:", i);
        scanf("%d", &available[i]);
    }

    printf("\nEnter the no. of processes:");
    int num_process;
    scanf("%d", &num_process);

    for (int i = 0; i < num_process; i++)
    {

        process[i] = (struct processes *)malloc(sizeof(struct processes));

        printf("\nEnter the name of the process:");
        scanf("%s", process[i]->name);

        for (int j = 0; j < num_resources; j++)
        {

            printf("Enter amount of resource %d allocated to %s:", j, process[i]->name);
            scanf("%d", &process[i]->allocation[j]);

            printf("Enter the max. amount of resource %d required for %s:", j, process[i]->name);
            scanf("%d", &process[i]->max_need[j]);

            process[i]->remaining_need[j] = process[i]->max_need[j] - process[i]->allocation[j];

            total_allocated[j] += process[i]->allocation[j];

            printf("\n");
        }

        process[i] -> executed = false;
    }

    for (int i = 0; i < num_resources; i++)
    {
        remaining_available[i] = available[i] - total_allocated[i];
    }

    int iter_variable = 0;

    bool execute_flag = true;

    printf("\nSafe sequence:\n");

    while (num_executed < num_process)
    {

        if (isDeadlock(num_process, num_resources, remaining_available)){
            
            printf("\nDEADLOCKED!");
            break;
        }    

        if (process[iter_variable] -> executed != true) {

            for (int k = 0; k < num_resources; k++) {

                if (process[iter_variable] -> remaining_need[k] > remaining_available[k]) {
                    execute_flag = false;
                    break;
                }
            }

            if (execute_flag) {

                printf("%s ", process[iter_variable] -> name);

                for (int k = 0; k < num_resources; k++) {

                    remaining_available[k] += process[iter_variable] -> allocation[k];
                    process[iter_variable] -> executed = true;
                }

                num_executed += 1;
            }
        }

        iter_variable = (iter_variable+1)%num_process;

        execute_flag = true;
    }

    return 0;
}