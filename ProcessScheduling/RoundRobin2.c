#include <stdio.h>
#define MAX 100

struct process {
    int id, at, bt, rt, ct, tat, wt;
    int visited; // To track if added to queue
};

int main() {
    int n, tq;
    printf("Enter number of processes: ");
    scanf("%d", &n);

    struct process p[n];
    
    // Input process details
    for (int i = 0; i < n; i++) {
        printf("Enter arrival time of P%d: ", i);
        scanf("%d", &p[i].at);
        printf("Enter burst time of P%d: ", i);
        scanf("%d", &p[i].bt);
        p[i].rt = p[i].bt; // Remaining time = burst time initially
        p[i].visited = 0;   // Not yet added to queue
        p[i].id = i;        // Process ID
    }

    printf("Enter time quantum: ");
    scanf("%d", &tq);

    int time = 0, completed = 0;
    int queue[MAX], front = 0, rear = 0;

    // Initially, enqueue processes that arrive at time 0
    for (int i = 0; i < n; i++) {
        if (p[i].at == time) {
            queue[rear++] = i;
            p[i].visited = 1;
        }
    }

    printf("\n=== Round Robin Execution ===\n");

    while (completed < n) {
        if (front == rear) { // No process ready
            printf("Time %d: CPU Idle\n", time);
            time++;
            // Check for new arrivals
            for (int i = 0; i < n; i++) {
                if (!p[i].visited && p[i].at <= time) {
                    queue[rear++] = i;
                    p[i].visited = 1;
                }
            }
            continue;
        }

        int current = queue[front++]; // Get next process
        printf("Time %d: Executing P%d\n", time, current);

        // Execute for time quantum or remaining time (whichever is smaller)
        int slice = (p[current].rt < tq) ? p[current].rt : tq;
        p[current].rt -= slice;
        time += slice;

        // Check for new arrivals during execution
        for (int i = 0; i < n; i++) {
            if (!p[i].visited && p[i].at <= time) {
                queue[rear++] = i;
                p[i].visited = 1;
            }
        }

        if (p[current].rt > 0) {
            queue[rear++] = current; // Re-enqueue if not finished
        } else {
            p[current].ct = time;    // Process completed
            completed++;
            printf("-> P%d completed at time %d\n", current, time);
        }
    }

    // Calculate TAT and WT
    float avg_tat = 0, avg_wt = 0;
    printf("\n=== Results ===\n");
    printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n", 
               p[i].id, p[i].at, p[i].bt, p[i].ct, p[i].tat, p[i].wt);
    }

    printf("\nAverage Turnaround Time = %.2f\n", avg_tat / n);
    printf("Average Waiting Time = %.2f\n", avg_wt / n);

    return 0;
}