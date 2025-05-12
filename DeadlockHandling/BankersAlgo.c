#include<stdio.h>
#define maxSize 10

int main(){
int np;
int nr;
int allocation[maxSize][maxSize];
int max[maxSize][maxSize];
int need[maxSize][maxSize];
int available[maxSize];
int flag;
int finish[maxSize];
int safeSeq[maxSize];
int k = 0;

printf("Enter number of processes: ");
scanf("%d", &np);
printf("Enter number of resources: ");
scanf("%d", &nr);


printf("\nEnter allocation matrix (%d x %d):\n",np,nr);
for(int i=0;i<np;i++){
    for(int j=0;j<nr;j++){
        scanf("%d",&allocation[i][j]);
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
    scanf("%d",&available[i]);
}

for (int i = 0; i < np; i++)
        for (int j = 0; j < nr; j++)
            need[i][j] = max[i][j] - allocation[i][j];


for(int i=0;i<np;i++){
    finish[i]=0;
}

for(int i=0;i<np;i++){
    flag=0;
    if(finish[i]==0){
        for(int j=0;j<nr;j++){
            if(need[i][j]>available[j]){
                flag=1;
                break;
            }
        }

        if(flag==0){
            for(int j=0;j<nr;j++){
                available[j]+=allocation[i][j];
            }
            finish[i]=1;
            safeSeq[k++]=i;
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
        printf("P%d ",safeSeq[i]);
    }
    printf("\n");
}

return 0;
}
