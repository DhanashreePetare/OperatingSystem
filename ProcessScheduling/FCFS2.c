#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

struct process{
    int id,at,bt,ct,tat,wt,st;
};

void fcfs(struct process p[],int n){
    for(int i=0;i<n;i++){
        if(i==0) p[i].st=p[i].at;
        else{
            if(p[i-1].ct<=p[i].at) p[i].st=p[i].at;
            else if(p[i-1].ct>p[i].at) p[i].st=p[i-1].ct;
        }
        p[i].ct=p[i].st+p[i].bt;
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
    }
}

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
        printf(" P%d |", P[i].id);
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



int main(){
    printf("enter number of processes: ");
    int n;
    scanf("%d",&n);
    
    struct process p[n];
    printf("enter id,at,bt of all processes: ");
    for(int i=0;i<n;i++){
        scanf("%d %d %d",&p[i].id,&p[i].at,&p[i].bt);
    }
    fcfs(p,n);
    printf("pid\tat\tbt\tct\tst\ttat\twt\n");
    int totalwt=0,totaltat=0,totalbt=0;
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].id,p[i].at,p[i].bt,p[i].ct,p[i].st,p[i].tat,p[i].wt);
        totalwt+=p[i].wt;
        totaltat+=p[i].tat;
        totalbt+=p[i].bt;
    }

    drawGanttChart(p,n);

    float avgwt=(float)totalwt/n;
    float avgtat=(float)totaltat/n;
    float throughput=n/(float)totalbt;
    printf("avg waiting time = %.2f\n",avgwt);
    printf("avg tat time = %.2f\n",avgtat);
    printf("throughput = %.2f\n",throughput);

}



