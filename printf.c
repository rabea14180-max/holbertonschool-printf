#include "main.h"

/* small helper */
static int max(int a, int b)
{
	return (a > b ? a : b);
}

/* ===================== basic helpers ===================== */

/**
 * print_char - prints a character with optional width and '-'
 * @args: argument list
 * @width: field width
 * @minus_flag: 1 if '-' flag is active
 *
 * Return: number of printed characters
 */
static int print_char(va_list args, int width, int minus_flag)
{
	char c;
	int i, count = 0;

	c = (char)va_arg(args, int);
	if (width < 1)
		width = 1;

	if (!minus_flag)
		for (i = 0; i < width - 1; i++)
			count += _putchar(' ');

	count += _putchar(c);

	if (minus_flag)
		for (i = 0; i < width - 1; i++)
			count += _putchar(' ');

	return (count);
}

/**
 * print_string - prints a string with width / precision / '-'
 * @args: argument list
 * @width: field width
 * @precision: max characters to print (-1 means all)
 * @minus_flag: 1 if '-' flag is active
 *
 * Return: number of printed characters
 */
static int print_string(va_list args, int width, int precision, int minus_flag)
{
	char *s;
	int len = 0, i, pad, to_print;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";

	while (s[len])
		len++;

	to_print = len;
	if (precision >= 0 && precision < len)
		to_print = precision;

	if (width < to_print)
		width = to_print;

	pad = width - to_print;

	if (!minus_flag)
		for (i = 0; i < pad; i++)
			_putchar(' ');

	for (i = 0; i < to_print; i++)
		_putchar(s[i]);

	if (minus_flag)
		for (i = 0; i < pad; i++)
			_putchar(' ');

	return (width);
}

/**
 * print_percent - prints '%' with width / '-'
 * @width: field width
 * @minus_flag: 1 if '-' flag is active
 *
 * Return: number of printed characters
 */
static int print_percent(int width, int minus_flag)
{
	int i, count = 0;

	if (width < 1)
		width = 1;

	if (!minus_flag)
		for (i = 0; i < width - 1; i++)
			count += _putchar(' ');

	count += _putchar('%');

	if (minus_flag)
		for (i = 0; i < width - 1; i++)
			count += _putchar(' ');

	return (count);
}

/* ===================== custom helpers ===================== */

/**
 * print_rev - prints a string in reverse order (%r)
 * @args: argument list
 *
 * Return: number of printed characters
 */
static int print_rev(va_list args)
{
	char *s;
	int len = 0, i, count = 0;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";

	while (s[len])
		len++;

	for (i = len - 1; i >= 0; i--)
		count += _putchar(s[i]);

	return (count);
}

/**
 * print_rot13 - prints a string using ROT13 (%R)
 * @args: argument list
 *
 * Return: number of printed characters
 */
static int print_rot13(va_list args)
{
	char *s;
	char ch;
	int i = 0, count = 0;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";

	while (s[i])
	{
		ch = s[i];

		if (ch >= 'a' && ch <= 'z')
			ch = (char)('a' + ((ch - 'a' + 13) % 26));
		else if (ch >= 'A' && ch <= 'Z')
			ch = (char)('A' + ((ch - 'A' + 13) % 26));

		count += _putchar(ch);
		i++;
	}

	return (count);
}

/**
 * print_binary - prints an unsigned int in binary (%b)
 * @args: argument list
 *
 * Return: number of printed characters
 */
static int print_binary(va_list args)
{
	unsigned int n = va_arg(args, unsigned int);
	char buf[32];
	int i = 0, digits, count = 0;

	if (n == 0)
	{
		return (_putchar('0'));
	}

	while (n > 0)
	{
		buf[i++] = (char)('0' + (n & 1));
		n >>= 1;
	}
	digits = i;

	while (digits-- > 0)
		count += _putchar(buf[digits]);

	return (count);
}

/**
 * print_S - prints a string, non printable as \xHH (%S)
 * @args: argument list
 *
 * Return: number of printed characters
 */
static int print_S(va_list args)
{
	char *s;
	unsigned char c;
	int i = 0, count = 0;
	int hi, lo;

	s = va_arg(args, char *);
	if (!s)
		s = "(null)";

	while (s[i])
	{
		c = (unsigned char)s[i];

		if ((c > 0 && c < 32) || c >= 127)
		{
			count += _putchar('\\');
			count += _putchar('x');

			hi = c / 16;
			lo = c % 16;

			count += _putchar(hi < 10 ? '0' + hi : 'A' + (hi - 10));
			count += _putchar(lo < 10 ? '0' + lo : 'A' + (lo - 10));
		}
		else
		{
			count += _putchar(c);
		}
		i++;
	}

	return (count);
}

/**
 * print_pointer - prints a pointer value in hex (%p)
 *                with width and '-' flag
 * @args: argument list
 * @width: field width
 * @minus_flag: 1 if '-' flag is active
 *
 * Return: number of printed characters
 */
static int print_pointer(va_list args, int width, int minus_flag)
{
	void *ptr = va_arg(args, void *);
	unsigned long n;
	char buf[32];
	int len = 0, i, count = 0, pad;
	int total_len;

	/* NULL pointer: print "(nil)" مع احترام الـ width */
	if (!ptr)
	{
		char *nil = "(nil)";

		while (nil[len])
			len++;

		if (width < len)
			width = len;

		pad = width - len;

		if (!minus_flag)
			for (i = 0; i < pad; i++)
				count += _putchar(' ');

		for (i = 0; i < len; i++)
			count += _putchar(nil[i]);

		if (minus_flag)
			for (i = 0; i < pad; i++)
				count += _putchar(' ');

		return (count);
	}

	n = (unsigned long)ptr;

	while (n > 0)
	{
		int d = n % 16;

		if (d < 10)
			buf[len++] = (char)('0' + d);
		else
			buf[len++] = (char)('a' + (d - 10));
		n /= 16;
	}

	total_len = len + 2; /* 2 for "0x" */

	if (width < total_len)
		width = total_len;

	pad = width - total_len;

	if (!minus_flag)
		for (i = 0; i < pad; i++)
			count += _putchar(' ');

	count += _putchar('0');
	count += _putchar('x');

	for (i = len - 1; i >= 0; i--)
		count += _putchar(buf[i]);

	if (minus_flag)
		for (i = 0; i < pad; i++)
			count += _putchar(' ');

	return (count);
}

/* ===================== integers (d / i) ===================== */

/**
 * print_int - prints signed integers with flags/width/precision
 * @args: argument list
 * @width: field width
 * @plus_flag: '+' flag
 * @space_flag: ' ' flag
 * @zero_flag: '0' flag
 * @minus_flag: '-' flag
 * @length: 0, 'l' or 'h'
 * @precision: precision (-1 means not specified)
 *
 * Return: number of printed characters
 */
static int print_int(va_list args, int width, int plus_flag, int space_flag,
		     int zero_flag, int minus_flag, int length, int precision)
{
	long n;
	unsigned long u;
	char buf[32];
	int i = 0, digits, has_precision, zero_prec = 0;
	int total_len, pad, pad_left, pad_right, count = 0;
	char sign_char = 0;

	if (length == 'l')
		n = va_arg(args, long);
	else if (length == 'h')
		n = (short)va_arg(args, int);
	else
		n = va_arg(args, int);

	if (n < 0)
	{
		sign_char = '-';
		u = (unsigned long)(-n);
	}
	else
	{
		u = (unsigned long)n;
		if (plus_flag)
			sign_char = '+';
		else if (space_flag)
			sign_char = ' ';
	}

	has_precision = (precision >= 0);

	if (has_precision && precision == 0 && u == 0)
		digits = 0;
	else
	{
		if (u == 0)
			buf[i++] = '0';
		while (u > 0)
		{
			buf[i++] = (char)('0' + (u % 10));
			u /= 10;
		}
		digits = i;
	}

	if (has_precision)
		zero_prec = max(precision - digits, 0);
	else if (zero_flag && !minus_flag &&
		 width > digits + (sign_char ? 1 : 0))
		zero_prec = width - (digits + (sign_char ? 1 : 0));

	total_len = digits + zero_prec + (sign_char ? 1 : 0);
	if (width < total_len)
		width = total_len;

	pad = width - total_len;
	if (pad < 0)
		pad = 0;

	pad_left = minus_flag ? 0 : pad;
	pad_right = minus_flag ? pad : 0;

	while (pad_left-- > 0)
		count += _putchar(' ');

	if (sign_char)
		count += _putchar(sign_char);

	while (zero_prec-- > 0)
		count += _putchar('0');

	while (digits-- > 0)
		count += _putchar(buf[digits]);

	while (pad_right-- > 0)
		count += _putchar(' ');

	return (count);
}

/* ===================== unsigned (u / o / x / X) ===================== */

/**
 * print_unsigned - prints unsigned numbers with all flags
 * @args: argument list
 * @width: field width
 * @length: 0, 'l', 'h'
 * @precision: precision (-1 means not specified)
 * @is_octal: 1 for %o
 * @is_hex: 1 for %x / %X
 * @uppercase: 1 for %X
 * @hash_flag: '#' flag
 * @zero_flag: '0' flag
 * @minus_flag: '-' flag
 *
 * Return: number of printed characters
 */
static int print_unsigned(va_list args, int width, int length, int precision,
			  int is_octal, int is_hex, int uppercase,
			  int hash_flag, int zero_flag, int minus_flag)
{
	unsigned long n;
	unsigned long tmp;
	char buf[32];
	int i = 0, base = 10, digits, has_precision;
	int zero_prec = 0, total_len, pad, pad_left, pad_right, count = 0;
	int value_is_zero, prefix_len = 0;

	if (length == 'l')
		n = va_arg(args, unsigned long);
	else if (length == 'h')
		n = (unsigned short)va_arg(args, unsigned int);
	else
		n = va_arg(args, unsigned int);

	value_is_zero = (n == 0);

	if (is_octal)
		base = 8;
	else if (is_hex)
		base = 16;

	has_precision = (precision >= 0);

	if (has_precision && precision == 0 && value_is_zero)
		digits = 0;
	else
	{
		if (n == 0)
			buf[i++] = '0';
		tmp = n;
		while (tmp > 0)
		{
			int d = tmp % base;

			if (d < 10)
				buf[i++] = (char)('0' + d);
			else if (uppercase)
				buf[i++] = (char)('A' + (d - 10));
			else
				buf[i++] = (char)('a' + (d - 10));
			tmp /= base;
		}
		digits = i;
	}

	if (hash_flag)
	{
		if (is_octal)
		{
			if (!value_is_zero ||
			    (has_precision && precision == 0))
				prefix_len = 1;
		}
		else if (is_hex && !value_is_zero)
			prefix_len = 2;
	}

	if (has_precision)
		zero_prec = max(precision - digits, 0);
	else if (zero_flag && !minus_flag &&
		 width > digits + prefix_len)
		zero_prec = width - (digits + prefix_len);

	total_len = digits + zero_prec + prefix_len;
	if (width < total_len)
		width = total_len;

	pad = width - total_len;
	if (pad < 0)
		pad = 0;

	pad_left = minus_flag ? 0 : pad;
	pad_right = minus_flag ? pad : 0;

	while (pad_left-- > 0)
		count += _putchar(' ');

	if (prefix_len == 1 && is_octal)
		count += _putchar('0');
	else if (prefix_len == 2 && is_hex)
	{
		count += _putchar('0');
		if (uppercase)
			count += _putchar('X');
		else
			count += _putchar('x');
	}

	while (zero_prec-- > 0)
		count += _putchar('0');

	while (digits-- > 0)
		count += _putchar(buf[digits]);

	while (pad_right-- > 0)
		count += _putchar(' ');

	return (count);
}

/* ======================= main _printf ======================= */

/**
 * _printf - custom printf (all tasks 0..16)
 * @format: format string
 *
 * Return: number of characters printed, or -1 on error
 */
int _printf(const char *format, ...)
{
	va_list args;
	int i = 0, count = 0;
	int width, precision;
	int minus_flag, plus_flag, space_flag, zero_flag, hash_flag;
	int length;

	if (!format)
		return (-1);

	va_start(args, format);

	while (format[i])
	{
		if (format[i] != '%')
		{
			count += _putchar(format[i]);
			i++;
			continue;
		}

		i++;
		if (!format[i])
		{
			_putchar(-1);
			va_end(args);
			return (-1);
		}

		width = 0;
		precision = -1;
		minus_flag = plus_flag = space_flag = zero_flag = hash_flag = 0;
		length = 0;

		/* ---------- flags ---------- */
		while (format[i] == '-' || format[i] == '+' || format[i] == ' ' ||
		       format[i] == '0' || format[i] == '#')
		{
			if (format[i] == '-')
				minus_flag = 1;
			else if (format[i] == '+')
				plus_flag = 1;
			else if (format[i] == ' ')
				space_flag = 1;
			else if (format[i] == '0')
				zero_flag = 1;
			else if (format[i] == '#')
				hash_flag = 1;
			i++;
		}

		/* ---------- width ---------- */
		if (format[i] == '*')
		{
			width = va_arg(args, int);
			if (width < 0)
			{
				minus_flag = 1;
				width = -width;
			}
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

		/* ---------- precision ---------- */
		if (format[i] == '.')
		{
			i++;
			precision = 0;
			if (format[i] == '*')
			{
				precision = va_arg(args, int);
				if (precision < 0)
					precision = -1;
				i++;
			}
			else
			{
				while (format[i] >= '0' && format[i] <= '9')
				{
					precision = precision * 10 + (format[i] - '0');
					i++;
				}
			}
		}

		/* ---------- length modifiers ---------- */
		if (format[i] == 'l' || format[i] == 'h')
		{
			length = format[i];
			i++;
		}

		/* ---------- specifier ---------- */
		if (format[i] == 'c')
			count += print_char(args, width, minus_flag);
		else if (format[i] == 's')
			count += print_string(args, width, precision, minus_flag);
		else if (format[i] == '%')
			count += print_percent(width, minus_flag);
		else if (format[i] == 'b')
			count += print_binary(args);
		else if (format[i] == 'S')
			count += print_S(args);
		else if (format[i] == 'p')
			count += print_pointer(args, width, minus_flag);
		else if (format[i] == 'r')
			count += print_rev(args);
		else if (format[i] == 'R')
			count += print_rot13(args);
		else if (format[i] == 'd' || format[i] == 'i')
			count += print_int(args, width, plus_flag, space_flag,
					   zero_flag, minus_flag,
					   length, precision);
		else if (format[i] == 'u')
			count += print_unsigned(args, width, length, precision,
						0, 0, 0, hash_flag,
						zero_flag, minus_flag);
		else if (format[i] == 'o')
			count += print_unsigned(args, width, length, precision,
						1, 0, 0, hash_flag,
						zero_flag, minus_flag);
		else if (format[i] == 'x')
			count += print_unsigned(args, width, length, precision,
						0, 1, 0, hash_flag,
						zero_flag, minus_flag);
		else if (format[i] == 'X')
			count += print_unsigned(args, width, length, precision,
						0, 1, 1, hash_flag,
						zero_flag, minus_flag);
		else
		{
			/* unknown specifier: print '%' and the char */
			count += _putchar('%');
			count += _putchar(format[i]);
		}

		i++;
	}

	_putchar(-1); /* flush buffer */
	va_end(args);
	return (count);
}
