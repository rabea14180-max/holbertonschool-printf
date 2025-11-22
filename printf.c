#include "main.h"

/**
 * print_char - prints a character with optional field width
 * @args: argument list
 * @width: minimum field width
 *
 * Return: number of characters printed
 */
int print_char(va_list args, int width)
{
	char c;
	int count = 0, pad;

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
 * @width: minimum field width
 *
 * Return: number of characters printed
 */
int print_string(va_list args, int width)
{
	char *str;
	int len = 0, pad, count = 0, i;

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
 * print_S - prints a string, replacing non-printable chars with \xHH
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_S(va_list args)
{
	char *str;
	unsigned char c;
	char *hex = "0123456789ABCDEF";
	int i, count = 0;

	str = va_arg(args, char *);
	if (str == NULL)
		str = "(null)";

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
 * print_percent - prints '%' with optional field width
 * @width: minimum field width
 *
 * Return: number of characters printed
 */
int print_percent(int width)
{
	int pad, count = 0;

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
 * print_int - prints a signed integer with + and space flags and width
 * @args: argument list
 * @width: minimum field width
 * @plus_flag: if non-zero, print '+' for positive numbers
 * @space_flag: if non-zero, print leading space for positive numbers
 * @length: 0=int, 1=long, 2=short
 *
 * Return: number of characters printed
 */
int print_int(va_list args, int width, int plus_flag,
	      int space_flag, int length)
{
	long int n;
	unsigned long int u;
	char buf[32];
	int i, digits, pad, total_len, count = 0;
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
		u = (unsigned long int)(-n);
	}
	else
	{
		u = (unsigned long int)n;
		if (plus_flag)
			sign_char = '+';
		else if (space_flag)
			sign_char = ' ';
	}

	i = 0;
	do {
		buf[i] = (char)((u % 10) + '0');
		u /= 10;
		i++;
	} while (u > 0);
	digits = i;

	total_len = digits + (sign_char ? 1 : 0);
	if (width < total_len)
		width = total_len;

	pad = width - total_len;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	if (sign_char)
	{
		_putchar(sign_char);
		count++;
	}

	while (digits > 0)
	{
		digits--;
		_putchar(buf[digits]);
		count++;
	}

	return (count);
}

/**
 * print_binary - prints an unsigned int in binary (no width)
 * @args: argument list
 *
 * Return: number of characters printed
 */
int print_binary(va_list args)
{
	unsigned int n;
	char buf[32];
	int i, count = 0;

	n = va_arg(args, unsigned int);

	if (n == 0)
	{
		_putchar('0');
		return (1);
	}

	i = 0;
	while (n > 0 && i < 32)
	{
		buf[i] = (char)((n & 1) + '0');
		n >>= 1;
		i++;
	}

	while (i > 0)
	{
		i--;
		_putchar(buf[i]);
		count++;
	}

	return (count);
}

/**
 * print_unsigned - prints an unsigned decimal with width and length
 * @args: argument list
 * @width: minimum field width
 * @length: 0=unsigned int, 1=unsigned long, 2=unsigned short
 *
 * Return: number of characters printed
 */
int print_unsigned(va_list args, int width, int length)
{
	unsigned long int n;
	char buf[32];
	int i, digits, pad, count = 0;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buf[i] = (char)((n % 10) + '0');
		n /= 10;
		i++;
	} while (n > 0);
	digits = i;

	if (width < digits)
		width = digits;

	pad = width - digits;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	while (digits > 0)
	{
		digits--;
		_putchar(buf[digits]);
		count++;
	}

	return (count);
}

/**
 * print_octal - prints an unsigned integer in octal with # flag and width
 * @args: argument list
 * @width: minimum field width
 * @hash_flag: if non-zero, prefix with 0 when value != 0
 * @length: 0=uint,1=ulong,2=ushort
 *
 * Return: number of characters printed
 */
int print_octal(va_list args, int width, int hash_flag, int length)
{
	unsigned long int n;
	char buf[32];
	int i, digits, pad, count = 0;
	int prefix_len = 0;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buf[i] = (char)((n % 8) + '0');
		n /= 8;
		i++;
	} while (n > 0);
	digits = i;

	if (hash_flag && buf[digits - 1] != '0')
		prefix_len = 1;

	if (width < digits + prefix_len)
		width = digits + prefix_len;

	pad = width - digits - prefix_len;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	if (prefix_len == 1)
	{
		_putchar('0');
		count++;
	}

	while (digits > 0)
	{
		digits--;
		_putchar(buf[digits]);
		count++;
	}

	return (count);
}

/**
 * print_hex_lower - prints unsigned int in lowercase hex with # and width
 * @args: argument list
 * @width: minimum field width
 * @hash_flag: if non-zero, prefix with 0x when value != 0
 * @length: 0=uint,1=ulong,2=ushort
 *
 * Return: number of characters printed
 */
int print_hex_lower(va_list args, int width, int hash_flag, int length)
{
	unsigned long int n;
	char buf[32];
	char *digits_tab = "0123456789abcdef";
	int i, digits, pad, count = 0;
	int prefix_len = 0;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buf[i] = digits_tab[n % 16];
		n /= 16;
		i++;
	} while (n > 0);
	digits = i;

	if (hash_flag && !(digits == 1 && buf[0] == '0'))
		prefix_len = 2;

	if (width < digits + prefix_len)
		width = digits + prefix_len;

	pad = width - digits - prefix_len;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	if (prefix_len == 2)
	{
		_putchar('0');
		_putchar('x');
		count += 2;
	}

	while (digits > 0)
	{
		digits--;
		_putchar(buf[digits]);
		count++;
	}

	return (count);
}

/**
 * print_hex_upper - prints unsigned int in UPPERCASE hex with # and width
 * @args: argument list
 * @width: minimum field width
 * @hash_flag: if non-zero, prefix with 0X when value != 0
 * @length: 0=uint,1=ulong,2=ushort
 *
 * Return: number of characters printed
 */
int print_hex_upper(va_list args, int width, int hash_flag, int length)
{
	unsigned long int n;
	char buf[32];
	char *digits_tab = "0123456789ABCDEF";
	int i, digits, pad, count = 0;
	int prefix_len = 0;

	if (length == 1)
		n = va_arg(args, unsigned long int);
	else if (length == 2)
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	i = 0;
	do {
		buf[i] = digits_tab[n % 16];
		n /= 16;
		i++;
	} while (n > 0);
	digits = i;

	if (hash_flag && !(digits == 1 && buf[0] == '0'))
		prefix_len = 2;

	if (width < digits + prefix_len)
		width = digits + prefix_len;

	pad = width - digits - prefix_len;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	if (prefix_len == 2)
	{
		_putchar('0');
		_putchar('X');
		count += 2;
	}

	while (digits > 0)
	{
		digits--;
		_putchar(buf[digits]);
		count++;
	}

	return (count);
}

/**
 * print_pointer - prints a pointer value in hex with optional width
 * @args: argument list
 * @width: minimum field width
 *
 * Return: number of characters printed
 */
int print_pointer(va_list args, int width)
{
	void *ptr;
	unsigned long addr;
	char buf[32];
	char *digits = "0123456789abcdef";
	int i, digits_len, pad, count = 0;
	char *nil_str = "(nil)";
	int nil_len = 5, j;

	ptr = va_arg(args, void *);
	if (ptr == NULL)
	{
		if (width < nil_len)
			width = nil_len;

		pad = width - nil_len;
		while (pad > 0)
		{
			_putchar(' ');
			count++;
			pad--;
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
		buf[i] = digits[addr % 16];
		addr /= 16;
		i++;
	} while (addr > 0);
	digits_len = i;

	if (width < digits_len + 2)
		width = digits_len + 2;

	pad = width - digits_len - 2;

	while (pad > 0)
	{
		_putchar(' ');
		count++;
		pad--;
	}

	_putchar('0');
	_putchar('x');
	count += 2;

	while (digits_len > 0)
	{
		digits_len--;
		_putchar(buf[digits_len]);
		count++;
	}

	return (count);
}

/**
 * _printf - produces output according to a format
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i, count = 0;
	int plus_flag, space_flag, hash_flag;
	int length, width;

	if (format == NULL)
		return (-1);

	va_start(args, format);

	for (i = 0; format[i] != '\0'; i++)
	{
		if (format[i] != '%')
		{
			_putchar(format[i]);
			count++;
			continue;
		}

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

		/* ---- flags: +, space, # ---- */
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

		/* ---- field width (digits or *) ---- */
		width = 0;
		if (format[i] == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
				width = -width;
			i++;
		}
		else
		{
			while (format[i] >= '0' && format[i] <= '9')
			{
				width = width * 10 + (format[i] - '0');
				i++;
			}
		}

		/* ---- length modifier: l or h ---- */
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

		/* ---- conversion specifier ---- */
		if (format[i] == 'c')
			count += print_char(args, width);
		else if (format[i] == 's')
			count += print_string(args, width);
		else if (format[i] == 'S')
			count += print_S(args);
		else if (format[i] == '%')
			count += print_percent(width);
		else if (format[i] == 'd' || format[i] == 'i')
			count += print_int(args, width, plus_flag,
					   space_flag, length);
		else if (format[i] == 'b')
			count += print_binary(args);
		else if (format[i] == 'u')
			count += print_unsigned(args, width, length);
		else if (format[i] == 'o')
			count += print_octal(args, width, hash_flag, length);
		else if (format[i] == 'x')
			count += print_hex_lower(args, width, hash_flag, length);
		else if (format[i] == 'X')
			count += print_hex_upper(args, width, hash_flag, length);
		else if (format[i] == 'p')
			count += print_pointer(args, width);
		else
		{
			/* unknown specifier: print as-is */
			_putchar('%');
			_putchar(format[i]);
			count += 2;
		}
	}

	va_end(args);
	_putchar(-1); /* flush buffer */

	return (count);
}
