//SJF

#include<stdio.h>
#include<limits.h>

void sort(int bt[],int p[],int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=(i+1);j<n;j++)
        {
            if(bt[i]>bt[j])
            {
                int temp=bt[i];
                bt[i]=bt[j];
                bt[j]=temp;

                temp=p[i];
                p[i]=p[j];
                p[j]=temp;
            }
        }
    }
}

int main(){
    int n;
    printf("Enter the number of processes \n");
    scanf("%d",&n);
    int bt[n],wt[n],tat[n],p[n],temp[n];
    float awt=0,atat=0;
    temp[0]=0;
    printf("Enter burst time: \n");
    for(int i=0;i<n;i++)
    {
        p[i]=(i+1);
        scanf("%d",&bt[i]);
    }
    sort(bt,p,n);

    printf("Process\tBurst time\tWaiting time\tTurnaround time\n");
    for(int i=0;i<n;i++)
    {
        wt[i]=0,tat[i]=0;
        wt[i]=temp[i];
        temp[i+1]=temp[i]+bt[i];
        tat[i]=wt[i]+bt[i]; // formula
        awt=awt+wt[i];
        atat=atat+tat[i];
        printf("%d\t\t%d\t\t%d\t\t%d \n",p[i],bt[i],wt[i],tat[i]);
    }
    awt=awt/n;
    atat=atat/n;
    printf("Average waiting time = %f \n",awt);
    printf("Average turnaround time = %f \n",atat);
    return 0;
}