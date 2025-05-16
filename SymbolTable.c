#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

#include "SymbolTable.h"

#define SYMBOL_TABLE_STRSIZE 100
#define SYMBOL_TABLE_MAX_SYMBOL_NUM 5000

// Structures to represent symbol entries
typedef struct {
    char name[SYMBOL_TABLE_STRSIZE];
    int address;
} SymbolEntry;

// Global symbol table
SymbolEntry symbolTable[SYMBOL_TABLE_MAX_SYMBOL_NUM];
int symbolCount = 0;


// Function to add a new symbol entry to the table
void symbolTable_addEntry(const char symbolName[], int symbolAddress) {
    if (symbolCount < SYMBOL_TABLE_MAX_SYMBOL_NUM) {
        strcpy(symbolTable[symbolCount].name, symbolName);
        symbolTable[symbolCount].address = symbolAddress;
        symbolCount++;
    }
    else {
        printf("Error: Symbol table is full\n");
    }
}

// Function to return symbol address or -1 for symbol that does not exist in the symbol table
int symbolTable_getAddress(const char symbolName[]) {
    for (int i = 0; i < symbolCount; i++) {
        if (strcmp(symbolTable[i].name, symbolName) == 0) {
            return symbolTable[i].address;
        }
    }
    return -1; // Symbol not found
}

// Function to print the symbol table
void symbolTable_print() {
    printf("\n");
    printf("Symbols table (size=%d)\n", symbolCount);
    printf("-------------------------\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("%-10s  %-6d\n", symbolTable[i].name, symbolTable[i].address);
    }
}
