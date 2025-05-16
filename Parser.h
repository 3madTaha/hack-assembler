//#pragma once

#ifndef PARSER_H
#define PARSER_H

typedef enum {
    A_INSTRUCTION,
    C_INSTRUCTION,
    L_INSTRUCTION,
    COMMENT_OR_EMPTY
} InstructionTypeEnum;

#define LINE_MAX_SIZE 400

//inint module
//open assembly file for reading. return 0 if fail to open the file
int parser_init(const char assemblyFilename[]);

//rewind assembly file
void parser_rewind();

//parsing current line
//return 0 if no more lines
int parser_parseNextLine(char line[]);

//insturction parssing getters
InstructionTypeEnum parser_instructionType();
void parser_symbol(char symbol_[]);
void parser_address(char address_[]);
void parser_dest(char dest_[]);
void parser_comp(char comp_[]);
void parser_jump(char jump_[]);

#endif //PARSER_H






