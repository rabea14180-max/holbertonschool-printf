#include "main.h"

/**
 * print_char - prints a character with optional field width
 * @args: argument list
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_char(va_list args, int width)
{
	char c;
	int count = 0;
	int pad;

	c = (char)va_arg(args, int);

	if (width < 1)
		width = 1;

	pad = width - 1;
	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	_putchar(c);
	count++;

	return (count);
}

/**
 * print_string - prints a string with optional field width
 * @args: argument list
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_string(va_list args, int width)
{
	char *str;
	int len = 0, i, count = 0, pad;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

	while (str[len] != '\0')
		len++;

	if (width < len)
		width = len;

	pad = width - len;
	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	for (i = 0; i < len; i++)
	{
		_putchar(str[i]);
		count++;
	}

	return (count);
}

/**
 * print_S - prints a string, replacing non-printable chars
 *           with \xHH (uppercase hex, always 2 digits)
 * @args: argument list
 *
 * Return: number of characters printed
 *
 * Note: field width is not handled for this custom specifier.
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
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_percent(int width)
{
	int count = 0;
	int pad;

	if (width < 1)
		width = 1;

	pad = width - 1;
	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	_putchar('%');
	count++;

	return (count);
}

/**
 * print_int - prints a signed integer with optional flags and width
 * @args: argument list containing the integer to print
 * @plus_flag: if non-zero, print '+' for positive numbers
 * @space_flag: if non-zero and plus_flag is 0, print leading space
 * @length: 0 for int, 1 for long, 2 for short
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed (including sign if any)
 */
int print_int(va_list args, int plus_flag, int space_flag,
	      int length, int width)
{
	long int n;
	unsigned long int num;
	int count = 0;
	char buffer[32];
	int i, digits, total_len;
	char sign_char = 0;

	if (length == 1)
		n = va_arg(args, long int);
	else if (length == 2)
		n = (short)va_arg(args, int);
	else
		n = va_arg(args, int);

	if (n < 0)
	{
		sign_char = '-';
		num = (unsigned long int)(-(long)n);
	}
	else
	{
		if (plus_flag)
			sign_char = '+';
		else if (space_flag)
			sign_char = ' ';
		num = (unsigned long int)n;
	}

	i = 0;
	do {
		buffer[i] = (char)((num % 10) + '0');
		i++;
		num /= 10;
	} while (num > 0);

	digits = i;
	total_len = digits + (sign_char ? 1 : 0);

	if (width < total_len)
		width = total_len;

	while (width > total_len)
	{
		_putchar(' ');
		count++;
		width--;
	}

	if (sign_char)
	{
		_putchar(sign_char);
		count++;
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
 * print_binary - prints an unsigned int in binary
 * @args: argument list containing the unsigned int to print
 *
 * Return: number of characters printed
 *
 * Note: field width is not handled for this custom specifier.
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
 * print_unsigned - prints an unsigned integer in decimal
 * @args: argument list containing the value to print
 * @length: 0 for unsigned int, 1 for unsigned long, 2 for unsigned short
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list args, int length, int width)
{
	unsigned long int n;
	char buffer[32];
	int i, digits, count = 0;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buffer[i] = (char)((n % 10) + '0');
		i++;
		n /= 10;
	} while (n > 0);

	digits = i;

	if (width < digits)
		width = digits;

	while (width > digits)
	{
		_putchar(' ');
		count++;
		width--;
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
 * print_octal - prints an unsigned int in octal, with optional '#'
 * @args: argument list containing the value to print
 * @hash_flag: if non-zero and number != 0, prefix with '0'
 * @length: 0 for unsigned int, 1 for unsigned long, 2 for unsigned short
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_octal(va_list args, int hash_flag, int length, int width)
{
	unsigned long int n;
	char buffer[32];
	int i, digits, count = 0, prefix_len = 0, total_len;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buffer[i] = (char)((n % 8) + '0');
		i++;
		n /= 8;
	} while (n > 0);

	digits = i;

	if (hash_flag && buffer[digits - 1] != '0')
		prefix_len = 1;

	total_len = digits + prefix_len;

	if (width < total_len)
		width = total_len;

	while (width > total_len)
	{
		_putchar(' ');
		count++;
		width--;
	}

	if (prefix_len == 1)
	{
		_putchar('0');
		count++;
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
 * print_hex_lower - prints an unsigned int in lowercase hexadecimal,
 *                   with optional '#'
 * @args: argument list containing the value to print
 * @hash_flag: if non-zero and number != 0, prefix with 0x
 * @length: 0 for unsigned int, 1 for unsigned long, 2 for unsigned short
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list args, int hash_flag, int length, int width)
{
	unsigned long int n;
	char buffer[32];
	char *digits_tab = "0123456789abcdef";
	int i, digits, count = 0, prefix_len = 0, total_len;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buffer[i] = digits_tab[n % 16];
		i++;
		n /= 16;
	} while (n > 0);

	digits = i;

	if (hash_flag && !(digits == 1 && buffer[0] == '0'))
		prefix_len = 2;

	total_len = digits + prefix_len;

	if (width < total_len)
		width = total_len;

	while (width > total_len)
	{
		_putchar(' ');
		count++;
		width--;
	}

	if (prefix_len == 2)
	{
		_putchar('0');
		_putchar('x');
		count += 2;
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
 * print_hex_upper - prints an unsigned int in uppercase hexadecimal,
 *                   with optional '#'
 * @args: argument list containing the value to print
 * @hash_flag: if non-zero and number != 0, prefix with 0X
 * @length: 0 for unsigned int, 1 for unsigned long, 2 for unsigned short
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list args, int hash_flag, int length, int width)
{
	unsigned long int n;
	char buffer[32];
	char *digits_tab = "0123456789ABCDEF";
	int i, digits, count = 0, prefix_len = 0, total_len;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buffer[i] = digits_tab[n % 16];
		i++;
		n /= 16;
	} while (n > 0);

	digits = i;

	if (hash_flag && !(digits == 1 && buffer[0] == '0'))
		prefix_len = 2;

	total_len = digits + prefix_len;

	if (width < total_len)
		width = total_len;

	while (width > total_len)
	{
		_putchar(' ');
		count++;
		width--;
	}

	if (prefix_len == 2)
	{
		_putchar('0');
		_putchar('X');
		count += 2;
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
 * print_pointer - prints a pointer address in hexadecimal with width
 * @args: argument list containing the pointer to print
 * @width: minimum field width (pads with spaces on the left)
 *
 * Return: number of characters printed
 */
int print_pointer(va_list args, int width)
{
	void *ptr;
	unsigned long addr;
	char buffer[32];
	char *digits = "0123456789abcdef";
	int i, digits_len, count = 0, total_len;
	char *nil_str = "(nil)";
	int j;

	ptr = va_arg(args, void *);
	if (ptr == NULL)
	{
		int nil_len = 5;

		if (width < nil_len)
			width = nil_len;

		while (width > nil_len)
		{
			_putchar(' ');
			count++;
			width--;
		}

		for (j = 0; j < nil_len; j++)
		{
			_putchar(nil_str[j]);
			count++;
		}
		return (count);
	}

	addr = (unsigned long)ptr;

	i = 0;
	do {
		buffer[i] = digits[addr % 16];
		i++;
		addr /= 16;
	} while (addr > 0);

	digits_len = i;
	total_len = 2 + digits_len; /* "0x" + digits */

	if (width < total_len)
		width = total_len;

	while (width > total_len)
	{
		_putchar(' ');
		count++;
		width--;
	}

	_putchar('0');
	_putchar('x');
	count += 2;

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
	int i, count;
	int plus_flag, space_flag, hash_flag;
	int length;
	int width;

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

			plus_flag = 0;
			space_flag = 0;
			hash_flag = 0;

			while (format[i] == '+' || format[i] == ' ' || format[i] == '#')
			{
				if (format[i] == '+')
					plus_flag = 1;
				else if (format[i] == ' ')
					space_flag = 1;
				else if (format[i] == '#')
					hash_flag = 1;
				i++;
			}

			width = 0;
			while (format[i] >= '0' && format[i] <= '9')
			{
				width = width * 10 + (format[i] - '0');
				i++;
			}

			length = 0;
			if (format[i] == 'l')
			{
				length = 1;
				i++;
			}
			else if (format[i] == 'h')
			{
				length = 2;
				i++;
			}

			if (format[i] == '\0')
			{
				va_end(args);
				_putchar(-1);
				return (-1);
			}

			if (format[i] == 'c')
				count += print_char(args, width);
			else if (format[i] == 's')
				count += print_string(args, width);
			else if (format[i] == 'S')
				count += print_S(args);
			else if (format[i] == '%')
				count += print_percent(width);
			else if (format[i] == 'd' || format[i] == 'i')
				count += print_int(args, plus_flag, space_flag,
						   length, width);
			else if (format[i] == 'b')
				count += print_binary(args);
			else if (format[i] == 'u')
				count += print_unsigned(args, length, width);
			else if (format[i] == 'o')
				count += print_octal(args, hash_flag,
						     length, width);
			else if (format[i] == 'x')
				count += print_hex_lower(args, hash_flag,
							 length, width);
			else if (format[i] == 'X')
				count += print_hex_upper(args, hash_flag,
							 length, width);
			else if (format[i] == 'p')
				count += print_pointer(args, width);
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
