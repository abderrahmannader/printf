#include "main.h"

/** PRINT UNSIGNED NUMBER **/
/**
 * print_octal - unsigned number
 * @types: List argu
 * @buffer: arr handle
 * @flags: Calc flag
 * @width: width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numbe char
 */
int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN OCTAL  ****/
/**
 * print_octal - unsigned number in octal
 * @types: List argu
 * @buffer: arr handle
 * @flags: Calc flag
 * @width: width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numbe char
 */
int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/** PRINT UNSIGNED NUMBER IN HEXADECIMAL **/
/**
 * print_hexadecimal - unsigned number in hexadecimal
 * @types: List argu
 * @buffer: arr handle
 * @flags: Calc flag
 * @width: width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numbe char
 */
int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL **/
/**
 * print_hexa_upper - unsigned number in upper hexadecimal notation
 * @types: List argu
 * @buffer: arr handle
 * @flags: Calc flag
 * @width: width
 * @precision: Prec specific
 * @size: Size spec
 * Return: Numbe char
 */
int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/* PRINT HEXX NUM IN LOWER OR UPPER */
/**
 * print_hexa - hexadecimal number in lower or upper
 * @types: List argu
 * @map_to: Arr number
 * @buffer: arr handle
 * @flags: Calc flag
 * @flag_ch: Calcu flag
 * @width: width
 * @precision: Prec specific
 * @size: Size spec
 * @size: Size spec
 * Return: Numbe char
 */
int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
