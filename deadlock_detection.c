#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

void printMatrix(int matrix[MAX_PROCESSES][MAX_RESOURCES], int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

bool isSafeState(int processes, int resources, int available[], int allocation[MAX_PROCESSES][MAX_RESOURCES], int request[MAX_PROCESSES][MAX_RESOURCES]) {
    bool finish[MAX_PROCESSES] = { false };
    int work[MAX_RESOURCES];

    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    while (true) {
        bool found = false;

        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool canProceed = true;

                for (int j = 0; j < resources; j++) {
                    if (request[i][j] > work[j]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int k = 0; k < resources; k++) {
                        work[k] += allocation[i][k];
                    }
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            for (int i = 0; i < processes; i++) {
                if (!finish[i]) {
                    return false; // System is not in a safe state
                }
            }
            return true; // System is in a safe state
        }
    }
}

int main() {
    int processes, resources;
    int allocation[MAX_PROCESSES][MAX_RESOURCES];
    int request[MAX_PROCESSES][MAX_RESOURCES];
    int available[MAX_RESOURCES];

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    printf("Enter the request matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &request[i][j]);
        }
    }

    printf("Enter the available resources vector:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    if (isSafeState(processes, resources, available, allocation, request)) {
        printf("The system is in a safe state.\n");
    } else {
        printf("The system is in a deadlock state.\n");
    }

    return 0;
}

/*
5
3
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2
0 0 0
2 0 2
0 0 0
1 0 0
0 0 2
0 0 0
*/
