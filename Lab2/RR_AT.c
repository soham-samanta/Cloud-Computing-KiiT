//Round Robin

#include <stdio.h>
#include <stdlib.h>

struct node {
    int process;
    int burst_time;
    int arrival_time;
    int wait_time;
    int turn_around_time;
    int completion_time;
    int copy_bt;
};

void insertNode(struct node** p, int i, int process, int burst_time, int arrival_time) {

    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    newNode->process = process;
    newNode->burst_time = burst_time;
    newNode->copy_bt = burst_time;
    newNode->arrival_time = arrival_time;
    newNode->wait_time = 0;
    newNode->turn_around_time = 0;
    newNode->completion_time = 0;

    p[i] = newNode;
} 

int min(int b, int q)
{
    if (q >= b)
    {
        return b;
    }
    else
    {
        return q;
    }
}

void sortList(struct node** p, int n, int q)
{
    int flag = 0, i = 0, tbt = 0, r1 = 0, at = 0, min_val = 0;
    while (flag != n)
    {
        if (i == n)
        {
            i = 0;
        }
        min_val = min(p[i]->copy_bt, q);
        if (min_val == 0)
        {
            min_val = 10000;
        }
        if (p[i]->copy_bt - min_val >= 0 && p[i]->arrival_time <= tbt)
        {
            tbt += min_val;
            p[i]->copy_bt -= min_val;
            if (p[i]->copy_bt == 0)
            {
                p[i]->completion_time = tbt;
                flag++;
            }
        }
        else if (p[i]->arrival_time > tbt)
        {
            tbt += min_val;
        }
        i++;
    }
}

double waitTime(struct node** p, int n)
{
    double wt_sum = 0;
    for (int i = 0; i < n; i++)
    {
        p[i]->wait_time = (p[i]->completion_time - p[i]->arrival_time - p[i]->burst_time);
        wt_sum += p[i]->wait_time;
    }
    return wt_sum;
}

double turnAroundtime(struct node** p, int n)
{
    double tat_sum = 0;
    for (int i = 0; i < n; i++)
    {
        p[i]->turn_around_time = (p[i]->wait_time + p[i]->burst_time);
        tat_sum += p[i]->turn_around_time;
    }
    return tat_sum;
}


void display(struct node** p, int n)
{
    printf("---------------------------------------------------------------------------\n");
    printf("|Process |BurstTime |ArrivalTime |WaitTime |TurnAroundTime |CompletionTime|\n");
    printf("---------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++)
    {
        printf("|%-7d |%-9d |%-11d |%-8d |%-14d |%-14d|\n", p[i]->process, p[i]->burst_time, p[i]->arrival_time, p[i]->wait_time, p[i]->turn_around_time, p[i]->completion_time);
    }
    printf("---------------------------------------------------------------------------\n");
}


int main()
{
    int n, process, burst_time, q, arrival_time;
    printf("Enter number nodes to be entered: ");
    scanf("%d", &n);

    struct node** p = (struct node**)malloc(n * sizeof(struct node));

    for (int i = 0; i < n; i++)
    {
        printf("\nEnter node number - %d: ", i + 1);
        scanf("%d %d %d", &process, &burst_time, &arrival_time);
        insertNode(p, i, process, burst_time, arrival_time);
    }

    printf("\nEnter quantum: ");
    scanf("%d", &q);

    sortList(p, n, q);
    double wt_val = waitTime(p, n);
    double tat_val = turnAroundtime(p, n);
    display(p, n);
    printf("Average Wait Time is: %f\n", wt_val / n);
    printf("Average Turn Around Time is: %f\n", tat_val / n);

}
