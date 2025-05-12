#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,disk_req[20],head,totalheadmov=0;

    printf("Enter no. of requests: ");
    scanf("%d",&n);

    printf("Enter disk requests: ");
    for(int i=0;i<n;i++){
        scanf("%d",&disk_req[i]);
    }

    printf("Enter head: ");
    scanf("%d",&head);

    printf("%d ",head);
    for(int i=0;i<n;i++){
        totalheadmov+=abs(head-disk_req[i]);
        head=disk_req[i];
        printf("%d ",head);
    }
    return 0;
}

