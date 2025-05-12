/*
Consider the virtual machine with one general purpose register of 4 bytes,
instruction register of 4 bytes, instruction counter of 2 bytes &amp; toggle register of
a bit. The instruction set consists of 7 instructions of 4 bytes each. (GD, PD, LR,
SR, CR, BT &amp; H). Consider the main memory of 200 words. Add any arithmetic
instruction in the given instruction set. Write a program using the new
instruction. Write the OS code demonstrating execution of this program. [
Assume the program is already loaded in the main memory].
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MEM_SIZE 200
#define INSTR_SIZE 4

// CPU Registers
int R;              // General purpose register (4 bytes)
char IR[INSTR_SIZE]; // Instruction register (4 bytes)
short IC;           // Instruction counter (2 bytes)
bool C;             // Toggle register (1 bit)

// Main Memory
char memory[MEM_SIZE][INSTR_SIZE];

// Function prototypes
void initializeSystem();
void executeProgram();
void handleError(int errorCode);

int main() {
    initializeSystem();
    
    // Simulate loading a program with arithmetic operation
    strcpy(memory[0], "LR10");  // Load value from address 10 to R
    strcpy(memory[1], "ADD20"); // Add value from address 20 to R
    strcpy(memory[2], "SR30");  // Store result to address 30
    strcpy(memory[3], "PD30");  // Print value at address 30
    strcpy(memory[4], "H");     // Halt
    
    // Initialize test data
    int testValue1 = 25;
    int testValue2 = 17;
    memcpy(memory[10], &testValue1, sizeof(int)); // Address 10: 25
    memcpy(memory[20], &testValue2, sizeof(int)); // Address 20: 17
    
    executeProgram();
    
    return 0;
}

void initializeSystem() {
    // Initialize registers
    R = 0;
    memset(IR, 0, sizeof(IR));
    IC = 0;
    C = false;
    
    // Initialize memory
    for(int i = 0; i < MEM_SIZE; i++) {
        memset(memory[i], 0, INSTR_SIZE);
    }
}

void executeProgram() {
    printf("Starting program execution...\n");
    
    while(true) {
        // Fetch instruction
        memcpy(IR, memory[IC], INSTR_SIZE);
        printf("\nIC: %d | IR: %.4s | R: %d | C: %d\n", IC, IR, R, C);
        
        // Decode and execute
        if(strncmp(IR, "GD", 2) == 0) {
            // Get Data (not used in this example)
            IC++;
        }
        else if(strncmp(IR, "PD", 2) == 0) {
            // Print Data
            int address = (IR[2]-'0')*10 + (IR[3]-'0');
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            int value;
            memcpy(&value, memory[address], sizeof(int));
            printf("Output: %d\n", value);
            IC++;
        }
        else if(strncmp(IR, "LR", 2) == 0) {
            // Load Register
            int address = (IR[2]-'0')*10 + (IR[3]-'0');
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            memcpy(&R, memory[address], sizeof(int));
            IC++;
        }
        else if(strncmp(IR, "SR", 2) == 0) {
            // Store Register
            int address = (IR[2]-'0')*10 + (IR[3]-'0');
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            memcpy(memory[address], &R, sizeof(int));
            IC++;
        }
        else if(strncmp(IR, "CR", 2) == 0) {
            // Compare
            int address = (IR[2]-'0')*10 + (IR[3]-'0');
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            int value;
            memcpy(&value, memory[address], sizeof(int));
            C = (R == value);
            IC++;
        }
        else if(strncmp(IR, "BT", 2) == 0) {
            // Branch if True
            int address = (IR[2]-'0')*10 + (IR[3]-'0');
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            if(C) {
                IC = address;
            } else {
                IC++;
            }
        }
        else if(strncmp(IR, "ADD", 3) == 0) {
            // NEW: Arithmetic ADD instruction
            int address = (IR[3]-'0'); // Single digit address for simplicity
            if(address < 0 || address >= MEM_SIZE) {
                handleError(2); // Operand error
                break;
            }
            int value;
            memcpy(&value, memory[address], sizeof(int));
            R += value;
            IC++;
        }
        else if(strncmp(IR, "H", 1) == 0) {
            // Halt
            printf("Program terminated normally\n");
            break;
        }
        else {
            // Invalid opcode
            handleError(1); // Opcode error
            break;
        }
        
        // Check for memory bounds
        if(IC >= MEM_SIZE) {
            handleError(3); // Memory overflow
            break;
        }
    }
}

void handleError(int errorCode) {
    printf("\n--- ERROR HANDLER ---\n");
    
    switch(errorCode) {
        case 1:
            printf("OPCODE ERROR: Invalid instruction '%.4s'\n", IR);
            printf("Valid opcodes: GD, PD, LR, SR, CR, BT, ADD, H\n");
            break;
        case 2:
            printf("OPERAND ERROR: Invalid address in '%.4s'\n", IR);
            printf("Address must be between 00-%d\n", MEM_SIZE-1);
            break;
        case 3:
            printf("MEMORY ERROR: Instruction counter out of bounds\n");
            break;
        default:
            printf("UNKNOWN ERROR: Code %d\n", errorCode);
    }

    printf("Register State:\n");
    printf("R: %d\n", R);
    printf("C: %d\n", C);
    printf("IC: %d\n", IC);
}
