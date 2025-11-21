#include "main.h"

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
 * print_S - prints a string, replacing non-printable chars
 *           with \xHH (uppercase hex, always 2 digits)
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_S(va_list args)
{
	char *str;
	int i, count;
	unsigned char c;
	char *hex = "0123456789ABCDEF";

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

	count = 0;

	for (i = 0; str[i] != '\0'; i++)
	{
		c = (unsigned char)str[i];

		if (c > 0 && (c < 32 || c >= 127))
		{
			_putchar('\\');
			_putchar('x');
			_putchar(hex[c / 16]);
			_putchar(hex[c % 16]);
			count += 4;
		}
		else
		{
			_putchar(c);
			count++;
		}
	}

	return (count);
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
		num = (unsigned int)(-(long)n);
	}
	else
	{
		num = (unsigned int)n;
	}

	i = 0;
	do {
		buffer[i] = (char)((num % 10) + '0');
		i++;
		num /= 10;
	} while (num > 0);

	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
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
 * print_unsigned - prints an unsigned int in decimal
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list args)
{
	unsigned int n;
	char buffer[12];
	int i, count;

	n = va_arg(args, unsigned int);

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 12)
	{
		buffer[i] = (char)((n % 10) + '0');
		n /= 10;
		i++;
	}

	count = 0;
	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
}

/**
 * print_octal - prints an unsigned int in octal
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 */
int print_octal(va_list args)
{
	unsigned int n;
	char buffer[32];
	int i, count;

	n = va_arg(args, unsigned int);

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 32)
	{
		buffer[i] = (char)((n % 8) + '0');
		n /= 8;
		i++;
	}

	count = 0;
	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
}

/**
 * print_hex_lower - prints an unsigned int in lowercase hexadecimal
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list args)
{
	unsigned int n;
	char buffer[32];
	char *digits = "0123456789abcdef";
	int i, count;

	n = va_arg(args, unsigned int);

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 32)
	{
		buffer[i] = digits[n % 16];
		n /= 16;
		i++;
	}

	count = 0;
	while (i > 0)
	{
		i--;
		_putchar(buffer[i]);
		count++;
	}

	return (count);
}

/**
 * print_hex_upper - prints an unsigned int in uppercase hexadecimal
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list args)
{
	unsigned int n;
	char buffer[32];
	char *digits = "0123456789ABCDEF";
	int i, count;

	n = va_arg(args, unsigned int);

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 32)
	{
		buffer[i] = digits[n % 16];
		n /= 16;
		i++;
	}

	count = 0;
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
				_putchar(-1);
				return (-1);
			}

			if (format[i] == 'c')
				count += print_char(args);
			else if (format[i] == 's')
				count += print_string(args);
			else if (format[i] == 'S')
				count += print_S(args);
			else if (format[i] == '%')
				count += print_percent();
			else if (format[i] == 'd' || format[i] == 'i')
				count += print_int(args);
			else if (format[i] == 'b')
				count += print_binary(args);
			else if (format[i] == 'u')
				count += print_unsigned(args);
			else if (format[i] == 'o')
				count += print_octal(args);
			else if (format[i] == 'x')
				count += print_hex_lower(args);
			else if (format[i] == 'X')
				count += print_hex_upper(args);
			else
			{
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
	_putchar(-1); /* flush buffered output */

	return (count);
}
