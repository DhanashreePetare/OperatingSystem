#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
int nb,np;
printf("enter no. of blocks and processess: ");
scanf("%d %d",&nb,&np);

int b[nb];
int p[np];

printf("Enter sizes of blocks: ");
for(int i=0;i<nb;i++){
    scanf("%d",&b[i]);
}

printf("Enter sizes of processess: ");
for(int i=0;i<np;i++){
    scanf("%d",&p[i]);
}

int b_flag[nb];
int pinwhichb[np];
int frag[np];

for(int i=0;i<nb;i++){
    b_flag[i]=0;
}

for(int i=0;i<np;i++){
pinwhichb[i]=-1;
frag[i]=0;
}

//algo=>

for(int i=0;i<np;i++){
    int best_idx=-1;
    int largestb=INT_MIN;
    for(int j=0;j<nb;j++){
        if(b_flag[j]==0 && b[j]>=p[i]){
            if(b[j]>largestb){
                best_idx=j;
                largestb=b[j];
            }
        }
    }
    if(best_idx!=-1){
        pinwhichb[i]=best_idx;
        b_flag[best_idx]=1;
        frag[i]=b[best_idx]-p[i];
    }
}

printf("memory management as per Worst Fit:\n");

for(int i=0;i<np;i++){
    if(pinwhichb[i]!=-1){
    printf("process no. %d => ",i+1);
    printf("size: %d ",p[i]);
    printf("allocated block and its size : %d %d ",pinwhichb[i]+1,b[pinwhichb[i]]);
    printf("frag: %d\n ",frag[i]);
    }
    else{
        printf("process no. %d => not allocated\n", i+1);
    }
}

}
