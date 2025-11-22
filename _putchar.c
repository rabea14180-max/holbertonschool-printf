#include "main.h"

/**
 * _putchar - buffered character output
 * @c: character to write, or -1 to flush the buffer
 *
 * Return: 1 on success
 */
int _putchar(char c)
{
	static char buffer[1024];
	static int index;

	if (c == -1 || index == 1024)
	{
		if (index > 0)
			write(1, buffer, index);
		index = 0;
	}

	if (c != -1)
	{
		buffer[index] = c;
		index++;
	}

	return (1);
}
