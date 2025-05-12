#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int n,disk_req[20],head,totalhmov=0;
    int finish[20];

    printf("Enter no. of requests: ");
    scanf("%d",&n);

    printf("Enter disk requests: ");
    for(int i=0;i<n;i++){
        scanf("%d",&disk_req[i]);
        finish[i]=0;
    }

    printf("Enter head: ");
    scanf("%d",&head);

    printf("%d ",head);

    for(int i=0;i<n;i++){
        int min=INT_MAX;
        int pos=-1;

        for(int j=0;j<n;j++){
            if(finish[j]==0 && abs(head-disk_req[j])<min){
                min=abs(head-disk_req[i]);
                pos=j;
            }
        }

        finish[pos]=1;
        totalhmov+=abs(head-disk_req[i]);
        head=disk_req[pos];
        printf("%d ",head);
    }
    return 0;
}

/*
same initialization but add a finish array and initilise to 0
here 2 for loops will be require, 1st to travel every disk req, second to find the min seek time
for this inside 1st loop maintain min and its position, 2nd loop then after 2nd loop same everything as did in fcfs 
i mean totalhmov+= then head updation and printing.
*/