#include "main.h"
/**
* printf-praduces out put accourding to a format
* @fotmat :format string containing format specifiers
* return:numbr of characters printed (excluding nall by te )
*/

int -print (const char *format,...)
va-list args;
int count =0;
if (!format ||(format[0]=='%' &&format[1]=='\0'))
return (-1)

va _start (arg,format);
while (*formar)

if (*format =='%')

format ++;
if (*format == '\0')
return (-1)
if (*format == 'c')

count += _put char (va-arg(args ,int));
else if (*format =='s')
count + = print_string(va_va arg(args,char)
else if (*format =='%')
counr + = _putchar ('%')
else if (*format=='d' ||*format =='i')
count + = print _numbr (va_arg(args , int))
else
count + =_putchar ('%');

count + = _put char (*format);


else
count + = _putchar (*format);

format + + ;

va_end (args);
return (count);
