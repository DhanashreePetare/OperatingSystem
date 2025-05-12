/*Consider the virtual machine with one general purpose register of 4 bytes, instruction
register of 4 bytes, instruction counter of 2 bytes &amp; toggle register of a bit. The
instruction set consists of 7 instructions of 4 bytes each. (GD, PD, LR, SR, CR, BT &amp; H).
Consider the main memory of 200 words. Write a program with opcode &amp; operand
error. Write the OS code which execute this program and display errors. Consider block
size as 10 words. [ Assume the program is already loaded in the main memory].*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MEM_SIZE 200
#define BLOCK_SIZE 10
#define INSTR_SIZE 4

// CPU Registers
char R[4];          // General purpose register
char IR[INSTR_SIZE]; // Instruction register
int IC;             // Instruction counter (2 bytes)
bool C;             // Toggle register (1 bit)

// Main Memory
char memory[MEM_SIZE][INSTR_SIZE];

// Function prototypes
void executeProgram();
void handleError(int errorCode);
void loadProgram();

int main() {
    // Initialize registers
    memset(R, 0, sizeof(R));
    memset(IR, 0, sizeof(IR));
    IC = 0;
    C = false;

    // Load the program into memory (simulated)
    loadProgram();

    // Execute the program
    executeProgram();

    return 0;
}

void loadProgram() {
    // Simulate loading a program with errors
    strcpy(memory[0], "GD10");  // Valid
    strcpy(memory[1], "PD20");  // Valid
    strcpy(memory[2], "LRX5");  // Operand error (X is not digit)
    strcpy(memory[3], "XX30");  // Opcode error (XX invalid)
    strcpy(memory[4], "H");     // Valid
}

void executeProgram() {
    printf("Starting program execution...\n");
    
    while (true) {
        // Fetch instruction
        memcpy(IR, memory[IC], INSTR_SIZE);
        printf("\nIC: %d | IR: %.4s\n", IC, IR);

        // Decode and execute
        if (strncmp(IR, "GD", 2) == 0) {
            // Get Data instruction
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing GD - Reading data\n");
            IC++;
        }
        else if (strncmp(IR, "PD", 2) == 0) {
            // Print Data instruction
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing PD - Printing data\n");
            IC++;
        }
        else if (strncmp(IR, "LR", 2) == 0) {
            // Load Register
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing LR - Loading register\n");
            IC++;
        }
        else if (strncmp(IR, "SR", 2) == 0) {
            // Store Register
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing SR - Storing register\n");
            IC++;
        }
        else if (strncmp(IR, "CR", 2) == 0) {
            // Compare
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing CR - Comparing values\n");
            IC++;
        }
        else if (strncmp(IR, "BT", 2) == 0) {
            // Branch if true
            if (!isdigit(IR[2]) || !isdigit(IR[3])) {
                handleError(2); // Operand error
                break;
            }
            printf("Executing BT - Branching if C=true\n");
            IC++;
        }
        else if (strncmp(IR, "H", 1) == 0) {
            // Halt
            printf("Executing H - Normal termination\n");
            handleError(0);
            break;
        }
        else {
            // Invalid opcode
            handleError(1); // Opcode error
            break;
        }

        // Check for memory bounds
        if (IC >= MEM_SIZE/BLOCK_SIZE) {
            handleError(3); // Memory overflow
            break;
        }
    }
}

void handleError(int errorCode) {
    printf("\n--- ERROR HANDLER ---\n");
    
    switch (errorCode) {
        case 0:
            printf("Normal termination\n");
            break;
        case 1:
            printf("OPCODE ERROR: Invalid instruction '%.4s'\n", IR);
            printf("Valid opcodes: GD, PD, LR, SR, CR, BT, H\n");
            break;
        case 2:
            printf("OPERAND ERROR: Invalid operand in '%.4s'\n", IR);
            printf("Operands must be 2-digit numbers (00-99)\n");
            break;
        case 3:
            printf("MEMORY ERROR: Instruction counter out of bounds\n");
            break;
        default:
            printf("UNKNOWN ERROR: Code %d\n", errorCode);
    }

    printf("Register State:\n");
    printf("R: %.4s\n", R);
    printf("C: %d\n", C);
    printf("IC: %d\n", IC);
}