#include "main.h"

/**
 * _putchar - buffered write of a single character
 * @c: character to print, or -1 to flush the buffer
 *
 * Return: 1 when writing a normal character.
 * When flushing (c == -1), returns number of bytes written by write().
 */
int _putchar(char c)
{
    static char buffer[1024];
    static int index;
    int written = 0;

    if (c == -1)
    {
        if (index > 0)
        {
            written = write(1, buffer, index);
            index = 0;
        }
        return (written);
    }

    buffer[index++] = c;
    if (index == 1024)
    {
        written = write(1, buffer, index);
        index = 0;
    }

    return (1);
}
