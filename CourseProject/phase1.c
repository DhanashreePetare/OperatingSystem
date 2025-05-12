#include<stdio.h>
#include<string.h>
FILE *Input, *Output;

#define buffsize 40
#define irSize 4
#define memSize 100
#define resSize 4


char buffer[buffsize];
int IC;
char Memory[memSize][irSize];
char IR[irSize];
int R[resSize];
int C;
int SI;


void clearBuffer(){
for(int i=0;i<buffsize;i++){
    buffer[i]='\0';
}
}

void INIT(){
    for(int i=0;i<memSize;i++){
        for(int j=0;j<irSize;j++){
            Memory[i][j]='\0';
        }
    }
    for(int i=0;i<irSize;i++){
        IR[i]='\0';
    }
    for(int i=0;i<irSize;i++){
        R[i]=0;
    }
    C=0;
    IC=0;
    printf("[INFO] System Initialized.\n");
}

int GETLOCATION(){
    return ((IR[2]-'0')*10)+(IR[3]-'0');
}

void TERMINATE(){
    fprintf(Output,"\n");
    printf("Programe terminated.\n");
}

void READ(){
    clearBuffer();
    int i=0;
    char ch;
    while((ch=fgetc(Input)) !='\n' && i<buffsize){
        buffer[i++]=ch;
    }

    int loc=GETLOCATION();
    for(int j=0;j<i;j++){
        Memory[loc][j%irSize]=buffer[j];
        if((j%irSize)==irSize-1){
            loc++;
        }
    }
    printf("Read complete to location starting at %d.\n",GETLOCATION());
}

void WRITE(){
    clearBuffer();
    int loc=GETLOCATION();
    int stop=((loc/10)+1)*10; 
    for(int i=loc;i<stop;i++){
        for(int j=0;j<4;j++){
            if(Memory[i][j]!='\0'){
                fprintf(Output,"%c",Memory[i][j]);
            }
        }
    }
    fprintf(Output,"\n");
    printf("WRITE from location %d complete.\n",loc);
}



void MOS(){
    switch (SI){
    case 1:
        READ();
        break;
    case 2:
        WRITE();
        break;
    case 3:
        TERMINATE();
        break;
    default:
        printf("Invalid SI value.\n");
        break;
    }
}

void STARTEXECUTION(){
    IC=0;
    printf("Execution Started.\n");

    while(1){
        for(int i=0;i<4;i++){
            IR[i]=Memory[IC][i];
        }

        printf("IR = %.4s, IC = %d\n",IR,IC);
        IC++;

        if(IR[0]=='G' && IR[1]=='D') SI=1, MOS();
        else if(IR[0] == 'P' && IR[1] == 'D') SI = 2, MOS();
        else if (IR[0] == 'H'){
            SI=3;
            MOS();
            break;
        }
        else if(IR[0] == 'L' && IR[1] == 'R'){
            int loc=GETLOCATION();
            for(int i=0;i<4;i++){
                R[i]=Memory[loc][i];
            }
        }
        else if(IR[0] == 'S' && IR[1] == 'R'){
            int loc=GETLOCATION();

            printf("====LOCATION SR %d====\n",loc);
            printf("[MEMORY]: %c%c%c%c \n", Memory[loc][0],Memory[loc][1],Memory[loc][2],Memory[loc][3]);
            for(int i=0;i<4;i++){
                Memory[loc][i]=R[i];
            }
            printf("[REG] R: %c%c%c%c | C: %d\n", R[0],R[1],R[2],R[3],C);
        }
        else if(IR[0] == 'C' && IR[1] == 'R'){
            int loc=GETLOCATION();
            C=1;
            for(int i=0;i<4;i++){
                if(Memory[loc][i]!=R[i]){
                    C=0;
                    break;
                }
            }
        }
        else if(IR[0] == 'B' && IR[1] == 'T'){
            if(C!=0){
                int loc=GETLOCATION();
                IC=loc;
                printf("Branching to location %d.\n",loc);
            }
        }
        else{
            printf("[ERROR] Unknown instruction %.4s\n", IR);
        }
    }
}

void LOAD(){
    printf("[INFO] Loading started.\n");
    clearBuffer();
    char ch;
    int i=0,flag=0;

    while((ch=fgetc(Input))!=EOF && IC!=100){
        if(ch!='\n')
        buffer[i++]=ch;
        else{
            buffer[i]='\0';

            i=0;

            if(strncmp(buffer,"$AMJ",4)==0){
                INIT();
                continue;
            }
            else if(strncmp(buffer,"$DTA",4)==0){
                flag=1;
                STARTEXECUTION();
                continue;
            }
            else if(strncmp(buffer,"$END",4)==0){
                flag=0;
                continue;
            }

            if(flag==0){
                for(int j=0;buffer[j]!='\0';j++){
                    Memory[IC][j%irSize]=buffer[j];

                    if((j%irSize)==irSize-1) IC++;
                }
            }
            clearBuffer();
        }
    }
    printf("[INFO] Loading complete.\n");
}

int main(){
    Input=fopen("input2.txt","r");
    if(Input==NULL){
        printf("[ERROR] could not open input file.\n");
        return 0;
    }
    Output=fopen("output3.txt","a");
    if(Output==NULL){
        printf("[Error] Could not open output file.\n");
        return 0;
    }

    LOAD();
    for(int i=0;i<100;i++){
        printf("M[%d]:%c%c%c%c\n",i,Memory[i][0],Memory[i][1],Memory[i][2],Memory[i][3]);
    }
    fclose(Input);
    fclose(Output);
    return 0;
}