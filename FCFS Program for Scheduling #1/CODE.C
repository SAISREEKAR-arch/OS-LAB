//FCFS
#include <stdio.h>

int main() {
int n;
printf("Enter number of processes: ");
scanf("%d", &n);

int pid[n], at[n], bt[n], ct[n], tat[n], wt[n];

for(int i = 0; i < n; i++) {
    printf("\nProcess %d\n", i+1);
    pid[i] = i+1;
    printf("Arrival Time: ");
    scanf("%d", &at[i]);
    printf("Burst Time: ");
    scanf("%d", &bt[i]);
}


for(int i = 0; i < n-1; i++) {
    for(int j = i+1; j < n; j++) {
        if(at[i] > at[j]) {

            int temp = at[i];
            at[i] = at[j];
            at[j] = temp;


            temp = bt[i];
            bt[i] = bt[j];
            bt[j] = temp;

            temp = pid[i];
            pid[i] = pid[j];
            pid[j] = temp;
        }
    }
}

ct[0] = at[0] + bt[0];

for(int i = 1; i < n; i++) {
    if(ct[i-1] < at[i])
        ct[i] = at[i] + bt[i];
    else
        ct[i] = ct[i-1] + bt[i];
}

for(int i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];
}

printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
for(int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", pid[i], at[i], bt[i], ct[i], tat[i], wt[i]);
}

double tatsum=0;
double wtsum=0;
for(int i = 0; i < n; i++) {
    tat[i] = ct[i] - at[i];
    wt[i] = tat[i] - bt[i];
    tatsum+=tat[i];
    wtsum+=wt[i];
}
double tatavg=tatsum/n;
double wtavg=wtsum/n;
printf("Average TAT: %f", tatavg);
printf("\nAverage WT: %f", wtavg);
return 0;
}


