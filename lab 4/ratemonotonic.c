#include <stdio.h>
#include <math.h>

#define MAX 10

typedef struct {
    int id;
    int burst;
    int deadline;
    int period;
    int weight;
    int remaining;
    int ct, wt, tat;
} Process;

Process p[MAX];
int n;

float calculateUtilization() {
    float u = 0;
    for (int i = 0; i < n; i++) {
        u += (float)p[i].burst / p[i].period;
    }
    return u;
}

void edf() {
    printf("\n====== Earliest Deadline First (EDF) Scheduling =====\n");

    float u = calculateUtilization();
    printf("CPU Utilization: %.2f\n", u);

    if (u <= 1)
        printf("Schedulable (Utilization <= 1)\n");
    else {
        printf("NOT Schedulable (Utilization > 1)\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].deadline > p[j].deadline) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;
    }

    printf("\nID  BF  Deadline  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d     %d       %d   %d   %d\n",
               p[i].id, p[i].burst, p[i].deadline,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

void rms() {
    printf("\n====== Rate Monotonic Scheduling (RMS) =====\n");

    float u = calculateUtilization();
    printf("CPU Utilization: %.2f\n", u);

    float bound = n * (pow(2, (1.0 / n)) - 1);
    printf("RM Bound: %.4f\n", bound);

    if (u <= bound)
        printf("Schedulable (Utilization <= RM Bound)\n");
    else {
        printf("NOT Schedulable (Utilization > RM Bound)\n");
        return;
    }

    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (p[i].period > p[j].period) {
                Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }

    int time = 0;
    for (int i = 0; i < n; i++) {
        time += p[i].burst;
        p[i].ct = time;
        p[i].tat = p[i].ct;
        p[i].wt = p[i].tat - p[i].burst;
    }

    printf("\nID  BF  Period  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d    %d     %d   %d   %d\n",
               p[i].id, p[i].burst, p[i].period,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

void proportional() {
    printf("\n====== Proportional Scheduling =====\n");

    int total_weight = 0;

    for (int i = 0; i < n; i++) {
        total_weight += p[i].weight;
        p[i].remaining = p[i].burst;
    }

    int time = 0, completed = 0;

    while (completed < n) {
        for (int i = 0; i < n; i++) {

            int share = p[i].weight;

            while (share-- && p[i].remaining > 0) {
                time++;
                p[i].remaining--;

                if (p[i].remaining == 0) {
                    p[i].ct = time;
                    p[i].tat = p[i].ct;
                    p[i].wt = p[i].tat - p[i].burst;
                    completed++;
                    break;
                }
            }
        }
    }

    printf("\nID  BF  Weight  CT  WT  TAT\n");
    for (int i = 0; i < n; i++) {
        printf("%d   %d     %d     %d   %d   %d\n",
               p[i].id, p[i].burst, p[i].weight,
               p[i].ct, p[i].wt, p[i].tat);
    }
}

int main() {
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("\nEnter process details:\n");

    for (int i = 0; i < n; i++) {
        printf("\nProcess %d:\n", i);

        p[i].id = i;

        printf("Burst Time: ");
        scanf("%d", &p[i].burst);

        printf("Deadline (for EDF): ");
        scanf("%d", &p[i].deadline);

        printf("Period (for RMS): ");
        scanf("%d", &p[i].period);

        printf("Weight (for Proportional): ");
        scanf("%d", &p[i].weight);
    }

    edf();
    rms();
    proportional();

    return 0;
}
