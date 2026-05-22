#include<stdio.h>

struct process{
    int pid, at, bt, pr, ct, tat, wt, rt, rbt, started;
};

int main(){

    int n,i,time=0,completed=0,highest;
    float avg_wt=0,avg_tat=0,avg_rt=0;

    struct process p[20];

    printf("Enter number of processes: ");
    scanf("%d",&n);

    for(i=0;i<n;i++){
        p[i].pid=i+1;
        printf("Enter at and bt and priority for P%d: ",p[i].pid);
        scanf("%d%d%d",&p[i].at,&p[i].bt,&p[i].pr);

        p[i].rbt=p[i].bt;
        p[i].started=0;
    }

    while(completed<n){

        highest=-1;

        for(i=0;i<n;i++){
            if(p[i].at<=time && p[i].rbt>0){
                if(highest==-1 || p[i].pr < p[highest].pr){
                    highest=i;
                }
            }
        }

        if(highest==-1){
            time++;
        }
        else{

            if(p[highest].started==0){
                p[highest].rt = time - p[highest].at;
                p[highest].started=1;
            }

            p[highest].rbt--;
            time++;

            if(p[highest].rbt==0){

                p[highest].ct=time;

                p[highest].tat=p[highest].ct-p[highest].at;

                p[highest].wt=p[highest].tat-p[highest].bt;

                avg_wt+=p[highest].wt;
                avg_tat+=p[highest].tat;
                avg_rt+=p[highest].rt;

                completed++;
            }
        }
    }

    printf("\npid\tat\tbt\tpr\tct\ttat\twt\trt\n");


    for(i=0;i<n;i++){
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
        p[i].pid,
        p[i].at,
        p[i].bt,
        p[i].pr,
        p[i].ct,
        p[i].tat,
        p[i].wt,
        p[i].rt);
    }

    printf("\nAverage TAT = %.2f",avg_tat/n);
    printf("\nAverage WT  = %.2f",avg_wt/n);
    printf("\nAverage RT  = %.2f\n",avg_rt/n);

    return 0;
}
