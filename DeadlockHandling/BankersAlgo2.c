#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resources: ");
    scanf("%d", &R);

    int allocation[P][R], max[P][R], need[P][R], available[R];

    // Input allocation matrix
    printf("Enter allocation matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input max matrix
    printf("Enter maximum matrix:\n");
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input available resources
    printf("Enter available resources:\n");
    for (int i = 0; i < R; i++) {
        scanf("%d", &available[i]);
    }

    // Calculate need matrix
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Initialize finish array
    bool finish[P];
    for (int i = 0; i < P; i++) {
        finish[i] = false;
    }

    int work[R];
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < P) {
        bool found = false;

        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool can_allocate = true;

                for (int j = 0; j < R; j++) {
                    if (need[p][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int k = 0; k < R; k++) {
                        work[k] += allocation[p][k];
                    }

                    finish[p] = true;
                    found = true;
                    count++;

                    printf("Process %d is executed.\n", p);
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return 0;
        }
    }

    printf("System is in a safe state.\n");
    return 0;
}