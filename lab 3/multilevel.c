#include <stdio.h>
#include <string.h>

#define MAX 50

struct process {
    int pid;
    int at, bt, rt, ct, tat, wt;
    int type;
};

struct queue {
    int items[MAX];
    int front, rear;
};

void initQueue(struct queue *q) {
    q->front = q->rear = -1;
}

int isEmpty(struct queue *q) {
    return (q->front == -1);
}

void enqueue(struct queue *q, int val) {
    if (q->rear == MAX - 1) return;
    if (q->front == -1) q->front = 0;
    q->items[++q->rear] = val;
}

int dequeue(struct queue *q) {
    if (isEmpty(q)) return -1;
    int val = q->items[q->front];
    if (q->front == q->rear)
        q->front = q->rear = -1;
    else
        q->front++;
    return val;
}

void sort(struct process p[], int n) {
    struct process temp;
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (p[j].at > p[j+1].at) {
                temp = p[j];
                p[j] = p[j+1];
                p[j+1] = temp;
            }
        }
    }
}

int main() {
    int n;
    struct process p[MAX];

    printf("Enter number of processes: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        p[i].pid = i;
        printf("\nProcess %d\n", i);
        printf("Enter arrival time: ");
        scanf("%d", &p[i].at);
        printf("Enter burst time: ");
        scanf("%d", &p[i].bt);
        printf("Enter type (0 = System, 1 = User): ");
        scanf("%d", &p[i].type);

        p[i].rt = p[i].bt;
    }

    sort(p, n);

    struct queue systemQ, userQ;
    initQueue(&systemQ);
    initQueue(&userQ);

    int time = 0, completed = 0, i = 0;
    int current = -1;

    while (completed < n) {

        while (i < n && p[i].at <= time) {
            if (p[i].type == 0)
                enqueue(&systemQ, i);
            else
                enqueue(&userQ, i);
            i++;
        }

        if (current != -1) {
            if (p[current].type == 1 && !isEmpty(&systemQ)) {
                enqueue(&userQ, current);
                current = -1;
            }
        }

        if (current == -1) {
            if (!isEmpty(&systemQ))
                current = dequeue(&systemQ);
            else if (!isEmpty(&userQ))
                current = dequeue(&userQ);
            else {
                time++;
                continue;
            }
        }

        p[current].rt--;
        time++;

        if (p[current].rt == 0) {
            p[current].ct = time;
            completed++;
            current = -1;
        }
    }

    float avg_wt = 0, avg_tat = 0;

    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\nID\tType\tAT\tBT\tCT\tWT\tTAT\n");

    for (int i = 0; i < n; i++) {
        printf("%d\t%s\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               (p[i].type == 0) ? "System" : "User",
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].wt,
               p[i].tat);
    }

    printf("\nAverage Waiting Time: %.2f", avg_wt/n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_tat/n);

    return 0;
}
