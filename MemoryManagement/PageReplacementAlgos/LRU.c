#include<stdio.h>
#include<stdlib.h>

int main(){
    int np,nf,p[30],f[10],time[10],pos=0,flag1,flag2;
    int cnt=0,pagefaults=0,min=100;

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

    for(int i=0;i<np;i++){
        flag1=0;
        flag2=0;
        //page hit
        for(int j=0;j<nf;j++){
            if(p[i]==f[j]){
                cnt++;
                time[j]=cnt;
                flag1=flag2=1; //next 2 conditions not satisfied.
                break;
            }
        }
        //page fault but free frame
        if(flag1==0){
            for(int j=0;j<nf;j++){
                if(f[j]==-1){
                    f[j]=p[i];
                    pagefaults++,cnt++,time[j]=cnt;
                    flag2=1;
                    break;
                }
            }
        }
        //page fault and RAM full
        if(flag2==0){
            min=time[0];
            for(int j=0;j<nf;j++){
                if(time[j]<min){
                    min=time[j];
                    pos=j;
                }
            }
            f[pos]=p[i];
            cnt++;
            time[pos]=cnt;
            pagefaults++;
        }

        printf("\nFor page %d: ",p[i]);
        for(int j=0;j<nf;j++){
            printf("%d ",f[j]);
        }
    }
    printf("\nTotal Page Faults: %d\n", pagefaults);
    return 0;
}

//np,nf,p[],f[],time[np],cnt,pos=0,flag1,flag2,
//basically 3 conditions: page hit, page miss but free frame, page miss but RAM full.
//when the 3rd condition occur, go to get the min time of a process and replace new with that
