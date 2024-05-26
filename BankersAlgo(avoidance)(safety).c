#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 10
#define MAX_RESOURCES 10

int no_of_processes, no_of_resources;
int available[MAX_RESOURCES];
int max_need[MAX_PROCESSES][MAX_RESOURCES];
int allocated[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];
bool finish[MAX_PROCESSES];

// Function to check if a process can be safely executed
bool isSafe(int process) {
    for (int i = 0; i < no_of_resources; i++) {
        if (need[process][i] > available[i])
            return false;
    }
    return true;
}

int main() {
    printf("** BANKER'S ALGORITHM **\n\n");

    // Input the number of processes and resources
    printf("Enter the number of processes: ");
    scanf("%d", &no_of_processes);
    printf("Enter the number of resources: ");
    scanf("%d", &no_of_resources);

    // Input the maximum resource needs for each process
    printf("Enter the maximum resource needs for each process:\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < no_of_resources; j++) {
            scanf("%d", &max_need[i][j]);
        }
        finish[i] = false;
    }

    // Input the allocated resources for each process
    printf("Enter the allocated resources for each process:\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("Process %d: ", i);
        for (int j = 0; j < no_of_resources; j++) {
            scanf("%d", &allocated[i][j]);
            need[i][j] = max_need[i][j] - allocated[i][j];
        }
    }

    // Input the available resources
    printf("Enter the available resources: ");
    for (int i = 0; i < no_of_resources; i++) {
        scanf("%d", &available[i]);
    }

    // Display the resource allocation table
    printf("\nResource Allocation Table:\n");
    printf("Process | Maximum  | Allocated | Needed  |\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < no_of_processes; i++) {
        printf("P%d      | ", i);
        for (int j = 0; j < no_of_resources; j++) {
            printf("%d ", max_need[i][j]);
        }
        printf("| ");
        for (int j = 0; j < no_of_resources; j++) {
            printf("%d ", allocated[i][j]);
        }
        printf("| ");
        for (int j = 0; j < no_of_resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Determine a safe sequence
    bool safe = true;
    int safe_sequence[MAX_PROCESSES];
    int sequence_index = 0;

    for (int count = 0; count < no_of_processes; count++) {
        bool found = false;
        for (int i = 0; i < no_of_processes; i++) {
            if (!finish[i] && isSafe(i)) {
                // Simulate the execution of this process
                for (int j = 0; j < no_of_resources; j++) {
                    available[j] += allocated[i][j];
                }
                safe_sequence[sequence_index++] = i;
                finish[i] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            safe = false;
            break;
        }
    }

    if (safe) {
        // Print the safe sequence if it exists
        printf("\nSystem is in a safe state.\n");
        printf("Safe sequence: ");
        for (int i = 0; i < sequence_index; i++) {
            printf("P%d ", safe_sequence[i]);
        }
        printf("\n");
    } else {
        // Indicate that the system is in an unsafe state
        printf("\nSystem is in an unsafe state. Deadlock detected.\n");
        printf("Processes involved in the deadlock: ");
        for (int i = 0; i < no_of_processes; i++) {
            if (!finish[i]) {
                printf("P%d ", i);
            }
        }
        printf("\n");
    }

    return 0;
}

/*5
3
7 5 3
3 2 2
9 0 2
4 2 2
5 3 3
0 1 0
2 0 0
3 0 2 
2 1 1
0 0 2
3 3 2*/
