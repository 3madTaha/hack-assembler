// ==========================
// Hack Assembler - main()
// ==========================
// This program translates Hack assembly (.asm) files into binary machine code (.hack)
// Based on provided modules: Parser, SymbolTable, Code
// Developed as part of the Nand to Tetris course

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

        // If no file name is passed via command line, use default ../input.asm
        const char* assemblyFilename;
        if (argc < 2) {
            fprintf(stderr, "Assembly filename is ../input.asm\n");
            assemblyFilename = "../input.asm";
        }
        else
            assemblyFilename = argv[1];

        // Initialize the parser with the input file
        if (!parser_init(assemblyFilename)) {
            fprintf(stderr, "Usage: assembler filename (default ../file.asm)\n");
            perror("fopen");
            exit(0);
        }


        // Open output file for writing the binary code
        FILE* outf;
        outf = fopen("output.hack", "w");
        if (outf == NULL) {
            printf("Error opening file!\n");
            return 1;
        }

        // Add predefined symbols to the symbol table: R0–R15, SCREEN, KBD, and other standard symbols
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

        // First pass - add labels to symbol table
        while (parser_parseNextLine(line)) {
            if (parser_instructionType() == A_INSTRUCTION || parser_instructionType() == C_INSTRUCTION)
                j++; // Each real instruction increases ROM address
            if (parser_instructionType() == L_INSTRUCTION) {
                parser_symbol(symbol);
                symbolTable_addEntry(symbol, j); // Map label to current ROM address
            }
        }

        // Second pass - translate instructions to binary
        parser_rewind(); // Reset parser to beginning
        while (parser_parseNextLine(line)) {
            if (parser_instructionType() == COMMENT_OR_EMPTY || parser_instructionType() == L_INSTRUCTION)
                continue; // Skip empty lines and labels
            // Handle A-instruction (e.g. @value or @symbol)
            if (parser_instructionType() == A_INSTRUCTION) {
                parser_address(addressStr);
                char* endptr;
                long value = strtol(addressStr, &endptr, 10);
                if (*endptr != '\0') { // It's a symbol, not a number
                    if (symbolTable_getAddress(addressStr) == -1) { // Not in table: assign new RAM address
                        symbolTable_addEntry(addressStr, i);
                        code_convertIntToBinString(i, binaryString);
                        i++;
                    }
                    else // Already exists: use its address
                        code_convertIntToBinString(symbolTable_getAddress(addressStr), binaryString);
                }
                else // It's a direct numeric value
                    code_convertIntToBinString(value, binaryString);
            }
            // Handle C-instruction (e.g. dest=comp;jump)
            if (parser_instructionType() == C_INSTRUCTION) {
                parser_comp(comp);
                parser_dest(dest);
                parser_jump(jump);
                code_dest(dest, destBinaryStr);
                code_comp(comp, compBinaryStr);
                code_jump(jump, jumpBinaryStr);
                sprintf(binaryString, "111%s%s%s", compBinaryStr, destBinaryStr, jumpBinaryStr); // Compose full binary string
            }
            fprintf(outf, "%s\n", binaryString); // Write the 16-bit binary instruction to the output file
        }
        symbolTable_print(); // Show all stored symbols and addresses
        return 0;
}