#include <stdio.h>
#include <stdlib.h>

#define TRACKS 100

//bubble sort
void sort(int tracks[], int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (tracks[j] > tracks[j + 1]) {
                int temp = tracks[j];
                tracks[j] = tracks[j + 1];
                tracks[j + 1] = temp;
            }
        }
    }
}

void c_scan(int tracks[], int n, int start) {
    int i, j, seek_count = 0;
    int current_track = start;

    sort(tracks, n);

    int start_index = -1;
    for (i = 0; i < n; i++) {
        if (tracks[i] >= start) {
            start_index = i;
            break;
        }
    }

    printf("Sequence of tracks visited: ");
    for (i = start_index; i < n; i++) {
        printf("%d ", tracks[i]);
        seek_count += abs(tracks[i] - current_track);
        current_track = tracks[i];
    }

    printf("%d ", 0);
    seek_count += abs(current_track);
    current_track = 0;

    for (i = 0; i < start_index; i++) {
        printf("%d ", tracks[i]);
        seek_count += abs(tracks[i] - current_track);
        current_track = tracks[i];
    }

    printf("\nTotal number of track movements: %d\n", seek_count);
}

int main() {
    int n, start_track;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int tracks[n];
    printf("Enter the request numbers: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &tracks[i]);
    }

    printf("Enter the current position of Read/Write head: ");
    scanf("%d", &start_track);

    c_scan(tracks, n, start_track);

    return 0;
}

/*
8
95 180 34 119 11 123 62 64
50
*/
