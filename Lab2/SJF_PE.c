//SJF PRE-EMPTIVE

#include <stdio.h>
#include <stdlib.h>

struct node {
  int process;
  int burst_time, copy_bt;
  int arrival_time;
  int wait_time;
  int turn_around_time;
  int completion_time;
};

void insertNode(struct node **p, int i, int process, int burst_time, int arrival_time) {

  struct node *newNode = (struct node*)malloc(sizeof(struct node));

  newNode->process = process;
  newNode->burst_time = burst_time;
  newNode->copy_bt = burst_time;
  newNode->arrival_time = arrival_time;
  newNode->wait_time = 0;
  newNode->turn_around_time = 0;
  newNode->completion_time = 0;

  p[i]= newNode;
}

//Initial sorting by arrival time.
void sortList(struct node **p, int n)
{
  struct node *temp = (struct node*)malloc(sizeof(struct node));
  for (int i = 0; i < n; i++)
  {
    for(int j = i + 1; j < n; j++)
    {
      if (p[i]->arrival_time > p[j]->arrival_time)
      {
        temp = p[i];
        p[i] = p[j];
        p[j] = temp;
      }
    }
  }
}

void internalSort(struct node **p, int n)
{
  int total_burst_time = 0;
  int j = 0, k = 0;

  for (int i = 0; i < n; i++)
  {
    total_burst_time += p[i]->burst_time;
  }

  for (int i = 0; i < total_burst_time+ 1; i++)
  {
    if (p[j]->copy_bt - 1 > 0 && i >=1)
    {
      p[j]->copy_bt -= 1;
    }
    else if(p[j]->copy_bt - 1 == 0  && i >=1)
    {
      p[j]->copy_bt = 0;
      p[j]->completion_time = i;
      int min_bt = 10000;
      for(int val = 0; val < n; val++)
      {
        if (p[val]->arrival_time <= i && p[val]->copy_bt < min_bt && p[val]->copy_bt != 0)
        {
          j = val;
          min_bt = p[val]->copy_bt;
        }
      }
    }
    if (i == p[k]->arrival_time)
    {
      int min_bt = 10000;
      for(int val = 0; val < n; val++)
      {
        if (p[val]->arrival_time <= i && p[val]->copy_bt < min_bt && p[val]->copy_bt != 0)
        {
          j = val;
          min_bt = p[val]->copy_bt;
        }
      }
      if (k < n -1)
      {
        k++;
      }
    }
  }
}

double waitTime(struct node **p, int n)
{
  double wt_sum = 0;
  for (int i = 0; i < n; i++)
  {
    p[i]->wait_time = (p[i]->completion_time - p[i]->arrival_time - p[i]->burst_time);
    wt_sum += p[i]->wait_time;
  }
  return wt_sum;
}

double turnAroundtime(struct node **p, int n)
{
  double tat_sum = 0;
  for (int i = 0; i < n; i++)
  {
    p[i]->turn_around_time = (p[i]->wait_time + p[i]->burst_time);
    tat_sum += p[i]->turn_around_time;
  }
  return tat_sum;
}


void display(struct node **p, int n)
{
  printf(" ----------------------------------------------------------------------------\n");
  printf(" |Process |BurstTime |ArrivalTime |WaitTime |TurnAroundTime |CompletionTime |\n");
  printf(" ----------------------------------------------------------------------------\n");
  for(int i = 0; i < n; i++)
  {
    printf(" |%-7d |%-9d |%-11d |%-8d |%-14d |%-14d |\n", p[i]->process, p[i]->burst_time, p[i]->arrival_time, p[i]->wait_time,  p[i]->turn_around_time, p[i]->completion_time);
  }
  printf(" ----------------------------------------------------------------------------\n");
}


int main()
{
  int n, process, burst_time, arrival_time;
  float avg_nd_calc;
  printf("Enter number nodes to be entered: ");
  scanf("%d", &n);

  struct node **p = (struct node **)malloc(n*sizeof(struct node));

  for (int i = 0; i < n; i++)
  {
    printf("\nEnter node number - %d: ", i + 1);
    scanf("%d %d %d", &process, &burst_time, &arrival_time);
    insertNode(p, i, process, burst_time, arrival_time);
  }

  sortList(p, n);
  internalSort(p, n);
  double wt_val = waitTime(p, n);
  double tat_val = turnAroundtime(p , n);
  display(p, n);
  printf("Average Wait Time is: %f\n", wt_val/n);
  printf("Average Turn Around Time is: %f\n", tat_val/n);

}
