#include<stdio.h>
#include<stdlib.h>

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
int last_allocated=0;

//algo=>

for(int i=0;i<np;i++){
    int j=last_allocated;
    int count=0;
    while(count!=nb){
        if(b_flag[i]==0 && b[j]>=p[i]){
            pinwhichb[i]=j;
            b_flag[j]=1;
            frag[i]=b[j]-p[i];
            last_allocated=(j+1)%nb;
            break;
        }
        j=(j+1)%nb;
        count++;
    }
}

printf("memory management as per Next Fit:\n");

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

//here 2nd loop you need to start from where you left so maintain lastused and now 
// we straightforward are not iterating till np , we are strting from where left so
// we need to maintain count and 2nd loop will loop till count =nb;