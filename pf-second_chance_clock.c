#include <stdio.h>
#include <stdlib.h>

void secondChance(int ref[], int size, int n) {
    int frames[n];
    int referenceBits[n];
    int pointer = 0;
    int pageMiss = 0;
    int pageHits = 0;

    for (int i = 0; i < n; i++) {
        frames[i] = -1;
        referenceBits[i] = 0;
    }

    for (int i = 0; i < size; i++) {
        int flag = 0;
        for (int j = 0; j < n; j++) {
            if (frames[j] == ref[i]) {
                flag = 1;
                referenceBits[j] = 1;
                break;
            }
        }

        if (flag == 1) {
            pageHits++;
        } else {
            while (referenceBits[pointer] == 1) {
                referenceBits[pointer] = 0;
                pointer = (pointer + 1) % n;
            }

            frames[pointer] = ref[i];
            referenceBits[pointer] = 1;
            pointer = (pointer + 1) % n;
            pageMiss++;
        }
    }

    printf("Second Chance Page Faults: %d, Page Hits: %d\n", pageMiss, pageHits);
}

int main(void) {
    int frames;
    printf("Enter the number of frames: ");
    scanf("%d", &frames);

    int size;
    printf("Enter the size of the reference string: ");
    scanf("%d", &size);

    int ref[size];
    printf("Enter the reference string: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &ref[i]);
    }

    secondChance(ref, size, frames);

    return 0;
}

/*
3
20
7 1 0 2 0 3 0 4 2 3 0 3 2 1 2 0 1 7 0 1
*/
