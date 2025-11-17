#include "main.h"
#include <stdarg.h>

/**
 * _printf - produces output according to a format
 * @format: character string containing directives
 *
 * Return: number of characters printed
 */
int _printf(const char *format, ...)
{
va_list args;
int i = 0, count = 0;

if (format == NULL)
return (-1);

va_start(args, format);

while (format[i])
{
if (format[i] != '%')
{
_putchar(format[i]);
count++;
}
else
{
i++;

if (format[i] == '\0')
return (-1);

if (format[i] == 'c')
{
char c = va_arg(args, int);
_putchar(c);
count++;
}
else if (format[i] == 's')
{
char *str = va_arg(args, char *);
int j = 0;

if (str == NULL)
str = "(null)";

while (str[j])
{
_putchar(str[j]);
count++;
j++;
}
}
else if (format[i] == '%')
{
_putchar('%');
count++;
}
else
{

_putchar('%');
_putchar(format[i]);
count += 2;
}
}
i++;
}

va_end(args);
return (count);
}
