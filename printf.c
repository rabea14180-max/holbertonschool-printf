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
