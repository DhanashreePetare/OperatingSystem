#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct process{
    int pid,at,bt,ct,starttime,tat,wt;
};

void drawGanttChart(struct process P[], int n)
{
    printf("\nGantt Chart:\n");
    printf(" ");
    for (int i = 0; i < n; i++)
    {
        printf("--------");
    }
    printf("\n|");
    for (int i = 0; i < n; i++)
    {
        printf(" P%d |", P[i].pid);
    }
    printf("\n ");
    for (int i = 0; i < n; i++)
    {
        printf("--------");
    }
    printf("\n");
    printf("0");
    for (int i = 0; i < n; i++)
    {
        printf("   %d", P[i].ct);
    }
    printf("\n");
}

void fcfs(struct process P[],int n){
    for(int i=0;i<n;i++){
        if(i==0){
            P[i].starttime=P[i].at;
        }
        else{
            if(P[i-1].ct<P[i].at) P[i].starttime=P[i].at;
            else P[i].starttime=P[i-1].ct;
        }

        P[i].ct=P[i].starttime+P[i].bt;
        P[i].tat=P[i].ct-P[i].at;
        P[i].wt=P[i].tat-P[i].bt;
    }
}

int main(){
 int n;
 printf("enter number of processes: ");
 scanf("%d",&n);
 struct process P[n];
 printf("enter process info for each process (pid,at,bt): \n");

 for(int i=0;i<n;i++){
    printf("process %d: \n",i+1);
    scanf("%d %d %d", &P[i].pid,&P[i].at,&P[i].bt);
 }

    fcfs(P,n);

    printf("\nComplete process Information:\n");
    printf("Pid\tArival Time\tBurst Time\tCompletion Time\tTurnAround Time\tWaiting Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\n",P[i].pid,P[i].at,P[i].bt,P[i].ct,P[i].tat,P[i].wt);
    }
 drawGanttChart(P,n);
 return 0;
}

/*
first come first server..just loop through processes and check 3 conditions 
i=0, st=at;
i!=0, compare ct of previous and at of this process and assign accordingly and finally compute other things.
*/