#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R;
    int i, j;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int Allocation[P][R], Max[P][R], Need[P][R];
    int Available[R], Work[R];
    bool Finish[P];
    int SafeSequence[P];

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            scanf("%d", &Allocation[i][j]);
        }
    }

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            scanf("%d", &Max[i][j]);
        }
    }

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < R; j++) {
        scanf("%d", &Available[j]);
    }

    for (i = 0; i < P; i++) {
        for (j = 0; j < R; j++) {
            Need[i][j] = Max[i][j] - Allocation[i][j];
        }
    }

    for (j = 0; j < R; j++) {
        Work[j] = Available[j];
    }

    for (i = 0; i < P; i++) {
        Finish[i] = false;
    }

    int count = 0;

    while (count < P) {
        bool found = false;

        for (i = 0; i < P; i++) {

            if (Finish[i] == false) {

                bool canExecute = true;

                for (j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {

                    for (j = 0; j < R; j++) {
                        Work[j] += Allocation[i][j];
                    }

                    Finish[i] = true;
                    SafeSequence[count++] = i;

                    found = true;
                }
            }
        }

        if (found == false) {
            break;
        }
    }

    bool safe = true;
    for (i = 0; i < P; i++) {
        if (Finish[i] == false) {
            safe = false;
            break;
        }
    }

    if (safe) {
        printf("\nSystem is in SAFE STATE\nSafe Sequence: ");
        for (i = 0; i < P; i++) {
            printf("P%d ", SafeSequence[i]);
        }
        printf("\n");
    } else {
        printf("\nSystem is in UNSAFE STATE (Potential Deadlock)\n");
    }

    return 0;
}
