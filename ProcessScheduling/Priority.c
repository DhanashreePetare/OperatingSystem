//Priority
//      preemptive and non preemptive

#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

//------------------------------------------non-preemptive---------------------------------


struct process {
    int pid;
    int at;
    int bt;
    int pri;   // priority
    int ct;
    int tat;
    int wt;
    int st;
    int done;
};

int findHighestPriority(struct process p[], int n, int current_time) {
    int idx = -1;
    int highest_priority = INT_MAX;  // smaller number = higher priority

    for (int i = 0; i < n; i++) {
        if (p[i].done == 0 && p[i].at <= current_time) {
            if (p[i].pri < highest_priority) {
                highest_priority = p[i].pri;
                idx = i;
            } else if (p[i].pri == highest_priority) {
                if (p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
    }
    return idx;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].done = 0;
    }

    int completed = 0, current_time = 0;
    int total_tat = 0, total_wt = 0;

    while (completed != n) {
        int idx = findHighestPriority(p, n, current_time);

        if (idx != -1) {
            p[idx].st = current_time;
            p[idx].ct = p[idx].st + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            total_tat += p[idx].tat;
            total_wt += p[idx].wt;

            p[idx].done = 1;
            completed++;
            current_time = p[idx].ct;
        } else {
            current_time++;
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);
    printf("Average Waiting Time = %.2f\n", (float)total_wt/n);

    return 0;
}

//------------------------------------------preemptive------------------------------------

struct process {
    int pid;
    int at;
    int bt;
    int rbt;  // remaining burst time
    int pri;
    int ct;
    int tat;
    int wt;
    int st;
    int done;
};

int findHighestPriority(struct process p[], int n, int current_time) {
    int idx = -1;
    int highest_priority = INT_MAX;

    for (int i = 0; i < n; i++) {
        if (p[i].done == 0 && p[i].at <= current_time) {
            if (p[i].pri < highest_priority) {
                highest_priority = p[i].pri;
                idx = i;
            } else if (p[i].pri == highest_priority) {
                if (p[i].at < p[idx].at) {
                    idx = i;
                }
            }
        }
    }
    return idx;
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct process p[n];

    for (int i = 0; i < n; i++) {
        printf("Enter arrival time, burst time and priority for P%d: ", i + 1);
        p[i].pid = i + 1;
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].pri);
        p[i].rbt = p[i].bt; // initially rbt = bt
        p[i].done = 0;
    }

    int completed = 0, current_time = 0;
    int total_tat = 0, total_wt = 0;

    while (completed != n) {
        int idx = findHighestPriority(p, n, current_time);

        if (idx != -1) {
            if (p[idx].rbt == p[idx].bt) {
                p[idx].st = current_time;
            }

            p[idx].rbt--;
            current_time++;

            if (p[idx].rbt == 0) {
                p[idx].ct = current_time;
                p[idx].tat = p[idx].ct - p[idx].at;
                p[idx].wt = p[idx].tat - p[idx].bt;

                total_tat += p[idx].tat;
                total_wt += p[idx].wt;

                p[idx].done = 1;
                completed++;
            }
        } else {
            current_time++;  // CPU is idle
        }
    }

    printf("\nProcess\tAT\tBT\tPriority\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%d\n", p[i].pid, p[i].at, p[i].bt, p[i].pri, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat/n);
    printf("Average Waiting Time = %.2f\n", (float)total_wt/n);

    return 0;
}
