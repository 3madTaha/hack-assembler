#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Parser.h"



//assembly file pointer
FILE* fp = NULL;

//inint module
//open assembly file for reading. return 0 if fail to open the file
int parser_init(const char assemblyFilename[]) {
    fp = fopen(assemblyFilename, "rt");
    return (fp != NULL);
}

//rewind assembly file
void parser_rewind() {
    rewind(fp);
}


//insturction parssing results and getters
InstructionTypeEnum instructionType;
char symbol[LINE_MAX_SIZE];
char address[LINE_MAX_SIZE];
char dest[LINE_MAX_SIZE];
char comp[LINE_MAX_SIZE];
char jump[LINE_MAX_SIZE];
InstructionTypeEnum parser_instructionType() {
    return instructionType;
}
void parser_symbol(char symbol_[]) {
    strcpy(symbol_, symbol);
}
void parser_address(char address_[]) {
    strcpy(address_, address);
}
void parser_dest(char dest_[]) {
    strcpy(dest_, dest);
}
void parser_comp(char comp_[]) {
    strcpy(comp_, comp);
}
void parser_jump(char jump_[]) {
    strcpy(jump_, jump);
}



//helper functions
char* copyUntilChar(const char* src, char* dest, char ch);
int charExist(const char* str, char ch);
void removeLeadingSpaces(char src[], char dst[]);
void removeTrailingSpaces(char line[]);


//parsing current line
//return 0 if no more lines
int parser_parseNextLine(char line[]) {
    char command[LINE_MAX_SIZE];

    if (fgets(line, LINE_MAX_SIZE, fp) == NULL)
        return 0;
    else {
        removeLeadingSpaces(line, command);
        removeTrailingSpaces(command);

        //comment or empty line
        if (*command == '\0') {
            instructionType = COMMENT_OR_EMPTY;
            *symbol  = '\0';
            *address = '\0';
            *dest    = '\0';
            *comp    = '\0';
            *jump    = '\0';
        }
        //L instruction (label)
        else if (*command == '(') {
            //updating instructionType
            instructionType = L_INSTRUCTION;
            //updating symbol
            copyUntilChar(command + 1, symbol, ')');
            //updating dest, comp, jump to empty
            *address = '\0';
            *dest    = '\0';
            *comp    = '\0';
            *jump    = '\0';
        }
        //A instruction
        else if (*command == '@') {
            //updating instructionType
            instructionType = A_INSTRUCTION;
            //updating symbol
            copyUntilChar(command + 1, address, '\0');
            //updating dest, comp, jump to empty
            *symbol  = '\0';
            *dest    = '\0';
            *comp    = '\0';
            *jump    = '\0';
        }
        //C insturction
        else {
            //updating instructionType
            instructionType = C_INSTRUCTION;
            //updating symbol to empty
            *symbol  = '\0';
            *address = '\0';

            char* restOfCommandPt = command;
            //updating dest
            if (charExist(restOfCommandPt, '='))
                restOfCommandPt = copyUntilChar(restOfCommandPt, dest, '=');
            else
                *dest = '\0';
            //updating comp and jump
            if (charExist(restOfCommandPt, ';')) {
                restOfCommandPt = copyUntilChar(restOfCommandPt, comp, ';');
                copyUntilChar(restOfCommandPt, jump, '\0');
            }
            else {
                restOfCommandPt = copyUntilChar(restOfCommandPt, comp, '\0');
                *jump = '\0';
            }
        }
        return 1;
    }
}




char* copyUntilChar(const char* src, char* dest, char ch) {
    while (*src != '\0' && *src != ch) {
        *dest++ = *src++;
    }
    *dest = '\0';
    return src + 1;
}

int charExist(const char* str, char ch) {
    char* pt = str;
    while (*pt != '\0')
        if (*pt++ == ch)
            return 1;
    return 0;
}

void removeLeadingSpaces(char src[], char dst[])
{
    char* srcPtr = src;
    while (isspace(*srcPtr)) {
        srcPtr++;
    }
    strcpy(dst, srcPtr);
}

void removeTrailingSpaces(char line[])
{
    char* linePtr = line;
    while ((*linePtr != '\0') && (*linePtr != '/'))
        linePtr++;
    while ( (linePtr>=line) &&  (isspace(*linePtr) || (*linePtr == '\0') || (*linePtr == '/')) )
        linePtr--;
    *(linePtr+1) = '\0';
}
