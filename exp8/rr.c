#include <stdio.h>
#include <stdlib.h>

// Represent a process
struct pcb
{
    // Process Attributes
    int i, a, b, br, s, p, c, t, w;
}; 
struct pcb *p;

// Represent element of ready queue
struct qnode
{
    struct pcb *node;
    struct qnode *link;
};
struct qnode *front = NULL, *rear = NULL;

// Represent a Gantt entry
struct gantt
{
    int id; // PID
    int time; // Start time
};
struct gantt *g;
int gmax = -1;

int algo, tot, tq = 0, flag = 0;

// Add entry to Gantt Chart
// Setting id to -1 if IDLE/END
void addGantt(int id, int time)
{
    gmax++;
    g[gmax].id = id;
    g[gmax].time = time;
}

// Draw horizontal line
// Just print
// Tab = 8 spaces
void hLine(int tab)
{
    int i;
    printf("\n");
    for (i = 0; i <= tab * 8; i++)
        printf("-");
}

// Performs final tabulation
// Common for all algorithms
void tabulate()
{
    float tt = 0, wt = 0;
    int i, j, flag = 0;

    // Gantt Chart
    printf("\nGantt Chart\n");
    hLine(gmax);
    printf("\n|");
    for (i = 0; i < gmax; i++)
    {
        if (flag == 1 && g[i].id == -1)
            continue;
        else if (g[i].id == -1)
        {
            flag = 1;
            printf("--\t|");
        }
        else
        {
            flag = 0;
            printf("P%d\t|", g[i].id + 1);
        }
    }
    hLine(gmax);
    printf("\n");
    for (i = 0; i <= gmax; i++)
    {
        if (flag == 1 && g[i].id == -1)
            continue;
        if (g[i].id == -1)
            flag = 1;
        else
            flag = 0;
        printf("[%d]\t", g[i].time);
    }
    printf("\n\t ");

    // Calculating final TT, WT
    for (i = 0; i < tot; i++)
    {
        p[i].t = p[i].c - p[i].a;
        p[i].w = p[i].t - p[i].b;
        tt += p[i].t;
        wt += p[i].w;
    }

    // Tabular data
    printf("\n\nFINAL TABULATION (TIME QUANTUM = %d)", tq);
    hLine(14);
    printf("\n|\tID\t|\tAT\t|\tBT\t|\tPR\t|\tCT\t|\tTT\t|\tWT\t|");
    hLine(14);
    for (i = 0; i < tot; i++)
    {
        struct pcb t = p[i];
        printf("\n|\tP%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|", t.i + 1, t.a, t.b, t.p, t.c, t.t, t.w);
    }
    hLine(14);
    printf("\n\t\t\t\t\t\t\t\t\t\t|\t%d\t|\t%d\t|", (int)tt, (int)wt);
    hLine(14);

    // Average TT, WT
    printf("\n\nAverage TT = %f ms", tt / tot);
    printf("\nAverage WT = %f ms\n", wt / tot);
    printf("\n\n");
}

// 0 if incomplete
// 1 if complete
int complete()
{
    int i;
    for (i = 0; i < tot; i++)
        if (p[i].br != 0)
            return 0;
    flag = 1;
    return 1;
}

// Enqueue to ready queue
void push(struct pcb *item)
{
    struct qnode *p = malloc(sizeof(struct qnode));
    p->node = item;
    p->link = NULL;
    if (front == NULL)
    {
        front = p;
        rear = p;
    }
    else
    {
        rear->link = p;
        rear = p;
    }
}

// Dequeue from ready queue
struct pcb *pop()
{
    if (front == NULL)
        return NULL;
    struct qnode *temp = front;
    struct pcb *item = front->node;
    if (front == rear)
    {
        front = NULL;
        rear = NULL;
    }
    else
    {
        front = front->link;
    }
    free(temp);
    return item;
}

void rr()
{
    int pulse, i, tqq = tq;
    struct pcb *current = NULL;
    for (pulse = 0; complete() == 0; pulse++)
    {
        for (i = 0; i < tot; i++)
            if (p[i].a == pulse)
                push(&p[i]);

        if (current != NULL)
        {
            current->br -= 1;
            tqq--;
            if (current->br == 0)
            {
                current->c = pulse;
                current = NULL;
            }
        }
        if (tqq == 0 && current != NULL)
        {
            tqq = tq;
            push(current);
            current = NULL;
        }
        if (current == NULL)
        {
            current = pop();
            tqq = tq;
            if (current == NULL)
            {
                addGantt(-1, pulse);
                continue;
            }
            else
            {
                addGantt(current->i, pulse);
                current->s = pulse;
            }
        }
    }
}

int input()
{
    int i;
    printf("\nInput Data (Space Separated):");
    printf("NO: ");
    scanf("%d", &tot);
    if (tot < 1)
    {
        printf("\n~ Invalid Number of Processes.\n");
        return -1;
    }

    p = malloc(sizeof(struct pcb) * tot);

    // maximum of 100 Gantt entries only.
    g = malloc(sizeof(struct gantt) * 100);

    printf("AT: ");
    for (i = 0; i < tot; i++)
    {
        scanf("%d", &p[i].a);
        if (p[i].a < 0)
        {
            printf("\n~ Invalid Arrival Time(s).\n");
            return -1;
        }
        // default PID.
        // not asking user for pid
        p[i].i = i;
        p[i].p = 0;
    }

    printf("BT: ");
    for (i = 0; i < tot; i++)
    {
        scanf("%d", &p[i].b);
        if (p[i].b < 1)
        {
            printf("\n~ Invalid Burst Time(s).\n");
            return -1;
        }
        p[i].br = p[i].b;
    }
    
    printf("TQ: ");
	  scanf("%d", &tq);
	  if (tq < 1)
	  {
		   printf("\n~ Invalid Time Slice.\n");
		   return -1;
	  }
    return 0;
}

void main()
{
    if (input() != -1)
    {
      rr();
      tabulate();
    }
    free(p);
    free(g);
    return;
}
