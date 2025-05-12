#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int n,disk_req[200],head,totalhmov=0;
    int finish[200];

    printf("Enter no. of requests: ");
    scanf("%d",&n);

    printf("Enter content of disk_req: ");
    for(int i=0;i<n;i++){
        scanf("%d",&disk_req[i]);
        finish[i]=0;
    }

    printf("head : ");
    scanf("%d", &head);

    for(int i=0;i<n;i++){
        int min=INT_MAX;
        int pos=-1;

        for(int j=0;j<n;j++){
            if(!finish[j] && abs(head-disk_req[j])<min){
                min=abs(head-disk_req[j]);
                pos=j;

            }
        }

        finish[pos]=1;
        totalhmov+=abs(head-disk_req[pos]);
        head=disk_req[pos];
        printf("%d ",head);
    }
    printf("totalhmove = %d",totalhmov);
    return 0;
}