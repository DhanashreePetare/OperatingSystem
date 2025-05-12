#include<stdio.h>
#include<stdlib.h>

int main(){
    int np,nf,p[30],f[30],pos=0,hit=0,miss=0;

    printf("enter number of pages and frames: ");
    scanf("%d %d",&np,&nf);
    printf("enter page reference string: ");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    for(int i=0;i<nf;i++){
        f[i]=-1;
    }

    for(int i=0;i<np;i++){
        int flag=0;
        for(int j=0;j<nf;j++){
            if(f[j]==p[i]){
                flag=1;
                hit++;
                break;
            }
        }
        if(flag==0){
            f[pos]=p[i];
            miss++;
            pos=(pos+1)%nf;
        }

        for(int k=0;k<nf;k++){
            printf("%d ",f[k]);
        }
        printf("\n");
    }

    float missr=(miss/(float)(np))*100;
    float hitr=(hit/(float)(np))*100;

    printf("\n");     
    printf("no. of fault = %d", miss);     
    printf("\n");     
    printf("no. of hits= %d", hit);     
    printf("\n");     
    printf("hit ratio = %f",hitr);     
    printf("\n");     
    printf("miss ratio = %f", missr ); 
    
    return 0;
}