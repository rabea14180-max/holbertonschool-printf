#include "main.h"

/**
 * print_int - prints a signed integer using _putchar
 * @args: argument list containing the integer to print
 *
 * Return: number of characters printed (including sign if negative)
 */
int print_int(va_list args)
{
	int n;
	unsigned int num;
	int count;
	char buffer[12];
	int i;

	n = va_arg(args, int);
	count = 0;

	if (n < 0)
	{
		_putchar('-');
		count++;
		/* Cast to long to safely handle INT_MIN before converting */
		num = (unsigned int)(-(long)n);
	}
	else
	{
		num = (unsigned int)n;
	}

	i = 0;
	/* Store digits in reverse order in buffer */
	do {
		buffer[i] = (char)((num % 10) + '0');
		i++;
		num /= 10;
	} while (num > 0);

	/* Print digits in the correct order */
	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
}

/**
 * print_char - prints a character
 * @args: argument list
 *
 * Return: number of characters printed (1)
 */
int print_char(va_list args)
{
	char c;

	c = (char)va_arg(args, int);
	_putchar(c);

	return (1);
}

/**
 * print_string - prints a string
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_string(va_list args)
{
	char *str;
	int i;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);

	return (i);
}

/**
 * print_percent - prints the character '%'
 *
 * Return: number of characters printed (1)
 */
int print_percent(void)
{
	_putchar('%');

	return (1);
}

/**
 * print_binary - prints an unsigned int in binary
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 */
int print_binary(va_list args)
{
	unsigned int n;
	char buffer[32];
	int i, count;

	n = va_arg(args, unsigned int);
	count = 0;

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 32)
	{
		buffer[i] = (char)((n & 1) + '0');
		n >>= 1;
		i++;
	}

	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string containing characters and specifiers
 *
 * Return: number of characters printed (excluding the null byte),
 *         or -1 if format is NULL or if an incomplete
 *         format specifier is found.
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i;
	int count;

	if (format == NULL)
		return (-1);

	va_start(args, format);
	count = 0;

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] == '%')
		{
			i++;
			if (format[i] == '\0')
			{
				va_end(args);
				return (-1);
			}

			if (format[i] == 'c')
				count += print_char(args);
			else if (format[i] == 's')
				count += print_string(args);
			else if (format[i] == '%')
				count += print_percent();
			else if (format[i] == 'd' || format[i] == 'i')
				count += print_int(args);
			else if (format[i] == 'b')
				count += print_binary(args);
			else
			{
				/*
				 * For unsupported specifiers, print the
				 * percent sign and the character as-is.
				 */
				_putchar('%');
				_putchar(format[i]);
				count += 2;
			}
		}
		else
		{
			_putchar(format[i]);
			count++;
		}
	}

	va_end(args);
	return (count);
}
