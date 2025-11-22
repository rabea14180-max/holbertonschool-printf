#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/* main printf and putchar */
int _printf(const char *format, ...);
int _putchar(char c);

/* helpers for different specifiers */
int print_char(va_list args, int width);
int print_string(va_list args, int width, int precision);
int print_S(va_list args);
int print_percent(int width);

int print_int(va_list args, int width, int plus_flag,
	      int space_flag, int length, int precision);

int print_binary(va_list args);

int print_unsigned(va_list args, int width, int length, int precision);
int print_octal(va_list args, int width, int hash_flag,
		int length, int precision);
int print_hex_lower(va_list args, int width, int hash_flag,
		    int length, int precision);
int print_hex_upper(va_list args, int width, int hash_flag,
		    int length, int precision);

int print_pointer(va_list args, int width);

#ifndef MAIN_H
#define MAIN_H

#include <stdarg.h>
#include <unistd.h>

/* main printf and putchar */
int _printf(const char *format, ...);
int _putchar(char c);

/* helpers for different specifiers */
int print_char(va_list args, int width);
int print_string(va_list args, int width);
int print_S(va_list args);
int print_percent(int width);

int print_int(va_list args, int width, int plus_flag,
	      int space_flag, int length);

int print_binary(va_list args);

int print_unsigned(va_list args, int width, int length);
int print_octal(va_list args, int width, int hash_flag, int length);
int print_hex_lower(va_list args, int width, int hash_flag, int length);
int print_hex_upper(va_list args, int width, int hash_flag, int length);

int print_pointer(va_list args, int width);

#endif /* MAIN_H */
#endif /* MAIN_H */`
