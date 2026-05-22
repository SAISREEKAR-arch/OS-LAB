#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int Allocation[P][R], Request[P][R];
    int Available[R], Work[R];
    bool Finish[P];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &Allocation[i][j]);

    printf("\nEnter Request Matrix:\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &Request[i][j]);

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < R; j++)
        scanf("%d", &Available[j]);

    // Initialize
    for (j = 0; j < R; j++)
        Work[j] = Available[j];

    for (i = 0; i < P; i++) {
        Finish[i] = false;
        for (j = 0; j < R; j++) {
            if (Allocation[i][j] != 0) {
                Finish[i] = false;
                break;
            }
        }
    }

    // Detection Algorithm
    bool found;
    do {
        found = false;

        for (i = 0; i < P; i++) {
            if (!Finish[i]) {

                bool canExecute = true;

                for (j = 0; j < R; j++) {
                    if (Request[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (j = 0; j < R; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = true;
                    found = true;
                }
            }
        }

    } while (found);

    // Check deadlock
    bool deadlock = false;
    for (i = 0; i < P; i++) {
        if (!Finish[i]) {
            deadlock = true;
            printf("Process P%d is deadlocked\n", i);
        }
    }

    if (!deadlock)
        printf("\nNo Deadlock Detected\n");

    return 0;
}
