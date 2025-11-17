#include "main.h"
#include <stdarg.h>
/**
 * _printf - produces output according to a format
 * @format: a character string containing zero or more directives
 *
 * Handles the following conversion specifiers:
 *  c: prints a character
 *  s: prints a string
 *  %: prints a percent sign
 *
 * Return: the number of characters printed (excluding the null byte)
 *         or -1 if format is NULL
 */
int _printf(const char *format, ...)
{
va_list args;
int i = 0, count = 0, j;
char *str;

if (!format)
return (-1);
va_start(args, format);
while (format[i])
{
if (format[i] != '%')
count += _putchar(format[i]);
else
{
i++;
if (!format[i])
return (-1);
if (format[i] == 'c')
count += _putchar(va_arg(args, int));
else if (format[i] == 's')
{
str = va_arg(args, char *);
if (!str)
str = "(null)";
for (j = 0; str[j]; j++)
count += _putchar(str[j]);
}
else if (format[i] == '%')
count += _putchar('%');
else
{
count += _putchar('%');
count += _putchar(format[i]);
}
}
i++;
}
va_end(args);
return (count);
}
