//SJF- shortest job first
//      preemptive and non preemptive

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//------------------------------------------non-preemptive---------------------------------

struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int st;
    int done;
};

int findshortestjob(struct process p[10],int n,int currenttime){
    int shortestjobid=-1;
    int min_bt=INT_MAX;

    for(int i=0;i<n;i++){
        if(p[i].done==0 && p[i].at<=currenttime){
            if(p[i].bt<min_bt){
                min_bt=p[i].bt;
                shortestjobid=i;
            }
            else if(p[i].bt==min_bt){
                if(p[i].at < p[shortestjobid].at) {
                    shortestjobid = i;
                }
            }
        }
    }
    return shortestjobid;
}

int main(){
    int n;
    printf("enter number of processes: ");
    scanf("%d",&n);
    struct process p[n];

    for(int i=0;i<n;i++){
        printf("Enter arrival time and burst time for P%d ", i+1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at,&p[i].bt);
        p[i].done=0;
    }

    int completed=0,current_time=0;

    int total_tat=0,total_wt=0;

    while(completed!=n){
        int idx=findshortestjob(p,n,current_time);

        if(idx!=-1){
            p[idx].st=current_time;
            p[idx].ct=p[idx].st+p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat+=p[idx].tat;
            total_wt+=p[idx].wt;

            p[idx].done=1;
            completed++;
            current_time=p[idx].ct;
        }
        else{
            current_time++;  // no process arrived yet, idle time
        }
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);
    printf("Average Waiting Time = %.2f\n", (float)total_wt/n);

    return 0;

}

//------------------------------------------preemptive------------------------------------

struct process{
    int pid;
    int at;
    int bt;
    int ct;
    int rbt;
    int tat;
    int wt;
    int st;
    int done;
};

int findshortestjob(struct process p[], int n, int currenttime) {
    int shortestjobid = -1;
    int min_rbt = INT_MAX;

    for(int i = 0; i < n; i++) {
        if(p[i].done == 0 && p[i].at <= currenttime) {
            if(p[i].rbt < min_rbt) {
                min_rbt = p[i].rbt;
                shortestjobid = i;
            }
            else if(p[i].rbt == min_rbt) {
                if(p[i].at < p[shortestjobid].at) {
                    shortestjobid = i;
                }
            }
        }
    }
    return shortestjobid;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i+1);
        p[i].pid = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rbt = p[i].bt; // initially remaining time = burst time
        p[i].done = 0;
    }

    int completed = 0, current_time = 0;
    int total_tat = 0, total_wt = 0;

    int is_first_time[n]; // to check if process is starting first time

    for(int i = 0; i < n; i++) {
        is_first_time[i] = 1;
    }

    while(completed != n) {
        int idx = findshortestjob(p, n, current_time);

        if(idx != -1) {
            if(is_first_time[idx]) {
                p[idx].st = current_time;
                is_first_time[idx] = 0;
            }

            p[idx].rbt--; // run for 1 unit

            if(p[idx].rbt == 0) {
                p[idx].ct = current_time + 1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].done = 1;
                completed++;

                total_tat += p[idx].tat;
                total_wt += p[idx].wt;
            }
        }

        current_time++;
    }

    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);
    printf("Average Waiting Time = %.2f\n", (float)total_wt/n);

    return 0;
}



//in both...please remember that you have to build adifferent function to get shortestjob.


/*----------non premptive------------

get shortest job id first 
till completed!=n loop and take shortest job id and compute things 
remember about completed, current time here

------------premptive-------------

get shortest remaining time first
till completed!=n loop, apply is first time, if its first time then st=currtime
below it decrement remtime, then another if to check if remtime become 0, if yes
then only compute all the things , finally currtime++;
dont forget to make done =1 and increment completed everytime.
*/
