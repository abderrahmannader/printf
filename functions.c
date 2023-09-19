#include "main.h"
/* PRINT CHAR */
/**
 * print_char - P char
 * @types: argu list
 * @buffer: arr print
 * @flags:  Calcu act flags
 * @width: value Width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numb print
 */
int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c = va_arg(types, int);

	return (handle_write_char(c, buffer, width, flags, precision, size));
}

/* Print String */
/**
 * print_string - prt str
 * @types: argu list
 * @buffer: arr print
 * @flags:  Calcu act flags
 * @width: value Width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numb print
 */
int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int len = 0;
	int x;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}

	while (str[len] != '\0')
		len++;

	if (precision >= 0 && precision < len)
		len = precision;

	if (width > len)
	{
		if (flags & F_MINUS)
		{
			write(2, &str[0], len);
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (x = width - len; x > 0; x--)
				write(1, " ", 1);
			write(1, &str[0], len);
			return (width);
		}
	}
	return (write(1, str, len));
}

/* PRINT PERCENT SIGN */
/**
 * print_string - prt str
 * @types: argu list
 * @buffer: arr print
 * @flags:  Calcu act flags
 * @width: value Width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numb print
 */
int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/* PRINT INT */
/**
 * print_string - prt str
 * @types: argu list
 * @buffer: arr print
 * @flags:  Calcu act flags
 * @width: value Width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numb print
 */
int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int int_neg = 0;
	int x = BUFF_SIZE - 2;
	unsigned long int numb;
	long int y = va_arg(types, long int);

	y = convert_size_number(y, size);

	if (y == 0)
		buffer[x--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	numb = (unsigned long int)y;

	if (y < 0)
	{
		numb = (unsigned long int)((-1) * y);
		int_neg = 1;
	}

	while (numb > 0)
	{
		buffer[x--] = (numb % 10) + '0';
		numb /= 10;
	}

	x++;

	return (write_number(int_neg, x, buffer, flags, width, precision, size));
}

/* PRINT BINARY */
/**
 * print_string - prt str
 * @types: argu list
 * @buffer: arr print
 * @flags:  Calcu act flags
 * @width: value Width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numb print
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, z, sum;
	unsigned int arr[32];
	int coun;

	x = va_arg(types, unsigned int);
	y = 2147483648; /* (2 ** 31) */

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	arr[0] = x / y;
	for (z = 1; z < 32; z++)
	{
		y /= 2;
		arr[z] = (x / y) % 2;
	}
	for (z = 0, sum = 0, coun = 0; z < 32; z++)
	{
		sum += arr[z];
		if (sum || z == 31)
		{
			char z = '0' + arr[z];

			write(1, &z, 1);
			coun++;
		}
	}
	return (coun);
}

