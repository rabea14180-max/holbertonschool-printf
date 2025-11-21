#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/* Prototypes */
int _printf(const char *format, ...);
int _putchar(char c);

int print_char(va_list args);
int print_string(va_list args);
int print_S(va_list args);
int print_percent(void);
int print_int(va_list args, int plus_flag, int space_flag);
int print_binary(va_list args);
int print_unsigned(va_list args);
int print_octal(va_list args, int hash_flag);
int print_hex_lower(va_list args, int hash_flag);
int print_hex_upper(va_list args, int hash_flag);
int print_pointer(va_list args);

#endif /* MAIN_H */
