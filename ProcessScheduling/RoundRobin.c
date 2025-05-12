#include<stdio.h>

struct process{
    int id,at,bt,remtime,ct,tat,wt,rt;
};

void roundRobin(struct process p[],int np,int quantum){
    int time=0, completed=0;
    int all_done;

    while(completed<np){
        all_done=1;

        for(int i=0;i<np;i++){
            if(p[i].at<=time && p[i].remtime>0){
                all_done=0;

                if(p[i].rt==-1) p[i].rt=time-p[i].at;

                if(p[i].remtime>quantum){
                    time+=quantum;
                    p[i].remtime-=quantum;
                }
                else{
                    time+=p[i].remtime;
                    p[i].ct=time;
                    p[i].remtime=0;
                    completed++;
                }
                printf("Process %d executed till time %d\n",p[i].id,time);
            }
        }

        if(all_done) time++;
    }
    for(int i=0;i<np;i++){
        p[i].tat=p[i].ct-p[i].at;
        p[i].wt=p[i].tat-p[i].bt;
    }
}

void drawGanttChart(struct process p[],int np,int quantum){


}

int main(){
    int np, quantum;
    printf("enter number of processes: ");
    scanf("%d",&np);

    struct process p[np];

    printf("enter id,at,bt of all processes: ");
    for(int i=0;i<np;i++){
        scanf("%d %d %d",&p[i].id,&p[i].at,&p[i].bt);
        p[i].remtime=p[i].bt;
        p[i].rt=-1;
    }

    printf("enter time quantum: ");
    scanf("%d",&quantum);

    roundRobin(p,np,quantum);
    drawGanttChart(p,np,quantum);
    return 0;
}