#include "main.h"

/**
 * handle_unknown - Handles unknown format specifiers
 * @fmt: Formatted string in which to print the arguments.
 * @ind: Pointer to index of current character being processed in fmt.
 *
 * Return: Number of characters printed.
 */

int handle_unknown(const char *fmt, int *ind)
{
	int unknown_len = 0;

	/* Print the percent sign and any preceding space */
	unknown_len += write(1, "%%", 1);
	if (fmt[*ind - 1] == ' ')
		unknown_len += write(1, " ", 1);

	/* If a width is specified, skip the unknown format specifier */
	else if (fmt[*ind] == ' ')
	{
		while (fmt[*ind] == ' ')
			(*ind)++;
		(*ind)--;
	}

	/* Otherwise, print the unknown format specifier */
	else
		unknown_len += write(1, &fmt[*ind], 1);

	return (unknown_len);
}
/**
 * handle_print - Prints an argument based on its type
 * @fmt: Formatted string in which to print the arguments.
 * @list: List of arguments to be printed.
 * @ind: Pointer to index of current character being processed in fmt.
 * @buffer: Buffer array to handle print.
 * @flags: Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 *
 * Return: Number of characters printed or -1 on failure.
 */

int handle_print(const char *fmt, int *ind, va_list list,
		char buffer[], int flags,
		int width, int precision, int size)
{
	int i, printed_chars = -1;
	fmt_t fmt_types[] =  {
		{'c', print_char},
		{'s', print_string},
		{'%', print_percent},
		{'i', print_int},
		{'d', print_int},
		{'b', print_binary},
		{'u', print_unsigned},
		{'o', print_octal},
		{'x', print_hexadecimal},
		{'X', print_hexa_upper},
		{'p', print_pointer},
		{'S', print_non_printable},
		{'r', print_reverse},
		{'R', print_rot13string},
		{'\0', NULL}
	};

	/* Loop through the format specifiers to find the matching one */
	for (i = 0; fmt_types[i].fmt != '\0'; i++)
	{
		if (fmt[*ind] == fmt_types[i].fmt)
			return (fmt_types[i].fn(list, buffer, flags, width, precision, size));
	}

	/*
	 * If the end of the format string is reached
	 * without finding a match, handle the unknown format specifier
	 */
	if (fmt_types[i].fmt == '\0')
	{
		if (fmt[*ind] == '\0')
			return (-1);
		return (handle_unknown(fmt, ind));
	}

	return (printed_chars);
}
