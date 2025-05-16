#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "Code.h"

#define ENCODING_MAX_STRSIZE 16

// Structures to represent encoding information
typedef struct {
    const char command[ENCODING_MAX_STRSIZE];
    const char code[ENCODING_MAX_STRSIZE];
} EncodingEntry;

// Arrays to store encoding information for destination, jump, and computation
const EncodingEntry destdict[] = { {"", "000"}, {"M", "001"}, {"D", "010"}, {"MD", "011"}, {"A", "100"}, {"AM", "101"}, {"AD", "110"}, {"ADM", "111"} };
const EncodingEntry compdict[] = { {"0", "0101010"}, {"1", "0111111"}, {"-1", "0111010"}, {"D", "0001100"}, {"A", "0110000"}, {"M", "1110000"}, {"!D", "0001101"}, {"!A", "0110001"}, {"!M", "1110001"}, {"-D", "0001111"}, {"-A", "0110011"}, {"-M", "1110011"}, {"D+1", "0011111"}, {"A+1", "0110111"}, {"M+1", "1110111"}, {"D-1", "0001110"}, {"A-1", "0110010"}, {"M-1", "1110010"}, {"D+A", "0000010"}, {"D+M", "1000010"}, {"D-A", "0010011"}, {"D-M", "1010011"}, {"A-D", "0000111"}, {"M-D", "1000111"}, {"D&A", "0000000"}, {"D&M", "1000000"}, {"D|A", "0010101"}, {"D|M", "1010101"}, {"M+D", "1000010"}, {"M+A", "0000010"} };
const EncodingEntry jmpdict[] = { {"", "000"}, {"JGT", "001"}, {"JEQ", "010"}, {"JGE", "011"}, {"JLT", "100"}, {"JNE", "101"}, {"JLE", "110"}, {"JMP", "111"} };

// Function to encode a field into binary code from an encoding dictionary
int encode(const EncodingEntry dictarr[], int tableSize, const char* command, char* code) {
    for (int i = 0; i < tableSize; i++) {
        if (strcmp(dictarr[i].command, command) == 0) {
            strcpy(code, dictarr[i].code);
            return 1;
        }
    }
    *code = '\0';
    return 0;
}

// Functions to encode destination, computation, and jump command parts
int code_dest(const char* command, char* code) {
    return encode(destdict, sizeof(destdict) / sizeof(destdict[0]), command, code);
}
int code_comp(const char* command, char* code) {
    return encode(compdict, sizeof(compdict) / sizeof(compdict[0]), command, code);
}
int code_jump(const char* command, char* code) {
    return encode(jmpdict, sizeof(jmpdict) / sizeof(jmpdict[0]), command, code);
}

// Function to convert an integer to a binary string
void code_convertIntToBinString(int x, char* binaryString)
{
    for (int i = 15; i >= 0; i--) {
        binaryString[15 - i] = (x & (1 << i)) ? '1' : '0';
    }
    binaryString[16] = '\0';
}
