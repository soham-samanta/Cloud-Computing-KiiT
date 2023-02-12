#include <stdio.h>
#include <limits.h>

struct process
{
    int pid, at, bt, ct, tat, wt, rt, bt_remaining, start;
};

int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    else
        return a;
}

int main()
{
    int length, max_com = INT_MIN, min_at = INT_MAX, idle = 0, n, completed = 0, index, current = 0, first = 0, prev = 0;
    float awt = 0, atat = 0, art = 0, cpu, throughput;
    printf("Enter number of process: \n");
    scanf("%d", &n);
    struct process p[n];
    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Arrival Time: ", i);
        scanf("%d", &p[i].at);
        p[i].pid = i;
    }

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter Process %d Burst Time: ", i);
        scanf("%d", &p[i].bt);
        p[i].bt_remaining = p[i].bt;
    }

    int is_completed[n];
    for (int i = 0; i < n; i++)
    {
        is_completed[i] = 0;
    }
    while (completed != n)
    {
        int index = -1;//becomes -1 when there is a gap in time
        int minimum = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= current && is_completed[i] == 0)
            {
                if (minimum > p[i].bt_remaining)
                {
                    minimum = p[i].bt_remaining;
                    index = i;
                }
                if (minimum == p[i].bt_remaining) // in case 2 BTS are same we order them in FCFS
                {
                    if (p[index].at > p[i].at)
                    {
                        minimum = p[i].bt_remaining;
                        index = i;
                    }
                }
            }
        }

        if (index == -1)
        {
            current++;
        }
        else
        {
            if (p[index].bt_remaining == p[index].bt)
            {
                p[index].start = current;
                if (first == 0)
                {
                    first = 1;
                }
                else
                {
                    idle = idle + (p[index].start - prev); // cpu utilization
                }
            }
            p[index].bt_remaining -= 1;
            current += 1;
            prev = current;
            if (p[index].bt_remaining == 0)
            {
                p[index].ct = current;
                p[index].tat = p[index].ct - p[index].at;
                p[index].wt = p[index].tat - p[index].bt;
                p[index].rt = p[index].start - p[index].at;
                awt = awt + p[index].wt;
                atat = atat + p[index].tat;
                art = art + p[index].rt;
                completed++;
                is_completed[index] = 1;
            }
        }
    }
    awt = awt / n;
    atat = atat / n;
    art = art / n;
    for (int i = 0; i < n; i++)
    {
        max_com = max(max_com, p[i].ct);
        min_at = min(min_at, p[i].at);
    }
    length = max_com - min_at;
    throughput = (float)(length / n);
    cpu = (float)(length - idle) / length * 100;

    printf("Pid\tArrival time\tBurst time\tcompletion time\tTurnaround time\tWaiting time\tResponse time\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("average waiting time = %f\n", awt);
    printf("average turnaround time = %f\n", atat);
    printf("average response time = %f\n", art);
    printf("Throughput = %f\n", throughput);
    printf("CPU utilization(in percentage) = %f\n", cpu);

    return 0;
}