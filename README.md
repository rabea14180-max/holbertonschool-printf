# printf

## Project Overview
This project is a custom-built version of the C standard library function `printf`.  
Our function, `_printf`, reproduces the core behavior of `printf` for the conversion specifiers that are implemented in this repository. The goal is to understand formatted output, variadic arguments, and low-level printing using system calls.

0.Basic conversion specifiers

Implement _printf handling:

%c → print a character

%s → print a string

%% → print a literal percent sign

Integers
Extend _printf to handle:

%d → print a decimal number

%i → print an integer

Man page
Create a manual page man_3_printf describing:

Function prototype

Description
Return value

Supported specifiers

Examples
---

## Requirements
All programs are compiled and tested on Ubuntu 20.04 LTS using:

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 -Wno-format *.c

👥 Team Collaboration
rabea thabit
Moudhi Almutlaq
