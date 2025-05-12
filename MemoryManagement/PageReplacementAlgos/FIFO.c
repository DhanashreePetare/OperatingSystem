#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int np,nf,p[30],f[30],pos=0,hit=0,fault=0,flag;

    printf("enter number of processes & number of frames: ");
    scanf("%d %d",&np,&nf);
    printf("enter the page ref string: ");
    for(int i=0;i<np;i++){
        scanf("%d",&p[i]);
    }
    for(int i=0;i<nf;i++){
        f[i]=-1;
    }

    for(int i=0;i<np;i++){
        flag=0;
        for(int j=0;j<nf;j++){
            if(p[i]==f[j]){
                //hit
                flag=1;
                hit++;
                break;
            }
        }
        if(flag==0){
            //fault
            fault++;
            f[pos]=p[i];
            pos=(pos+1)%nf;
        }

        //display
    for(int i=0;i<nf;i++){
        printf("%d ",f[i]);
    }
    printf("\n");
    }

    float missr=(fault/(float)(np))*100;
    float hitr=(hit/(float)(np))*100;

    printf("\n");     
    printf("no. of fault = %d", fault);     
    printf("\n");     
    printf("no. of hits= %d", hit);     
    printf("\n");     
    printf("hit ratio = %f",hitr);     
    printf("\n");     
    printf("miss ratio = %f", missr ); 
    
    return 0;
}

//np,nf,prefstrig->p[30],f[30],fit,miss,pos=0(for assigning frame).
//loop for all process and set flag=0(to detect this particular process face  hit or miss)
//loop through frames and check for hit or miss, if hit,flag=1,break, if miss,f[pos]=page and pos++(circular way);
