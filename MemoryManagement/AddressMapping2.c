#include<stdio.h>
#include<stdlib.h>

int main(){
    int npages,framenum,pagesize,pagetable[10],pagenum,framenum,ladd,offset;
    int physicaladd;

    printf("enter number of pages: ");
    scanf("%d",&npages);

    printf("enter size of pages: ");
    scanf("%d",&pagesize);

    printf("enter pagetable: ");
    for(int i=0;i<npages;i++){
        printf("fame for page %d:",i+1);
        scanf("%d",&pagetable[i]);
    }
    printf("Enter logical address: ");
    scanf("%d",&ladd);

    pagenum=ladd/pagesize;
    offset=ladd%pagesize;

    if(pagenum>=npages){
        printf("Invalid logical address;\n");
        return 1;
    }

    framenum=pagetable[pagenum];
    physicaladd=(framenum*pagesize)+offset;

    printf("Physical Address = %d",physicaladd);
    return 0;

}