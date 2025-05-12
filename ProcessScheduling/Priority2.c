#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

// struct process {
//     int id,at,bt,ct,pri,tat,wt,st,done;
// };

// int findhighenstpri(struct process p[],int n,int currtime){
// int idx=-1;
// int highpri=INT_MAX;

// for(int i=0;i<n;i++){
//     if(p[i].done==0 && p[i].at<=currtime){
//         if(p[i].pri<highpri){
//             highpri=p[i].pri;
//             idx=i;
//         }
//         else if(p[i].pri==highpri){
//             if(p[i].at<p[idx].at){
//                 idx=i;
//             }
//         }
//     }
// }
// return idx;
// }

// int main(){
//     int n;
//     printf("Enter number of processes: ");
//     scanf("%d", &n);
//     struct process p[n];

//     for (int i = 0; i < n; i++) {
//         printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
//         p[i].id = i + 1;
//         scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
//         p[i].done = 0;
//     }

//     int completed = 0, currtime = 0;

//     while(completed!=n){
//         int idx=findhighenstpri(p,n,currtime);
//         if(idx!=-1){
//             p[idx].st=currtime;
//              p[idx].ct = p[idx].st + p[idx].bt;
//             p[idx].tat = p[idx].ct - p[idx].at;
//             p[idx].wt = p[idx].tat - p[idx].bt;

//             p[idx].done=1;
//             completed++;
//             currtime=p[idx].ct;
//         }
//         else{
//             currtime++;
//         }
//     }
//     printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
//     for (int i = 0; i < n; i++) {
//         printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
//     }
//     return 0;
// }

//---------------------------------------preemptive--------------------------------

struct process{
    int id,at,bt,rbt,ct,st,tat,wt,done,pri;
};

int findhighestpri(struct process p[], int n,int currtime){
    int idx=-1;
    int highpri=INT_MAX;

    for(int i=0;i<n;i++){
        if(p[i].done==0 && p[i].at<=currtime){
            if(p[i].pri<highpri){
                highpri=p[i].pri;
                idx=i;
            }
            else if(p[i].pri==highpri){
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

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        p[i].id = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].rbt = p[i].bt; 
        p[i].done = 0;
    }

    int completed = 0, currtime = 0;
    int isfirsttime[n];
    for(int i=0;i<n;i++){
        isfirsttime[i]=1;
    }

    while(completed!=n){
        int idx=findhighestpri(p,n,currtime);

        if(idx!=-1){
            if(isfirsttime[idx]){
                p[idx].st=currtime;
                isfirsttime[idx]=0;
            }
            p[idx].rbt--;
            currtime++;

            if(p[idx].rbt==0){
                p[idx].ct=currtime+1;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                p[idx].done=1;
                completed++;

            }
        }
        else{
            currtime++;
        }
    }
    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].id, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }
    return 0;
}

/*----------non premptive------------

get higher priority job id first 
till completed!=n loop and take shortest job id and compute things 

------------premptive-------------

get highest priority job id first
till completed!=n loop, apply is first time logic, and take shortest job id and compute things. 
*/

