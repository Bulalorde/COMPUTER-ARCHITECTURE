#include <stdio.h>
#include <stdbool.h>
#include <string.h>

unsigned char SF = 0;
unsigned char CF = 0;
unsigned char ZF = 0;
unsigned char OF = 0;

void HextoBin(unsigned char op, char *opBin) {
    char binary[9] = ""; // 8 bits + null terminator

    for (int i = 7; i >= 0; i--) {
        binary[7 - i] = ((op >> i) & 1) ? '1' : '0';
    }
    binary[8] = '\0'; // Null-terminate the string

    strcpy(opBin, binary); // Copy to output variable
    printf("%s\n", opBin); // Print the binary
}

void main() {
    unsigned char operand1 = 0x02;
    unsigned char operand2 = 0x02;
    unsigned char control_signals = 0x08;

    char opBin1[9]; // To store binary string
    printf("********************************\n");
    printf("Fetching Operands...\n");
    HextoBin(operand1, opBin1);

    printf("Binary representation: %s\n", opBin1);
}
