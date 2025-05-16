//#pragma once
#ifndef CODE_H
#define CODE_H

// Functions to encode destination, computation, and jump command parts
int code_dest(const char* command, char* code);
int code_comp(const char* command, char* code);
int code_jump(const char* command, char* code);

// Function to convert an integer to a binary string
void code_convertIntToBinString(int x, char* binaryString);

#endif //CODE_H