#include "shell.h"

/**
 *_puts - prints a string
 *@str: A pointer to an int that will be updated
 *
 *Return: void
 */
void _puts(char *str)
{
	int n;

	for (n = 0 ; str[n] != '\0' ; n++)
	{
		_putchar(str[n]);
	}
	_putchar('\n');
}

/**
 * _strlen - returns a string
 * @s: integer to be used
 * Return: length of string
 */
int _strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return ((i + 1));
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 *str_concat - back a pointer to array
 *@s1: Array one
 *@s2: Array two
 *Return: Always an array dinamic
 */
char *str_concat(char *s1, char *s2)
{
	char *dst;
	unsigned int i, j, size;

	/*If the array is empty*/
	if (s1 == NULL)
		s1 = "";

	if (s2 == NULL)
		s2 = "";

	/*count size total*/
	size = (_strlen(s1) + _strlen(s2) + 1);

	/*malloc*/
	dst = (char *) malloc(size * sizeof(char));

	if (dst == 0)
	{
		return (NULL);
	}

	/*Concatenate arrays*/
	for (i = 0; *(s1 + i) != '\0'; i++)
		*(dst + i) = *(s1 + i);

	for (j = 0; *(s2 + j) != '\0'; j++)
	{
		*(dst + i) = *(s2 + j);
		i++;
	}
	dst[i] = '\0';

	return (dst);
}

/**
 * _strcmp - compares two strings
 * @s1: string 1
 * @s2: string 2
 * Return: returns an integer less  than,  equal  to,  or
 * greater  than zero if s1 is found, respectively, to be
 * less than, to match, or be greater than s2.
 */
int _strcmp(char *s1, char *s2)
{
	char *p1 = s1;
	char *p2 = s2;

	while (*p1 != '\0' && *p2 != '\0' && *p1 == *p2)
	{
		p1++;
		p2++;
	}
	return (*p1 - *p2);
}

/**
 * _strdup - copies a string to another
 * @str: the array
 * Return: pointer of sting copied
 */
char *_strdup(char *str)
{
	int i, j;
	char *s = NULL;

	if (str == NULL)
		return (0);
	for (i = 0; str[i]; i++)
		;
	i++;
	s = malloc(i * sizeof(char *));
	if (!s)
		return (NULL);
	for (j = 0; j < i; j++)
	{
		s[j] = str[j];
	}
	return (s);
}

/**
 * _itoa - integer to ascii
 * @num: num
 * @base: base
 * Return: char
 * Reference: https://gist.github.com/narnat/95733cd0ad7bfac0d90697292914c407
 **/
char *_itoa(int num, int base)
{
	static char *array = "0123456789abcdef";
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (num < 0)
	{
		n = -num;
		sign = '-';
	}
	ptr = &buffer[49];
	*ptr = '\0';

	do      {
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}
