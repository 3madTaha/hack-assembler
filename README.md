# Hack Assembler – Nand to Tetris Project

This project is a complete assembler for the Hack assembly language, written in C, based on the Nand to Tetris architecture.

## 📋 Overview

This project implements a full assembler for the Hack assembly language as part of the Nand to Tetris course.

The assembler was built on top of a provided modular framework (`Parser`, `SymbolTable`, and `Code`), and I developed the full assembly logic in `HackAssembler.c` to translate `.asm` files into `.hack` machine code.

## 🔧 Features

- Supports all A and C instructions.
- Parses and resolves labels and variables.
- Maintains symbol table for predefined and user-defined symbols.
- Outputs valid 16-bit binary machine code lines.

## 🧠 System Calls and Techniques

- File I/O (`fopen`, `fread`, `fprintf`, etc.)
- String processing and parsing
- Symbol handling using a hash table
- Manual memory and pointer management

## 🚀 Usage (Windows / Visual Studio)

1. Open the provided Visual Studio project.
2. Replace `input.asm` with the desired `.asm` file (e.g., `Max.asm`) in the project folder.
3. Build and run the project:
   - The program will read from `input.asm` by default.
   - It will generate an output file named `output.hack` in the same folder.

4. To test correctness:
   - Use `diff` or any file comparison tool to compare `output.hack` with the reference `.hack` file.

Optional (if compiled to an `.exe` and used from command line):

```cmd
HackAssembler.exe path\to\your\file.asm

If no parameter is given, it will use input.asm by default.


