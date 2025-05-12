#include<stdio.h>
#include<stdlib.h>

int main(){
    int n,disk_req[200],head,totalhmov=0;

    printf("Enter no. of requests: ");
    scanf("%d",&n);

    printf("Enter content of disk_req: ");
    for(int i=0;i<n;i++){
        scanf("%d",&disk_req[i]);
    }

    printf("head : ");
    scanf("%d", &head);

    printf("%d ",head);
    for(int i=0;i<n;i++){
        totalhmov+=abs(head-disk_req[i]);
        head=disk_req[i];
        printf("%d ",head);
    }
    printf("\nTotal head movements = %d\n", totalhmov);
    return 0;
}

/*
n,disk_req[],head(3 inputs), totalhmov=0;
simply traverse through array and add totalhmov and update head
print head
finally print total head movemnt 
*/