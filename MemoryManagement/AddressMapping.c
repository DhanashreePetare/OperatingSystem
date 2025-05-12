#include<stdio.h>
#include<stdlib.h>
#include<limits.h>

int main(){
    int npages,pagesize,pagenum,framenum,offset;
    int ladd,padd;
    int pagetable[10];

    printf("enter number of pages: ");
    scanf("%d",&npages);
    
    printf("enter page size: ");
    scanf("%d",&pagesize);

    printf("enter the page table (frame number for page number): ");
    for(int i=0;i<npages;i++){
        printf("Page %d → Frame: ", i);         
        scanf("%d", &pagetable[i]); 
    }

    printf("Enter logical address: ");     
    scanf("%d", &ladd); 

    pagenum=ladd/pagesize;
    offset=ladd%pagesize;

    if(pagenum>=npages){
        printf("Invalid logical address!\n"); 
        return 1;
    }

    framenum=pagetable[pagenum];
    padd=(framenum*pagesize)+offset;

    printf("\nLogical Address: %d", ladd); 
    printf("\nPage Number: %d", pagenum); 
    printf("\nOffset: %d", offset); 
    printf("\nFrame Number: %d", framenum); 
    printf("\nPhysical Address: %d\n", padd); 

    return 0;

    
}

//npage,pagesize,pagenum,framenum,pagetable[10],offset,ladd,padd;
//pagenum=ladd/pagesize;
//offset=ladd%pagesize;
//framenum=pagetable[pagenum];
//padd=(framenum*pagesize)+offset;