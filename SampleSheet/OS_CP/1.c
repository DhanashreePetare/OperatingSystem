#include<stdio.h>
#include<limits.h>
#include<stdlib.h>


int main(){
    int np,nr,all[10][10],max[10][10],ava[10],need[10][10];
    int safeseq[10],finish[10],flag,k=0;

    printf("Enter number of processes: ");
    scanf("%d", &np);
    printf("Enter number of resources: ");
    scanf("%d", &nr);

    printf("\nEnter allocation matrix (%d x %d):\n",np,nr);
for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
        scanf("%d",&all[i][j]);
    }
}

printf("\nEnter maximum matrix (%d x %d):\n",np,nr);
for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
        scanf("%d",&max[i][j]);
    }
}
printf("\nEnter available resources (%d values): ", nr);
for(int i=0;i<nr;i++){
    scanf("%d",&ava[i]);
}

for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = max[i][j] - all[i][j];


for(int i=0;i<np;i++){
    finish[i]=0;
}

for(int i=0;i<np;i++){
    int flag=0;
    if(finish[i]==0){
        for(int j=0;j<nr;j++){
            if(need[i][j]>ava[j]){
                flag=1;
                break;
            }
        }
        if(flag=0){
            for(int j=0;j<nr;j++){
                ava[j]+=all[i][j];
            }
            finish[i]=1;
            safeseq[k++]=i;
            i=-1;
        }
    }
}

for(int i=0;i<np;i++){
    if(finish[i]==0){
        flag=1;
        break;
    }
}

if(flag==1){
    printf("\nDeadlock occured!.\n");
}
else{
    printf("\nSystem is in safe state.\n");
    for(int i=0;i<np;i++){
        printf("P%d ",safeseq[i]);
    }
    printf("\n");
}

    return 0;
}