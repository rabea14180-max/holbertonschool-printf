#include "main.h"

/**
 * print_int - prints a signed integer
 * @args: argument list
 *
 * Return: number of characters printed
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

		/* Cast to long to safely handle INT_MIN before converting to unsigned */
	
		num = (unsigned int)(-(long)n);
	}
	else
	{
		num = (unsigned int)n;
	}

	i = 0;

	do {
		buffer[i++] = (char)((num % 10) + '0');
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
