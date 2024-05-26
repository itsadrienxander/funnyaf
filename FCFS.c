#include <stdio.h>

int main() {
    int bt[15];
    int at[15];
    int ct[15];
    int wt[15];
    int tat[15];
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time of all the processes:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
    }

    int total_time = 0;
    for (int i = 0; i < n; i++) {
        if (at[i] > total_time) {
            total_time = at[i];
        }
        ct[i] = total_time + bt[i];
        total_time = ct[i];
        tat[i] = ct[i] - at[i];
        wt[i] = tat[i] - bt[i];
    }

    float avg_tat = 0, avg_wt = 0;
    for (int i = 0; i < n; i++) {
        avg_tat += tat[i];
        avg_wt += wt[i];
    }
    avg_tat /= n;
    avg_wt /= n;

    printf("\nArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", at[i], bt[i], ct[i], tat[i], wt[i]);
    }

    printf("\nAverage Turnaround Time: %.2f\n", avg_tat);
    printf("Average Waiting Time: %.2f\n", avg_wt);

    return 0;
}

/*
4
0
1
2
3
3
4
2
1
*/
