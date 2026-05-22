#include <stdio.h>
#include <stdbool.h>

int main() {
    int P, R, i, j;

    printf("Enter number of processes: ");
    scanf("%d", &P);

    printf("Enter number of resource types: ");
    scanf("%d", &R);

    int Allocation[P][R], Max[P][R], Need[P][R];
    int Available[R], Work[R];
    bool Finish[P];
    int SafeSequence[P];

    // NEW
    int Request[R], process;

    printf("\nEnter Allocation Matrix:\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &Allocation[i][j]);

    printf("\nEnter Max Matrix:\n");
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            scanf("%d", &Max[i][j]);

    printf("\nEnter Available Resources:\n");
    for (j = 0; j < R; j++)
        scanf("%d", &Available[j]);

    // Need = Max - Allocation
    for (i = 0; i < P; i++)
        for (j = 0; j < R; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];

    // 🔹 Take single request
    printf("\nEnter process number (0 to %d): ", P - 1);
    scanf("%d", &process);

    printf("Enter request vector:\n");
    for (j = 0; j < R; j++)
        scanf("%d", &Request[j]);

    // 🔹 Step 1: Check Request ≤ Need and ≤ Available
    for (j = 0; j < R; j++) {
        if (Request[j] > Need[process][j]) {
            printf("\nError: Request exceeds Need!\n");
            return 0;
        }
        if (Request[j] > Available[j]) {
            printf("\nResources not available. Process must wait.\n");
            return 0;
        }
    }

    // 🔹 Step 2: Pretend to allocate
    for (j = 0; j < R; j++) {
        Available[j] -= Request[j];
        Allocation[process][j] += Request[j];
        Need[process][j] -= Request[j];
    }

    // 🔹 Step 3: Safety Algorithm
    for (j = 0; j < R; j++)
        Work[j] = Available[j];

    for (i = 0; i < P; i++)
        Finish[i] = false;

    int count = 0;

    while (count < P) {
        bool found = false;

        for (i = 0; i < P; i++) {
            if (!Finish[i]) {

                bool canExecute = true;
                for (j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j]) {
                        canExecute = false;
                        break;
                    }
                }

                if (canExecute) {
                    for (j = 0; j < R; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = true;
                    SafeSequence[count++] = i;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    // 🔹 Step 4: Decide
    if (count == P) {
        printf("\nRequest GRANTED. System is in SAFE STATE\nSequence: ");
        for (i = 0; i < P; i++)
            printf("P%d ", SafeSequence[i]);
    } else {
        printf("\nRequest DENIED. System would be UNSAFE\n");
    }

    return 0;
}
