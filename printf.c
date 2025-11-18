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


	return (count);
}
