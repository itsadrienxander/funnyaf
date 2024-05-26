#include <stdio.h>

int main() {
    int n, i, j, time = 0, smallest, count = 0, end_time;
    int at[10], bt[10], rt[10], ct[10], tat[10], wt[10];
    float avg_tat = 0, avg_wt = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter arrival time and burst time of all the processes:\n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d", &at[i], &bt[i]);
        rt[i] = bt[i];
    }

    rt[9] = 9999;  // A large value for comparison
    for (time = 0; count != n; time++) {
        smallest = 9;
        for (i = 0; i < n; i++) {
            if (at[i] <= time && rt[i] < rt[smallest] && rt[i] > 0) {
                smallest = i;
            }
        }

        rt[smallest]--;

        if (rt[smallest] == 0) {
            count++;
            end_time = time + 1;
            ct[smallest] = end_time;
            tat[smallest] = end_time - at[smallest];
            wt[smallest] = tat[smallest] - bt[smallest];

            avg_tat += tat[smallest];
            avg_wt += wt[smallest];
        }
    }

    avg_tat /= n;
    avg_wt /= n;

    printf("\nArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (i = 0; i < n; i++) {
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
