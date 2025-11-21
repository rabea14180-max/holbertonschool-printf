#include "main.h"

/**
 * _putchar - buffered character output
 * @c: character to print; if c is -1, flush the internal buffer
 *
 * Return: 1 on success, or -1 on write error
 */
int _putchar(char c)
{
	static char buffer[1024];
	static int index;
	int written;

	/* Flush request: c == -1 (used at the end of _printf) */
	if (c == -1)
	{
		if (index > 0)
		{
			written = write(1, buffer, index);
			index = 0;
			if (written == -1)
				return (-1);
		}
		return (1);
	}

	/* Store character in the local buffer */
	buffer[index++] = c;

	/* If buffer is full, write it out and reset index */
	if (index == 1024)
	{
		written = write(1, buffer, index);
		index = 0;
		if (written == -1)
			return (-1);
	}

	return (1);
}
