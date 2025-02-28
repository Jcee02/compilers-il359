# Custom Language Lexer

## Overview
This project implements a lexical analyzer (lexer) for a custom programming language. It tokenizes input source code by recognizing patterns defined by the language's lexical rules, converting text into a stream of tokens that can be used in subsequent compilation phases.

## Project Structure
The project consists of the following main files:

- `main.c` - The entry point of the program that handles command-line arguments and drives the lexical analysis process
- `util.h` - Header file containing declarations for utility functions and data structures
- `util.c` - Implementation of utility functions, including token handling, string manipulation, and memory management
- `build.sh` - Shell script for compiling the project
- Example files (`example.txt`, `example2.txt`) - Sample code in the custom language for testing

## Building the Project
To build the project, use the provided build script:

```bash
./build.sh
```

This will compile the source files and create an executable.

## Running the Program
After building, run the program with an input file:

```bash
./lexer <filename>
```

Example:
```bash
./lexer example.txt
```

## Lexical Analysis
The lexer operates as the first phase of a potential compiler or interpreter. It performs the following functions:

- Scans the input text character by character
- Identifies tokens based on patterns and rules
- Categorizes tokens into different types
- Handles whitespace and comments
- Reports lexical errors (such as invalid characters)

### Token Types
The lexer recognizes various token types, including:
- Keywords (if, else, while, for, etc.)
- Identifiers (variable and function names)
- Literals (numbers, strings)
- Operators (+, -, *, /, etc.)
- Delimiters (parentheses, braces, semicolons)

## Language Features
The lexer supports tokenization of language features such as:

- Variable names and literals
- Arithmetic operators
- Comparison operators
- Assignment operations
- Control flow keywords
- Function declaration syntax
- Comments

Note that this lexer only performs tokenization and does not validate syntax or build syntax trees.

## Utility Functions
The utility module provides support functions for the lexer:

- Memory management for tokens and data structures
- String manipulation and comparison
- Error handling and reporting for lexical errors
- File I/O operations

## Error Handling
The program includes error detection and reporting for lexical errors:
- Invalid characters
- Malformed tokens
- File handling errors

## Examples
The repository includes example files demonstrating the language features that can be tokenized. You can use these to test the lexer functionality.

## Extending the Project
To extend this project:
- Add new token types in the token enumeration
- Support additional lexical patterns
- Enhance error reporting with more detailed messages
- Add a parser phase to analyze syntax
- Implement a symbol table for a complete compiler front-end

