#include<stdio.h>

int main(){
    printf("enter no. of processes and blocks: ");
    int np,nb;
    scanf("%d %d",&np,&nb);

    printf("enter size of blocks: ");
    int b[nb];
    for(int i=0;i<nb;i++){
        scanf("%d",&b[i]);
    }

    printf("enter size of processes: ");
    int p[np];
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }

    int bflag[nb];
    int pinwhichb[np];
    int frag[np];

    int lastblock=-1;

      for(int i=0;i<np;i++){
        pinwhichb[i]=-1;
        frag[i]=0;
    }
    for(int i=0;i<nb;i++){
        bflag[i]=0;
    }

    //algo
    for(int i=0;i<np;i++){
        int j=lastblock;
        int count=0;
        while(count!=nb){
            if(bflag[j]==0 && b[j]>=p[i]){
                pinwhichb[i]=j;
                bflag[j]=1;
                frag[i]=b[j]-p[i];
                lastblock=(j+1)%nb;
                break;
            }
            j=(j+1)%nb;
            count++;
        }
    }

    printf("Memory Allocation: \n");
    for(int i=0;i<np;i++){
        if(pinwhichb[i]!=-1){
        printf("processid:%d\t",i+1);
        printf("size:%d\t",p[i]);
        printf("allocated block and its size :%d %d \t",pinwhichb[i],b[pinwhichb[i]]);
        printf("frag:%d",frag[i]);
        }
        else{
            printf("process not allocated");
        }
        printf("\n");
    }

return 0;


}