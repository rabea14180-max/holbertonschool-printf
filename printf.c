#include <stdarg.h>
#include "main.h"

/**
 * print_char - print single char using _putchar
 * @c: char to print
 *
 * Return: number of chars printed (1) or -1 on error
 */
int print_char(char c)
{
    int r = _putchar(c);
    if (r < 0)
        return -1;
    return 1;
}

/**
 * print_string - print a C string using _putchar
 * @s: string to print (may be NULL)
 *
 * Return: number of characters printed, or -1 on error
 */
int print_string(const char *s)
{
    int count = 0;

    if (s == NULL)
        s = "(null)"; /* or "(nil)" depending on spec */

    while (*s)
    {
        if (_putchar(*s) < 0)
            return -1;
        count++;
        s++;
    }
    return count;
}

/**
 * _printf - minimal printf supporting %c, %s and %%
 * @format: format string
 *
 * Return: number of characters printed (excluding terminating null),
 *         or -1 on error (e.g., format == NULL or write error or stray % at end)
 */
int _printf(const char *format, ...)
{
va_list args;
int total = 0;
int res;

if (format == NULL)
return -1;

va_start(args, format);
while (*format)
{
if (*format != '%')
{
if (_putchar(*format) < 0)
{
va_end(args);
return -1;
}
total++;
format++;
continue;
}


format++;


if (*format == '\0')
{
            va_end(args);
return -1;
}

if (*format == 'c')
{
int ch = va_arg(args, int); /* char promoted to int
res = print_char((char)ch);
if (res < 0)
{
va_end(args);
return -1;
}
total += res;
}
else if (*format == 's')
{
const char *s = va_arg(args, const char *);
res = print_string(s);
if (res < 0)
            {
va_end(args);
return -1;
}
total += res;
}
else if (*format == '%')
{
if (_putchar('%') < 0)
{
va_end(args);
return -1;
}
total++;
}
else
{
if (_putchar('%') < 0 || _putchar(*format) < 0)
{
va_end(args);
return -1;
}
total += 2;
}

format++;
}

va_end(args);
return total;
}
