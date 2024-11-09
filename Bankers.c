#include <stdio.h>

int main() {
    // Number of processes and resources
    int n = 5; // Number of processes
    int r = 3; // Number of resources

    // Allocation Matrix: Resources currently allocated to each process
    int alloc[5][3] = {{0, 1, 0},
                       {2, 0, 0},
                       {3, 0, 2},
                       {2, 1, 1},
                       {0, 0, 2}};

    // Max Matrix: Maximum resources that each process may need
    int max[5][3] = {{7, 5, 3},
                     {3, 2, 2},
                     {9, 0, 2},
                     {4, 2, 2},
                     {5, 3, 3}};

    // Available resources
    int avail[3] = {3, 3, 2};

    // Need Matrix: Calculated as Max - Alloc
    int need[5][3];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < r; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Array to track finished processes (0 = not finished, 1 = finished)
    int finished[5] = {0};
    int safeSequence[5]; // Array to store the safe sequence
    int count = 0;       // Counter for safe sequence index

    // Loop to find the safe sequence
    while (count < n) {
        int found = 0; // Flag to check if we find a process in this loop

        for (int i = 0; i < n; i++) {
            if (!finished[i]) { // Check if the process is not finished
                int canProceed = 1;

                // Check if the process can get the required resources
                for (int j = 0; j < r; j++) {
                    if (need[i][j] > avail[j]) {
                        canProceed = 0; // Process can't proceed if any need > available
                        break;
                    }
                }

                // If the process can proceed
                if (canProceed) {
                    // Add this process to the safe sequence
                    safeSequence[count++] = i;

                    // Release the resources held by this process (add alloc to avail)
                    for (int j = 0; j < r; j++) {
                        avail[j] += alloc[i][j];
                    }

                    // Mark the process as finished
                    finished[i] = 1;

                    found = 1; // We found at least one process in this pass
                }
            }
        }

        // If no process was found in this iteration, we are in an unsafe state
        if (!found) {
            printf("The system is in an UNSAFE state.\n");
            return 1;
        }
    }

    // If we reach here, the system is in a safe state
    printf("The system is in a SAFE state.\nSafe sequence is: ");
    for (int i = 0; i < n - 1; i++) {
        printf("P%d -> ", safeSequence[i]);
    }
    printf("P%d\n", safeSequence[n - 1]);

    return 0;
}