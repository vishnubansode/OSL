#include <stdio.h>
#include <limits.h>

void FCFS(int pages[], int n, int frames[], int frameSize) {
    int pageFaults = 0, index = 0;
    
   

    printf("\nFCFS Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            frames[index] = pages[i];
            index = (index + 1) % frameSize;
            pageFaults++;
        }

        // Print frames
        printf("Page %d -> [", pages[i]);
        for (int k = 0; k < frameSize; k++) {
            if (frames[k] == -1)
                printf("  ");
            else
                printf("%d ", frames[k]);
        }
        printf("]\n");
    }
    printf("Total Page Faults in FCFS: %d\n", pageFaults);
}

void LRU(int pages[], int n, int frames[], int frameSize) {
    int pageFaults = 0;
    int recent[frameSize];
    for (int i = 0; i < frameSize; i++) {
        recent[i] = -1;
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                recent[j] = i;
                break;
            }
        }

        if (!found) {
            int lru = 0;
            for (int j = 1; j < frameSize; j++) {
                if (recent[j] < recent[lru]) {
                    lru = j;
                }
            }
            frames[lru] = pages[i];
            recent[lru] = i;
            pageFaults++;
        }

        // Print frames
        printf("Page %d -> [", pages[i]);
        for (int k = 0; k < frameSize; k++) {
            if (frames[k] == -1)
                printf("  ");
            else
                printf("%d ", frames[k]);
        }
        printf("]\n");
    }
    printf("Total Page Faults in LRU: %d\n", pageFaults);
}

void Optimal(int pages[], int n, int frames[], int frameSize) {
    int pageFaults = 0;

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < n; i++) {
        int found = 0;
        // Check if page is already in frame
        for (int j = 0; j < frameSize; j++) {
            if (frames[j] == pages[i]) {
                found = 1;
                break;
            }
        }

        if (!found) {
            int furthest = -1, replaceIndex = -1;
            for (int j = 0; j < frameSize; j++) {
                int nextUse = n;
                for (int k = i + 1; k < n; k++) {
                    if (frames[j] == pages[k]) {
                        nextUse = k;
                        break;
                    }
                }
                if (nextUse > furthest) {
                    furthest = nextUse;
                    replaceIndex = j;
                }
            }
            frames[replaceIndex] = pages[i];
            pageFaults++;
        }

        // Print frames
        printf("Page %d -> [", pages[i]);
        for (int k = 0; k < frameSize; k++) {
            if (frames[k] == -1)
                printf("  ");
            else
                printf("%d ", frames[k]);
        }
        printf("]\n");
    }
    printf("Total Page Faults in Optimal: %d\n", pageFaults);
}

int main() {
    int n, frameSize;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the page references: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &pages[i]);
    }

    printf("Enter the frame size (minimum 3): ");
    scanf("%d", &frameSize);

    if (frameSize < 3) {
        printf("Frame size should be at least 3.\n");
        return 1;
    }

    int frames[frameSize];

    // Initialize frames for FCFS and run
    for (int i = 0; i < frameSize; i++) frames[i] = -1;
    FCFS(pages, n, frames, frameSize);

    // Initialize frames for LRU and run
    for (int i = 0; i < frameSize; i++) frames[i] = -1;
    LRU(pages, n, frames, frameSize);

    // Initialize frames for Optimal and run
    for (int i = 0; i < frameSize; i++) frames[i] = -1;
    Optimal(pages, n, frames, frameSize);

    return 0;
}