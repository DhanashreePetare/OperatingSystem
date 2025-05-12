#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

FILE *Input, *Output;

#define irSize 4
#define memSize 300
#define resSize 4
#define buffSize 40
#define noFrame 30
#define framesize 10

char Memory[memSize][irSize];
char IR[irSize];
int IC;
int R[resSize];
int C;
int SI;
int TI;
int PI;
char buffer[buffSize];
int PageTabelPointer;
int TTC,LLC;
int TTL,TLL;
int jobid[4];
int programCount;
int terminateProgram;
int count;


void LOAD();
void INIT();
void EXECUTEUSERPROGRAM();
void STARTEXECUTION();
void MOS();
void TERMINATE(int );
void READ(int);
void WRITE();
int CHECK(int);
int Present_in_PageTable(int);
int GETLOCATION();
void clearBuffer();
int getRandomValue();



int getRandomValue()
{
    static unsigned int seed = 12345; // Fixed seed for reproducibility
    seed = (1103515245 * seed + 12345) % 2147483648; // Linear congruential generator
    return seed % noFrame;
}

void clearBuffer()
{
    for (int i = 0; i < buffSize; i++)
        buffer[i] = '\0';
}

void INIT()
{
    for (int i = 0; i < memSize; i++)
        for (int j = 0; j < irSize; j++)
            Memory[i][j] = '\0';

    for (int i = 0; i < irSize; i++)
        IR[i] = '\0';

    for (int i = 0; i < resSize; i++)
        R[i] = 0;

    C = 0;
    IC = 0;
    TTC = 0;
    LLC = 0;

    SI = 0;
    TI = 0;
    PI = 0;

    jobid[0] = buffer[4];
    jobid[1] = buffer[5];
    jobid[2] = buffer[6];
    jobid[3] = buffer[7];
    
    TTL = buffer[11] - '0';
    TTL += (buffer[10] - '0') * 10;
    TTL += (buffer[9] - '0') * 100;
    TTL += (buffer[8] - '0') * 1000;
    TLL = buffer[15] - '0';
    TLL += (buffer[14] - '0') * 10;
    TLL += (buffer[13] - '0') * 100;
    TLL += (buffer[12] - '0') * 1000;
    
    PageTabelPointer = getRandomValue();

    programCount = -1;
    printf("[INFO] System initialized.\n");
}


int GETLOCATION()
{
    return ((IR[2] - '0') * 10) + (IR[3] - '0');
}

int Present_in_PageTable(int frame)
{
    int pagetable = PageTabelPointer * 10;
    int ones = frame % 10;
    int tens = '\0';
    if (frame / 10 != 0)
    {
        tens = frame / 10;
    }

    for (int i = 0; i < 10; i++)
    {
        if (Memory[pagetable + i][0] == ones && Memory[pagetable + i][1] == tens)
        {
            return 1;
        }
    }
    return 0;
}

int CHECK(int virtualAdd)
{
    int PageTableStart = PageTabelPointer * 10;
    
    int page_number = virtualAdd / 10;

    if (Memory[PageTableStart + page_number + programCount][0] == '\0' && Memory[PageTableStart + page_number + programCount][1] == '\0')
    {
        return -1;
    }
    
    return (Memory[PageTableStart + page_number + programCount][1] * 10) + Memory[PageTableStart + page_number + programCount][0];
    
}


void READ(int physicalAddress)
{
    clearBuffer();
    physicalAddress = (physicalAddress * 10) + GETLOCATION()%10;
    int i = 0;
    char ch;
    while ((ch = fgetc(Input)) != '\n' && i < buffSize)
        buffer[i++] = ch;  
    for (int j = 0; j < i; j++)
    {
        Memory[physicalAddress][j % irSize] = buffer[j];
        printf("[DEBUG] Buffer = %c\n",buffer[j]);
        if ((j % irSize) == irSize - 1)
            physicalAddress++;
    }
    printf("[INFO] READ complete to location starting at %d.\n", GETLOCATION());
    
    
}

void WRITE()
{
    clearBuffer();
    int loc = CHECK(GETLOCATION());
    loc = loc *10;
    loc = loc + GETLOCATION()%10;
    int stop = ((loc/10)+1)*10;
    for (int i = loc; i < stop; i++)
    {
        for (int k = 0; k < 4; k++)
        {
            if (Memory[i][k] != '\0')
                fprintf(Output, "%c", Memory[i][k]);
            //else
              //   fprintf(Output, " ");
        }
    }
    fprintf(Output, "\n");
    LLC++;
    if (LLC > TLL) {
        TERMINATE(2); 
        return;
    }
    printf("[INFO] WRITE from location %d complete.\n", loc);
}


bool isPageTableFrame(int index) {
    return index >= (PageTabelPointer*10) && index < (PageTabelPointer*10) + 10;
}

void TERMINATE(int EM)
{
    
    switch (EM) {
        case 0:
            printf("==== [INFO]Normal Termination ====\n");
            fprintf(Output, "\n");
            break;
        case 1:
            printf("====[ERROR]: Out of Data ====\n");
            break;
        case 2:
            printf("====[ERROR]: Line Limit Exceeded ====\n");
            break;
        case 3:
            printf("====[ERROR]: Time Limit Exceeded ====\n");
            break;
        case 4:
            printf("====[ERROR]: Operation Code Error ====\n");
            break;
        case 5:
            printf("====[ERROR]: Operand Errorv ====\n");
            break;
        case 6:
            printf("====[ERROR]: Invalid Page Fault ====\n");
            break;
        case 7:
            printf("====[ERROR]: Time Limit + Opcode Error ====\n");
            break;
        case 8:
            printf("====[ERROR]: Time Limit + Operand Error ====\n");
            break;
        default:
            printf("====[ERROR]: Unknown Error Code ==== %d\n", EM);
    }
    printf("====[INFO] Program terminated.====\n\n\n");
    for (int i = 0; i < memSize; i++)
    {
        if (isPageTableFrame(i))
        {
            printf("M[%d]:%d%d%c%c\n", i, Memory[i][0], Memory[i][1], Memory[i][2], Memory[i][3]);
        }
        else {
            printf("M[%d]:%c%c%c%c\n", i, Memory[i][0], Memory[i][1], Memory[i][2], Memory[i][3]);
        }
        
        
    }
    terminateProgram = 1;
}

void MOS() {
    if (TI == 0) {
        if (SI == 1) {
            int available = CHECK(GETLOCATION());
            if (available == -1)
            {
                printf("=== [ERROR] VALID PAGE FAULT ===\n");
                int freeframe;
                int repeat = 1;
                do
                {
                    freeframe = getRandomValue();
                    if (freeframe == PageTabelPointer)
                    {
                        printf("[INFO] Frame %d is already in use. Trying again...\n", freeframe);
                        repeat = 1;
                    }
                    else if (Present_in_PageTable(freeframe))
                    {
                        printf("[INFO] Frame %d is already in use. Trying again...\n", freeframe);
                        repeat = 1;
                    }
                    else
                    {
                        repeat = 0;
                        printf("[INFO] Frame %d is free.\n", freeframe);
                    }
                } while (repeat);
                int page_number = GETLOCATION() / 10;
                Memory[PageTabelPointer * 10 + programCount + page_number][0] = freeframe % 10 ;
                Memory[PageTabelPointer * 10 + programCount +page_number][1] = freeframe / 10 ;
                printf("[INFO] Page Table updated.\n");
                printf("[DEBUG] PAGE TABEL:\n");
                for (int j = 0; j < 10; j++)
                {
                    printf("%c%c ", Memory[PageTabelPointer * 10 + j][0], Memory[PageTabelPointer * 10 + j][1]);
                }
                printf("\n");
                IC--;
                count--;
            }
            else{
                READ(available);
            }
            
        } else if (SI == 2) {
            WRITE();
        } else if (SI == 3) {
            TERMINATE(0); 
        } else if (PI == 1) {
            TERMINATE(4); 
        } else if (PI == 2) {
            TERMINATE(5);
        } else if (PI == 3) {
            TERMINATE(6);
        }
    }

    else if (TI == 2) { 
        if (SI == 1 || SI == 3) {
            TERMINATE(3); 
        }else if (SI == 2){
            WRITE();
            TERMINATE(3);
        } else if (PI == 1) {
            TERMINATE(7); 
        } else if (PI == 2) {
            TERMINATE(8); 
        } else if (PI == 3) {
            TERMINATE(3); 
        }
    }

    SI = 0;
    PI = 0;
    TI = 0;
}


void EXECUTEUSERPROGRAM(){
    terminateProgram = 0;
    count = 0;
    int progno= 0;
    printf("[INFO] Execution started.\n");
    while (!terminateProgram)
    {
        count++;
        if (count > 10)
        {
            progno++;
            printf("[INFO] Program %d executed. COUNT = %d\n", progno,count);
            if (progno > programCount)
            {
                printf("[INFO] All programs executed.\n");
                TERMINATE(0);
            }
            
            count = 0;
            IC = Memory[PageTabelPointer * 10 + progno][1] * 10 + Memory[PageTabelPointer * 10 +progno][0];
            IC = IC *10;
        }
        for (int i = 0; i < 4; i++)
            IR[i] = Memory[IC][i];

        printf("[EXEC] IR = %.4s, IC = %d , COUNT %d\n", IR, IC,count);
        
        IC++;

        if (IR[0] == 'G' && IR[1] == 'D'){
            TTC += 2;
            if (TTC > TTL)
                TI = 2;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2;
                MOS();
                break; 
            }
            SI = 1, MOS();
            
        }  
        else if (IR[0] == 'P' && IR[1] == 'D'){
            TTC += 1;
            if (TTC > TTL)
                TI = 2;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2;
                MOS();
                break;
            }
            int loc = CHECK(GETLOCATION());
            if (loc == -1)
            {
                PI = 3;
                MOS();
                break;
            }
            SI = 2, MOS();
        }   
        
        else if (IR[0] == 'H')
        {
            TTC += 1;
            if (IR[0] == 'H' && (IR[1] != '\0' || IR[2] != '\0' || IR[3] != '\0')) 
            {
                PI = 2,MOS();
                break;
            }   
            if (TTC > TTL)
            {
                TI = 2;
            }    
            SI = 3;
            MOS();
            break;
        }
        else if (IR[0] == 'L' && IR[1] == 'R')
        {
            TTC += 1;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2,MOS();
                break;
            } 
            int available = CHECK(GETLOCATION());
            if (available == -1)
            {
                PI = 3;
                MOS();
                break;
            }
            available = (available * 10) + GETLOCATION()%10;
            printf("[DEBUG] LOCATION LR: %d\n",available);
            for (int i = 0; i < 4; i++)
                R[i] = Memory[available][i];
            printf("[REG] R: %c%c%c%c | C: %d\n", R[0], R[1], R[2], R[3], C);
        }
        else if (IR[0] == 'S' && IR[1] == 'R')
        {
            TTC += 2;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2,MOS();
                break;
            } 
            int loc = CHECK(GETLOCATION());
            if (loc == -1)
            {
                SI = 1;
                MOS();
                continue;
            }
            loc = (loc * 10) + GETLOCATION()%10;
            printf("[DEBUG] LOCATION SR: %d\n",loc);
            printf("[MEMORY]: %c%c%c%c \n", Memory[loc][0],Memory[loc][1],Memory[loc][2],Memory[loc][3]);

            int PageTableStart = PageTabelPointer * 10;
    
            int page_number = GETLOCATION() / 10;
            for (int i = 0; i < 4; i++)
                Memory[loc][i] = R[i];
            printf("[MEMORY]: %c%c%c%c \n", Memory[loc][0],Memory[loc][1],Memory[loc][2],Memory[loc][3]);

        }
        else if (IR[0] == 'C' && IR[1] == 'R')
        {
            TTC += 1;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2,MOS();
                break;
            } 
            int loc = CHECK(GETLOCATION());
            if (loc == -1)
            {
                PI = 3;
                MOS();
                break;
            }
            C = 1;
            loc = (loc * 10) + GETLOCATION()%10;
            printf("[DEBUG] LOCATION CR: %d\n",loc);
            for (int i = 0; i < 4; i++)
            {
                if (Memory[loc][i] != R[i])
                {
                    C = 0;
                    break;
                }
            }
            printf("[REG] R: %c%c%c%c | C: %d\n", R[0], R[1], R[2], R[3], C);
        }
        else if (IR[0] == 'B' && IR[1] == 'T')
        {
            TTC += 1;
            int operand = (IR[2] - '0') * 10 + (IR[3] - '0');
            if (!isdigit(IR[2]) || !isdigit(IR[3]) || operand < 0 || operand >= 100) {
                PI = 2,MOS();
                break;
            }  
            if (C)
            {   int loc;
                if (GETLOCATION()/10 > 0)
                {
                    if (GETLOCATION()/10 > programCount)
                    {
                        printf("[ERROR] Invalid.\n");
                        TERMINATE(0);
                    }
                    progno++;
                    count = 0;
                    loc=Memory[PageTabelPointer * 10 +GETLOCATION()/10][1]*10 + Memory[PageTabelPointer * 10 +GETLOCATION()/10][0];
                    loc = (loc * 10)+ GETLOCATION()%10;
                }
                else{
                    loc = CHECK(GETLOCATION());
                    if (loc == -1)
                    {
                        PI = 3;
                        MOS();
                        break;
                    }
                    loc = (loc * 10) + GETLOCATION()%10;
                }
                IC = loc;
                printf("[INFO] Branching to location %d.\n", IC);
            }
        }
        else
        {
            PI = 1;
            if (TTC > TTL)
                TI = 2;
            MOS();
            break;
        }
    }
    
}

void STARTEXECUTION()
{

    IC = Memory[PageTabelPointer * 10][1] * 10 + Memory[PageTabelPointer * 10][0];
    IC = IC *10;
    printf("[INFO] IC set to %d.\n", IC);
    EXECUTEUSERPROGRAM();
}

void LOAD()
{
    printf("[INFO] Loading started.\n");
    clearBuffer();
    char ch;
    int i = 0, flag = 0;

    while ((ch = fgetc(Input)) != EOF && IC != 100)
    {
        if (ch != '\n'){
            buffer[i++] = ch;
            if (i > buffSize)
            {
                printf("[DEBUG] ch: %c i: %d\n", ch, i);
                printf("[DEBUG] Buffer: %s\n", buffer);
                printf("[ERROR] Buffer overflow.\n");
                return;
            }
        }
        else if (ch == '\n' && i != 0)
        {
            buffer[i] = '\0';
            i = 0;

            if (strncmp(buffer, "$AMJ", 4) == 0)
            {
                INIT();
                printf("[INFO] TTL: %d\n", TTL);
                printf("[INFO] TLL: %d\n", TLL);
                printf("[INFO] Job id: %c%c%c%c\n", jobid[0], jobid[1], jobid[2], jobid[3]);
                printf("[INFO] SI: %d\n", SI);
                printf("[INFO] TI: %d\n", TI);
                printf("[INFO] PI: %d\n", PI);
                printf("[INFO] TTC: %d\n", TTC);
                printf("[INFO] LLC: %d\n", LLC);
                printf("[INFO] IC: %d\n", IC);
                printf("[INFO] C: %d\n", C);
                printf("[INFO] IR: %.4s\n", IR);
                printf("[INFO] Page Table Pointer: %d\n", PageTabelPointer);
                printf("[INFO] Job loaded.\n");
                printf("[INFO] Program count: %d\n", programCount);
                flag = 0;
                continue;
            }
            else if (strncmp(buffer, "$DTA", 4) == 0)
            {
                flag = 1;
                STARTEXECUTION();
                continue;
            }
            else if (strncmp(buffer, "$END", 4) == 0)
            {
                flag = 0;
                continue;
            }

            else if (!flag)
            {
                int freeframe;
                int repeat = 1;
                printf("[DEBUG] PAGE TABEL:\n");
                for (int j = 0; j < 10; j++)
                {
                    printf("%c%c ", Memory[PageTabelPointer * 10 + j][0], Memory[PageTabelPointer * 10 + j][1]);
                }
                printf("\n");
                do
                {
                    freeframe = getRandomValue();
                    if (freeframe == PageTabelPointer)
                    {
                        printf("[INFO] Frame %d is already in use. Trying again...\n", freeframe);
                        repeat = 1;
                    }
                    else if (Present_in_PageTable(freeframe))
                    {
                        printf("[INFO] Frame %d is already in use. Trying again...\n", freeframe);
                        repeat = 1;
                    }
                    else
                    {
                        repeat = 0;
                        printf("[INFO] Frame %d is free.\n", freeframe);
                    }
                } while (repeat);

                programCount++;
                printf("[INFO] Program count: %d\n", programCount);

                int progIC = freeframe * 10;
                for (int j = 0; buffer[j] != '\0'; j++)
                {
                    Memory[progIC][j % irSize] = buffer[j];
                    if ((j % irSize) == irSize - 1)
                        progIC++;
                }
                
                printf("[INFO] Program loaded to frame %d.\n", freeframe);

                Memory[PageTabelPointer * 10 + programCount][0] = freeframe % 10 ;
                Memory[PageTabelPointer * 10 + programCount][1] = freeframe / 10 ;
                printf("[INFO] Page Table updated.\n");
                printf("[DEBUG] PAGE TABEL:\n");
                for (int j = 0; j < 10; j++)
                {
                    printf("%c%c ", Memory[PageTabelPointer * 10 + j][0], Memory[PageTabelPointer * 10 + j][1]);
                }
                printf("\n");
            }
            clearBuffer();
        }
    }
}

int main()
{
    Input = fopen("input.txt", "r");
    if (Input == NULL)
    {
        printf("[ERROR] Could not open input file.\n");
        return 4;
    }

    Output = fopen("output.txt", "a");
    if (Output == NULL)
    {
        printf("[ERROR] Could not open output file.\n");
        return 5;
    }

    LOAD();

    fclose(Input);
    fclose(Output);
    return 0;
}
