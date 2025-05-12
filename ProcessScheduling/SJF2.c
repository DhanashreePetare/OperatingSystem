#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// struct process {
// int id,at,bt,ct,st,tat,wt,done;
// };
// int currtime=0;

// int shortestjob(struct process p[],int n,int currtime){
//     int idx=-1;
//     int minbt=INT_MAX;

//     for(int i=0;i<n;i++){
//         if(p[i].done==0 && p[i].at<currtime){
//             if(p[i].bt<minbt){
//             minbt=p[i].bt;
//             idx=i;
//             }
//             else if(p[i].bt==minbt){
//                 if(p[i].at<p[idx].at){
//                     idx=i;
//                 }
//             }
//         }
//     }
//     return idx;
// }

// void drawGanttChart(struct process p[],int n){
//     printf("\nGantt Chart:\n");
//     printf(" ");
//     for(int i=0;i<n;i++){
//         printf("--------");
//     }
//     printf("\n|");
//     for(int i=0;i<n;i++){
//         printf("P%d |",p[i].id);
//     }
//     printf("\n ");
//     for(int i=0;i<n;i++){
//         printf("--------");
//     }
//     printf("\n");
//     printf("0");
//     for(int i=0;i<n;i++){
//         printf("    %d",p[i].ct);
//     }
//     printf("\n");
// }


// int main(){
//     printf("enter number of processes: ");
//     int n;
//     scanf("%d",&n);
    
//     struct process p[n];
//     printf("enter id,at,bt of all processes: ");
//     for(int i=0;i<n;i++){
//         scanf("%d %d %d",&p[i].id,&p[i].at,&p[i].bt);
//          p[i].done=0;
//     }
    
//     int completed=0,currtime=0;
    
//     while(completed!=n){
//         int idx=shortestjob(p,n,currtime);
//         if(idx!=-1){
//             p[idx].st=currtime;
//             p[idx].ct=p[idx].st+p[idx].bt;
//             p[idx].tat=p[idx].ct-p[idx].at;
//             p[idx].wt=p[idx].tat-p[idx].bt;

//             p[idx].done=1;
//             completed++;
//             currtime=p[idx].ct;
//         }
//         else{
//             currtime++;
//         }
//     }
//     printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
//     for(int i = 0; i < n; i++) {
//         printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
//     }
//     return 0;
// }

//---------------------------------------preemptive--------------------------------------

struct process{
    int id,at,bt,ct,rbt,st,done,tat,wt,rt;
};

// void gantt(struct process p[], int n) {
//     printf("\nGantt Chart:\n");

//     // Print process execution blocks
//     for(int i = 0; i < n; i++) {
//         printf("  P%d  ", p[i].id);
//     }
//     printf("\n");

//     // Print time markers
//     printf("%d", p[0].st);
//     for(int i = 0; i < n; i++) {
//         printf("     %d", p[i].ct);
//     }
//     printf("\n");
// }

int shortestjob(struct process p[],int n,int currtime){
    int idx=-1;
    int minrbt=INT_MAX;

    for(int i=0;i<n;i++){
        if(p[i].done==0 && p[i].at<=currtime){
            if(p[i].rbt<minrbt){
                minrbt=p[i].rbt;
                idx=i;
            }
            else if(p[i].rbt==minrbt){
                if(p[i].at<p[idx].at){
                    idx=i;
                }
            }
        }
    }
    return idx;
}

int main(){
int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    for(int i = 0; i < n; i++) {
        printf("Enter arrival time and burst time for P%d: ", i+1);
        p[i].id = i + 1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].done=0;
        p[i].rbt=p[i].bt;
    }

    int completed=0,currtime=0;

    int is_first_time[n];
    for(int i = 0; i < n; i++) is_first_time[i] = 1;

    while(completed!=n){
        int idx=shortestjob(p,n,currtime);
        if(idx!=-1){
            if(is_first_time[idx]){
                p[idx].st=currtime;
                is_first_time[idx]=0;
            }
            p[idx].rbt--;
            currtime++;

            if(p[idx].rbt==0){
                p[idx].ct=currtime;
                p[idx].tat=p[idx].ct-p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;
                p[idx].done = 1;
                completed++;
            }
        }
        currtime++;
    }
    printf("\nProcess\tAT\tBT\tCT\tTAT\tWT\n");
    for(int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }
    // gantt(p,n);

    return 0;
}


