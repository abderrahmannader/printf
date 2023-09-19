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
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/************************* PRINT BINARY *************************/
/**
 * print_binary - Prints an unsigned number
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * Return: Numbers of char printed.
 */
int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int n, m, i, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	n = va_arg(types, unsigned int);
	m = 2147483648; /* (2 ^ 31) */
	a[0] = n / m;
	for (i = 1; i < 32; i++)
	{
		m /= 2;
		a[i] = (n / m) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
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

