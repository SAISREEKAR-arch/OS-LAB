#include<stdio.h>

struct process{
    int pid, at, bt, ct, tat, wt, rt;
};

int main(){
    int n, i, time = 0, remain, tq, done;
    float avg_wt=0, avg_tat=0;

    struct process p[20];

    printf("enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        p[i].pid = i+1;
        printf("enter at and bt for P%d: ",p[i].pid);
        scanf("%d %d",&p[i].at,&p[i].bt);
        p[i].rt = p[i].bt;
    }

    printf("enter time quantum: ");
    scanf("%d",&tq);

    remain = n;

    while(remain != 0){
        done = 1;

        for(i = 0; i < n; i++){
            if(p[i].rt > 0 && p[i].at <= time){
                done = 0;

                if(p[i].rt > tq){
                    time += tq;
                    p[i].rt -= tq;
                }
                else{
                    time += p[i].rt;
                    p[i].rt = 0;
                    p[i].ct = time;
                    remain--;
                }
            }
        }

        if(done == 1){
            time++;
        }
    }

    for(i = 0; i < n; i++){
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;

        avg_wt += p[i].wt;
        avg_tat += p[i].tat;
    }

    printf("\npid\tat\tbt\tct\ttat\twt\n");

    for(i = 0; i < n; i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
    }

    printf("\naverage tat = %.2f", avg_tat/n);
    printf("\naverage wt  = %.2f\n", avg_wt/n);

    return 0;
}
