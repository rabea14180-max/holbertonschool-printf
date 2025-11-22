#include "main.h"
#include <stdlib.h>

/* Prototypes for internal helpers */
int print_char(va_list args, int width, int minus_flag);
int print_string(va_list args, int width, int precision, int minus_flag);
int print_percent(int width, int minus_flag);
int print_int(va_list args, int width, int plus_flag, int space_flag,
              int length, int precision);
int print_unsigned(va_list args, int width, int length, int precision,
                   int is_octal, int is_hex, int uppercase);

/* small helper */
static int max(int a, int b)
{
    return (a > b ? a : b);
}

/**
 * print_char - prints a single character with optional width / '-'
 */
int print_char(va_list args, int width, int minus_flag)
{
    char c;
    int count = 0;

    c = (char)va_arg(args, int);
    if (width < 1)
        width = 1;

    if (!minus_flag)
        while (--width > 0)
            count += _putchar(' ');

    count += _putchar(c);

    if (minus_flag)
        while (--width > 0)
            count += _putchar(' ');

    return (count);
}

/**
 * print_string - prints a string with width / precision / '-'
 */
int print_string(va_list args, int width, int precision, int minus_flag)
{
    char *s;
    int len = 0, i;

    s = va_arg(args, char *);
    if (!s)
        s = "(null)";

    while (s[len])
        len++;

    if (precision >= 0 && precision < len)
        len = precision;

    if (width < len)
        width = len;

    i = 0;
    if (!minus_flag)
        while (i++ < width - len)
            _putchar(' ');

    for (i = 0; i < len; i++)
        _putchar(s[i]);

    if (minus_flag)
        while (i++ < width)
            _putchar(' ');

    return (width);
}

/**
 * print_percent - prints a '%' with optional width / '-'
 */
int print_percent(int width, int minus_flag)
{
    int count = 0;

    if (width < 1)
        width = 1;

    if (!minus_flag)
        while (--width > 0)
            count += _putchar(' ');

    count += _putchar('%');

    if (minus_flag)
        while (--width > 0)
            count += _putchar(' ');

    return (count);
}

/**
 * print_int - prints signed integers (d / i)
 * Handles: width, precision, '+', ' ', 'l', 'h'
 */
int print_int(va_list args, int width, int plus_flag, int space_flag,
              int length, int precision)
{
    long n;
    unsigned long u;
    char buf[32];
    int i = 0, digits, total_len, pad, count = 0;
    int zero_prec = 0;
    char sign_char = 0;
    int has_precision = (precision >= 0);

    /* get value according to length modifier */
    if (length == 'l')
        n = va_arg(args, long);
    else if (length == 'h')
        n = (short)va_arg(args, int);
    else
        n = va_arg(args, int);

    /* sign handling */
    if (n < 0)
    {
        sign_char = '-';
        u = (unsigned long)(-n);
    }
    else
    {
        if (plus_flag)
            sign_char = '+';
        else if (space_flag)
            sign_char = ' ';
        u = (unsigned long)n;
    }

    /* special rule: precision == 0 && value == 0 -> print nothing */
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

    total_len = digits + zero_prec + (sign_char ? 1 : 0);
    if (width < total_len)
        width = total_len;

    pad = width - total_len;

    /* left spaces (no '0' flag في تاسك 11) */
    while (pad-- > 0)
        count += _putchar(' ');

    if (sign_char)
        count += _putchar(sign_char);

    while (zero_prec-- > 0)
        count += _putchar('0');

    while (digits-- > 0)
        count += _putchar(buf[digits]);

    return (count);
}

/**
 * print_unsigned - prints u / o / x / X with width & precision
 */
int print_unsigned(va_list args, int width, int length, int precision,
                   int is_octal, int is_hex, int uppercase)
{
    unsigned long n;
    char buf[32];
    int i = 0, base = 10, digits, total_len, pad, count = 0;
    int zero_prec = 0;
    int has_precision = (precision >= 0);

    if (length == 'l')
        n = va_arg(args, unsigned long);
    else if (length == 'h')
        n = (unsigned short)va_arg(args, unsigned int);
    else
        n = va_arg(args, unsigned int);

    if (is_octal)
        base = 8;
    else if (is_hex)
        base = 16;

    /* precision rule for zero */
    if (has_precision && precision == 0 && n == 0)
        digits = 0;
    else
    {
        if (n == 0)
            buf[i++] = '0';
        while (n > 0)
        {
            int digit = n % base;

            if (digit < 10)
                buf[i++] = (char)('0' + digit);
            else if (uppercase)
                buf[i++] = (char)('A' + (digit - 10));
            else
                buf[i++] = (char)('a' + (digit - 10));
            n /= base;
        }
        digits = i;
    }

    if (has_precision)
        zero_prec = max(precision - digits, 0);

    total_len = digits + zero_prec;
    if (width < total_len)
        width = total_len;

    pad = width - total_len;

    while (pad-- > 0)
        count += _putchar(' ');

    while (zero_prec-- > 0)
        count += _putchar('0');

    while (digits-- > 0)
        count += _putchar(buf[digits]);

    return (count);
}

/**
 * _printf - main function
 * Supports tasks 0..11 on non-custom specifiers.
 */
int _printf(const char *format, ...)
{
    va_list args;
    int i = 0, count = 0;

    int width, precision;
    int minus_flag, plus_flag, space_flag;
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

        /* we saw a '%' */
        i++;
        if (!format[i])
        {
            _putchar(-1);
            va_end(args);
            return (-1);
        }

        /* reset flags/state for this conversion */
        minus_flag = plus_flag = space_flag = 0;
        width = 0;
        precision = -1;  /* -1 means: precision not specified */
        length = 0;

        /* ----- flags: -, +, space ----- */
        while (format[i] == '-' || format[i] == '+' || format[i] == ' ')
        {
            if (format[i] == '-')
                minus_flag = 1;
            else if (format[i] == '+')
                plus_flag = 1;
            else if (format[i] == ' ')
                space_flag = 1;
            i++;
        }

        /* ----- field width ----- */
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

        /* ----- precision ----- */
        if (format[i] == '.')
        {
            i++;
            precision = 0;
            if (format[i] == '*')
            {
                precision = va_arg(args, int);
                if (precision < 0)
                    precision = -1; /* treat as “no precision” */
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

        /* ----- length modifier ----- */
        if (format[i] == 'l' || format[i] == 'h')
        {
            length = format[i];
            i++;
        }

        /* ----- specifier dispatch ----- */
        if (format[i] == 'c')
            count += print_char(args, width, minus_flag);
        else if (format[i] == 's')
            count += print_string(args, width, precision, minus_flag);
        else if (format[i] == '%')
            count += print_percent(width, minus_flag);
        else if (format[i] == 'd' || format[i] == 'i')
            count += print_int(args, width, plus_flag, space_flag,
                               length, precision);
        else if (format[i] == 'u')
            count += print_unsigned(args, width, length, precision, 0, 0, 0);
        else if (format[i] == 'o')
            count += print_unsigned(args, width, length, precision, 1, 0, 0);
        else if (format[i] == 'x')
            count += print_unsigned(args, width, length, precision, 0, 1, 0);
        else if (format[i] == 'X')
            count += print_unsigned(args, width, length, precision, 0, 1, 1);
        else
        {
            /* unknown specifier: print it literally like %q */
            count += _putchar('%');
            count += _putchar(format[i]);
        }

        i++;
    }

    _putchar(-1); /* flush buffer */
    va_end(args);
    return (count);
}
