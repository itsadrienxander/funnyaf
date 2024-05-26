#include <stdio.h>
#include <stdlib.h>

int main() {
    int queue[20], head, n, i, total_movement = 0;

    printf("Enter the number of requests: ");
    scanf("%d", &n);

    printf("Enter the request queue:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &queue[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &head);

    int direction;
    printf("Enter the direction (0 for left, 1 for right): ");
    scanf("%d", &direction);

    int max_track = 200;

    for(i = 0; i < n-1; i++) {
        for(int j = i+1; j < n; j++) {
            if(queue[i] > queue[j]) {
                int temp = queue[i];
                queue[i] = queue[j];
                queue[j] = temp;
            }
        }
    }

    int index;
    for(i = 0; i < n; i++) {
        if(queue[i] >= head) {
            index = i;
            break;
        }
    }

    if(direction == 0) {
        for(i = index-1; i >= 0; i--) {
            printf("Head movement from %d to %d\n", head, queue[i]);
            total_movement += abs(head - queue[i]);
            head = queue[i];
        }
        total_movement += head; // Move to track 0
        head = 0;
        for(i = index; i < n; i++) {
            printf("Head movement from %d to %d\n", head, queue[i]);
            total_movement += abs(head - queue[i]);
            head = queue[i];
        }
    } else {
        for(i = index; i < n; i++) {
            printf("Head movement from %d to %d\n", head, queue[i]);
            total_movement += abs(head - queue[i]);
            head = queue[i];
        }
        total_movement += max_track - head; // Move to the last track
        head = max_track;
        for(i = index-1; i >= 0; i--) {
            printf("Head movement from %d to %d\n", head, queue[i]);
            total_movement += abs(head - queue[i]);
            head = queue[i];
        }
    }

    printf("Total head movement: %d\n", total_movement);

    return 0;
}

/*
8
95 180 34 119 11 123 62 64
50
*/
