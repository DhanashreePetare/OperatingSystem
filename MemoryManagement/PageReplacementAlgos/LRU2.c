#include<stdio.h>
#include<stdlib.h>

int main(){
    int np,nf,p[30],f[30],pos=0,time[30],cnt=0,hit=0,miss=0;

    printf("enter number of processes & number of frames: ");
    scanf("%d %d",&np,&nf);
    printf("enter the page ref string: ");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    for(int i=0;i<nf;i++){
        f[i]=-1;
        time[i]=0;
    }

    //algo
    for(int i=0;i<np;i++){
        int flag1=0,flag2=0;
        for(int j=0;j<nf;j++){
            if(f[j]==p[i]){
                cnt++;
                time[j]=cnt;
                hit++;
                flag1=flag2=1;
                break;
            }
        }
        if(flag1==0){
            for(int j=0;j<nf;j++){
                if(f[j]==-1){
                    f[j]=p[i];
                    cnt++;
                    time[j]=cnt;
                    flag2=1;
                    break;
                }
            }
        }
        if(flag2==0){
            int min=time[0];
            for(int j=0;j<nf;j++){
                if(time[j]<min){
                    min=time[j];
                    pos=j;
                }
            }
            f[pos]=p[i];
            cnt++;
            time[pos]=cnt;
            miss++;
        }
         printf("\nFor page %d: ",p[i]);
        for(int j=0;j<nf;j++){
            printf("%d ",f[j]);
        }
    }
    printf("\nTotal Page Faults: %d\n", miss);
    return 0;
        
    
}