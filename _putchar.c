#include "main.h"

/**
 * _putchar - prints character to stdout
 * @c: The character to print
 *
 * Return: Always (1) Success
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

