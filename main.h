#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/* Prototypes */
int _printf(const char *format, ...);
int _putchar(char c);

int print_char(va_list args, int width);
int print_string(va_list args, int width, int precision);
int print_S(va_list args);
int print_percent(int width);
int print_int(va_list args, int plus_flag, int space_flag,
	      int length, int width, int precision);
int print_binary(va_list args);
int print_unsigned(va_list args, int length, int width, int precision);
int print_octal(va_list args, int hash_flag, int length,
		int width, int precision);
int print_hex_lower(va_list args, int hash_flag, int length,
		    int width, int precision);
int print_hex_upper(va_list args, int hash_flag, int length,
		    int width, int precision);
int print_pointer(va_list args, int width /* precision ignored */);

#endif /* MAIN_H */
