//assembler_modified5.c
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

int main(int argc, char* argv[]) 
{
        ////////////////////////////////////////////////////////////
        //Initialization
        ////////////////////////////////////////////////////////////
        printf("\n\n\n");
        printf("Initialization\n");
        printf("=======================\n");

        //Opens the input file, and gets ready to process it
        const char* assemblyFilename;
        if (argc < 2) {
            fprintf(stderr, "Assembly filename is ../input.asm\n");
            assemblyFilename = "../input.asm";
        }
        else
            assemblyFilename = argv[1];
        if (!parser_init(assemblyFilename)) {
            fprintf(stderr, "Usage: assembler filename (default ../file.asm)\n");
            perror("fopen");
            exit(0);
        }



        FILE* outf;
        outf = fopen("output.hack", "w");
        if (outf == NULL) {
            printf("Error opening file!\n");
            return 1;
        }


        char symbol[LINE_MAX_SIZE];
        int i = 0, j = 0;
        for (i = 0;i <= 15; i++) {
            sprintf(symbol, "R%d", i);
            symbolTable_addEntry(symbol, i);
        }
        symbolTable_addEntry("SCREEN", 16384);
        symbolTable_addEntry("KBD", 24576);
        symbolTable_addEntry("SP", 0);
        symbolTable_addEntry("LCL", 1);
        symbolTable_addEntry("ARG", 2);
        symbolTable_addEntry("THIS", 3);
        symbolTable_addEntry("THAT", 4);


        char addressStr[LINE_MAX_SIZE];
        char dest[LINE_MAX_SIZE];
        char comp[LINE_MAX_SIZE];
        char jump[LINE_MAX_SIZE];
        char line[LINE_MAX_SIZE];
        char destBinaryStr[20];
        char compBinaryStr[20];
        char jumpBinaryStr[20];
        char binaryString[17];
        while (parser_parseNextLine(line)) {
            if (parser_instructionType() == A_INSTRUCTION || parser_instructionType() == C_INSTRUCTION)
                j++;
            if (parser_instructionType() == L_INSTRUCTION) {
                parser_symbol(symbol);
                symbolTable_addEntry(symbol, j);
            }
        }
        parser_rewind();
        while (parser_parseNextLine(line)) {
            if (parser_instructionType() == COMMENT_OR_EMPTY || parser_instructionType() == L_INSTRUCTION)
                continue;
            if (parser_instructionType() == A_INSTRUCTION) {
                parser_address(addressStr);
                char* endptr;
                long value = strtol(addressStr, &endptr, 10);
                if (*endptr != '\0') {
                    if (symbolTable_getAddress(addressStr) == -1) {
                        symbolTable_addEntry(addressStr, i);
                        code_convertIntToBinString(i, binaryString);
                        i++;
                    }
                    else
                        code_convertIntToBinString(symbolTable_getAddress(addressStr), binaryString);
                }
                else
                    code_convertIntToBinString(value, binaryString);
            }
            if (parser_instructionType() == C_INSTRUCTION) {
                parser_comp(comp);
                parser_dest(dest);
                parser_jump(jump);
                code_dest(dest, destBinaryStr);
                code_comp(comp, compBinaryStr);
                code_jump(jump, jumpBinaryStr);
                sprintf(binaryString, "111%s%s%s", compBinaryStr, destBinaryStr, jumpBinaryStr);
            }
            fprintf(outf, "%s\n", binaryString);
        }
        symbolTable_print();

}