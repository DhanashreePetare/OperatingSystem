#include<stdio.h>

int main(){
    int np,nf,p[30],f[30],hit=0,miss=0;
    printf("enter number of processes & number of frames: ");
    scanf("%d %d",&np,&nf);
    printf("enter the page ref string: ");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    for(int i=0;i<nf;i++){
        f[i]=-1;
    }

    //algo
    for(int i=0;i<np;i++){
        int flag1=0,flag2=0;

        for(int j=0;j<nf;j++){
            if(p[i]==f[j]){
                flag1=flag2=1;
                hit++;
                break;
            }
        }
        if(flag1==0){
            for(int j=0;j<nf;j++){
                if(f[i]==-1){
                    f[i]=p[i];
                    miss++;
                    flag2=1;
                    break;
                }
            }
        }
        if(flag2==0){
            int farthest=-1,index=-1;
            for(int j=0;j<nf;j++){
                int next_used=-1;
                for(int k=i+1;k<np;k++){
                    if(f[j]==p[k]){
                        next_used=k;
                        break;
                    }
                }
                if(next_used==-1){
                    index=j;
                    break;
                }
                if(next_used>farthest){
                    farthest=next_used;
                    index=j;
                }
            }
            f[index]=p[i];
            miss++;
        }

        printf("\nFor process %d:\n",p[i]);
        for(int k=0;k<nf;k++){
            if (f[k] != -1)
                 printf("%d ", f[k]);
             else
                 printf("- ");
        }
    }
    printf("\nTotal Page Faults: %d\n", miss);
     return 0;

}