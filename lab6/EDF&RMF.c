#include <stdio.h>

#define MAX 10

typedef struct {
    int id;
    int execution;
    int period;
    int deadline;
    int remaining;
    int completion;
} Task;

void edf(Task t[], int n) {
    printf("\n===== Earliest Deadline First (EDF) Scheduling =====\n");
    printf("ID\tBT\tDeadline\tCT\tWT\tTAT\n");

    int time = 0, completed = 0;
    int deadlines[MAX];

    for (int i = 0; i < n; i++) {
        t[i].remaining = t[i].execution;
        deadlines[i] = t[i].deadline;
    }

    while (completed < n) {
        int earliest = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0 && deadlines[i] < earliest) {
                earliest = deadlines[i];
                selected = i;
            }
        }

        if (selected != -1) {
            t[selected].remaining--;

            if (t[selected].remaining == 0) {
                t[selected].completion = time + 1;
                completed++;
            }
        }
        time++;
    }

    for (int i = 0; i < n; i++) {
        int tat = t[i].completion;
        int wt = tat - t[i].execution;

        printf("%d\t%d\t%d\t\t%d\t%d\t%d\n",
               t[i].id, t[i].execution, t[i].deadline,
               t[i].completion, wt, tat);
    }
}

void rms(Task t[], int n) {
    printf("\n===== Rate Monotonic Scheduling (RMS) =====\n");
    printf("ID\tBT\tPeriod\tCT\tWT\tTAT\n");

    int time = 0, completed = 0;

    for (int i = 0; i < n; i++) {
        t[i].remaining = t[i].execution;
    }

    while (completed < n) {
        int min_period = 9999, selected = -1;

        for (int i = 0; i < n; i++) {
            if (t[i].remaining > 0 && t[i].period < min_period) {
                min_period = t[i].period;
                selected = i;
            }
        }

        if (selected != -1) {
            t[selected].remaining--;

            if (t[selected].remaining == 0) {
                t[selected].completion = time + 1;
                completed++;
            }
        }
        time++;
    }

    for (int i = 0; i < n; i++) {
        int tat = t[i].completion;
        int wt = tat - t[i].execution;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               t[i].id, t[i].execution, t[i].period,
               t[i].completion, wt, tat);
    }
}

void proportional(Task t[], int n) {
    printf("\n===== Proportional Share Scheduling =====\n");
    printf("ID\tBT\tShare\tCT\tWT\tTAT\n");

    int total = 0;

    for (int i = 0; i < n; i++)
        total += t[i].execution;

    int time = 0;

    for (int i = 0; i < n; i++) {
        t[i].completion = time + t[i].execution;
        time += t[i].execution;
    }

    for (int i = 0; i < n; i++) {
        int tat = t[i].completion;
        int wt = tat - t[i].execution;
        int share = (t[i].execution * 100) / total;

        printf("%d\t%d\t%d\t%d\t%d\t%d\n",
               t[i].id, t[i].execution, share,
               t[i].completion, wt, tat);
    }
}

int main() {
    int n;
    Task t[MAX];

    printf("Enter number of tasks: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("\nTask %d\n", i + 1);
        t[i].id = i + 1;

        printf("Execution time: ");
        scanf("%d", &t[i].execution);

        printf("Period: ");
        scanf("%d", &t[i].period);

        printf("Deadline: ");
        scanf("%d", &t[i].deadline);
    }

    edf(t, n);
    rms(t, n);
    proportional(t, n);

    return 0;
}
