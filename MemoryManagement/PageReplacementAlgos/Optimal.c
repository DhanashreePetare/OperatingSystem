#include<stdio.h>
#include<stdlib.h>

int main(){

    int np,nf,p[30],f[10],pos,flag1,flag2;
    int pagefaults=0,hit=0;

    printf("Enter number of pages & number of frames: ");
    scanf("%d %d", &np, &nf);

    printf("Enter the page reference string: ");
    for (int i = 0; i < np; i++) {
        scanf("%d", &p[i]);
    }

    for(int i=0;i<nf;i++){
        f[i]=-1;
    }

    for(int i=0;i<np;i++){
        flag1=flag2=0;

        for(int j=0;j<nf;j++){
            if(f[j]==p[i]){
                flag1=flag2=1;
                hit++;
                break;
            }
        }

        if(flag1==0){
            for(int j=0;j<nf;j++){
                if(f[j]==-1){
                    f[j]=p[i];
                    pagefaults++;
                    flag2=1;
                    break;
                }
            }
        }

        if(flag2==0){
            int farthest=-1,index=-1;
            for(int j=0;j<nf;j++){
                int next_use=-1;
                for(int k=i+1;k<np;k++){
                    if(p[k]==f[j]){
                        next_use=k;
                        break;
                    }
                }
                if(next_use==-1){
                    index=j;
                    break;
                }
                if(next_use>farthest){
                    farthest=next_use;
                    index=j;
                }
            }
            f[index]=p[i];
            pagefaults++;
        }

         // Show current frame status
         printf("\nFor page %d: ", p[i]);
         for (int j = 0; j < nf; j++) {
             if (f[j] != -1)
                 printf("%d ", f[j]);
             else
                 printf("- ");
         }
     }
 
     printf("\nTotal Page Faults: %d\n", pagefaults);
     return 0;
 }

    
/*
same flag1 flag2 but 
initially if we get , hit; flag1=0=> if we get free frame allocate,
flag2=0=> loop over all the frames and from those pages in frame find the farthest one=>
inside this loop over processes (i+1 to np) and now if found store that index in nextuse;
now 2 conditions=> if we didnt get at all (nextuse=-1) then directly store that index;
if we get then check if it is > then farthest if yes, store index;
finally put process on that index and miss++;
*/