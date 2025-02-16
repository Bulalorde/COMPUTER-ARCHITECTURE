#include <stdio.h>
#include <stdbool.h>

void printBin(int num, unsigned char num_width) {
    int i;
    for(i = num_width - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
}

int ALU(signed char operand1, signed char operand2, unsigned char control_signals) {
    signed short ACC = 0; // Accumulator to store the result

    switch(control_signals) {
        case 0x03: // Booth's Multiplication
            printf("Operation: MUL\n");

            signed short regA = 0;
            signed short regQ = operand2;
            signed short regM = operand1;
            int lastBitQ = 0;
            int stepCount = 8;

            printf("Initial values:\n");
            printf("A: "); printBin(regA, 8);
            printf("\tQ: "); printBin(regQ, 8);
            printf("\tM: "); printBin(regM, 8);
            printf("\n");

            while (stepCount > 0) {
                // Booth's condition checks
                if ((regQ & 1) == 1 && lastBitQ == 0) {
                    regA = regA - regM;
                } else if ((regQ & 1) == 0 && lastBitQ == 1) {
                    regA = regA + regM;
                }

                // Arithmetic Right Shift
                lastBitQ = regQ & 1;  // Save Q0 before shifting
                regQ = (regQ >> 1) | ((regA & 1) << 7); // Shift regQ right, bringing A0
                regA = (regA & 0x80) | (regA >> 1); // Preserve sign bit in A

                stepCount--;
            }

            // Correct ACC computation
            ACC = ((regA & 0xFF) << 8) | (regQ & 0xFF);
            printf("Final ACC: "); printBin(ACC, 16);
            printf("\n");

            return ACC;
    }
}

void main() {
    int result = ALU(0x03, 0x05, 0x03); // Multiply 5 * 5
    printf("Multiplication Result: %d\n", result);
}
