#ifndef SYMBOL_TABLE_H
#define SYMBOL_TABLE_H

// Function to add a new symbol entry to the table
void symbolTable_addEntry(const char symbolName[], int symbolAddress);

// Function to return symbol address or -1 for symbol that does not exist in the symbol table
int symbolTable_getAddress(const char symbolName[]);

// Function to print the symbol table
void symbolTable_print();


#endif //SYMBOL_TABLE_H
