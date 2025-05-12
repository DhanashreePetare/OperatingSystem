/*Consider the virtual machine with one general purpose register of 4 bytes, instruction
register of 4 bytes, instruction counter of 2 bytes &amp; toggle register of a bit. The
instruction set consists of 7 instructions of 4 bytes each. (GD, PD, LR, SR, CR, BT &amp; H).
Consider the main memory of 400 words. Write a program to print welcome message in
the input file. Given the page table entries [11, 23, 05]. Write the OS code which will
convert the given virtual address (e.g. VA =12) in the real address. Consider the page
size as 10 words.*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MEM_SIZE 400
#define PAGE_SIZE 10
#define INSTR_SIZE 4
#define NUM_PAGES (MEM_SIZE/PAGE_SIZE)

// CPU Registers
char R[4];          // General purpose register
char IR[INSTR_SIZE]; // Instruction register
short IC;           // Instruction counter (2 bytes)
bool C;             // Toggle register (1 bit)

// Memory Management
int pageTable[3] = {11, 23, 5}; // Given page table entries
char memory[MEM_SIZE][INSTR_SIZE];

// Function prototypes
void initializeSystem();
void loadWelcomeMessage();
int virtualToPhysical(int virtualAddress);
void executeProgram();
void printMemoryContents();

int main() {
    initializeSystem();
    loadWelcomeMessage();
    
    printf("System initialized. Memory contents:\n");
    printMemoryContents();
    
    // Test address translation
    int virtualAddress = 12; // Example VA
    int physicalAddress = virtualToPhysical(virtualAddress);
    printf("\nVirtual Address %d -> Physical Address %d\n", 
           virtualAddress, physicalAddress);
    
    // Execute the program
    executeProgram();
    
    return 0;
}

void initializeSystem() {
    // Initialize registers
    memset(R, 0, sizeof(R));
    memset(IR, 0, sizeof(IR));
    IC = 0;
    C = false;
    
    // Initialize memory
    for(int i = 0; i < MEM_SIZE; i++) {
        memset(memory[i], 0, INSTR_SIZE);
    }
}

void loadWelcomeMessage() {
    // Store welcome message in memory using page table
    char welcomeMsg[] = "WELCOME TO OUR OS SIMULATOR";
    int msgLength = strlen(welcomeMsg);
    
    // Use page 0 (frames 11-20) for the message
    int frame = pageTable[0];
    int offset = 0;
    
    for(int i = 0; i < msgLength; i++) {
        if(offset >= PAGE_SIZE) {
            frame = pageTable[1]; // Switch to next frame if needed
            offset = 0;
        }
        memory[frame * PAGE_SIZE + offset][0] = welcomeMsg[i];
        offset++;
    }
    
    // Load a simple program to print the message
    // Program instructions at page 2 (frame 5, addresses 50-59)
    strcpy(memory[pageTable[2] * PAGE_SIZE + 0], "PD10"); // Print from VA 10
    strcpy(memory[pageTable[2] * PAGE_SIZE + 1], "H");    // Halt
}

int virtualToPhysical(int virtualAddress) {
    int pageNumber = virtualAddress / PAGE_SIZE;
    int offset = virtualAddress % PAGE_SIZE;
    
    if(pageNumber >= 3) {
        printf("Error: Page fault - invalid page number %d\n", pageNumber);
        return -1;
    }
    
    int frame = pageTable[pageNumber];
    return (frame * PAGE_SIZE) + offset;
}

void executeProgram() {
    printf("\nStarting program execution...\n");
    
    // Set IC to start of program (page 2, frame 5)
    IC = pageTable[2] * PAGE_SIZE;
    
    while(true) {
        // Fetch instruction
        memcpy(IR, memory[IC], INSTR_SIZE);
        printf("IC: %d | IR: %.4s\n", IC, IR);
        
        // Execute instruction
        if(strncmp(IR, "GD", 2) == 0) {
            // Get Data (not used in this example)
            IC++;
        }
        else if(strncmp(IR, "PD", 2) == 0) {
            // Print Data
            int virtualAddress = (IR[2]-'0')*10 + (IR[3]-'0');
            int physicalAddress = virtualToPhysical(virtualAddress);
            
            if(physicalAddress == -1) {
                printf("Error: Invalid virtual address %d\n", virtualAddress);
                break;
            }
            
            // Print the string starting at this address
            printf("Output: ");
            for(int i = 0; i < PAGE_SIZE; i++) {
                if(memory[physicalAddress + i][0] != 0) {
                    printf("%c", memory[physicalAddress + i][0]);
                }
            }
            printf("\n");
            IC++;
        }
        else if(strncmp(IR, "H", 1) == 0) {
            // Halt
            printf("Program terminated normally\n");
            break;
        }
        else {
            printf("Error: Invalid instruction\n");
            break;
        }
    }
}

void printMemoryContents() {
    // Print memory contents for the frames we're using
    for(int p = 0; p < 3; p++) {
        int frame = pageTable[p];
        printf("\nFrame %d (Page %d):\n", frame, p);
        
        for(int i = 0; i < PAGE_SIZE; i++) {
            int addr = frame * PAGE_SIZE + i;
            printf("M[%d]: %.4s\n", addr, memory[addr]);
        }
    }
}