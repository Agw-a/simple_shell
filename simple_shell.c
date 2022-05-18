#include "simple_shell.h"

/**
 * sighandle_r- checks for signals in terminal
 * interrupt character.
 * @signum:signal whose behavior to control(int)
 * Return:no return
 */
void sighandle_r(int signum)
{
	if (signum == SIGINT)
	{
		_puts("\n#cisfun%$ ");
	}
}

/**
 * _EOF_-handles the End of file
 * @len:return value of getline function
 * @buf:line buffer (character array)
 * Return:no return
 */

void _EOF_(int len, char *buf)
{
	(void)buf;

	if (len == -1)
	{
	if (isatty(STDIN_FILENO))
	{
	_puts("\n");
	free(buf);
	}
	exit(0);
	}
}

/**
 * _isatty-verifies whether
 * a file descriptor is
 * associated with character device(terminal)
 * Return:no return
 */
void _isatty(void)
{
	if (isatty(STDIN_FILENO))
	_puts("#cisfun$ ");
}

/**
 * main- simple shell
 * Return: 0 on function sucesss
 */
int main(void)
{
	ssize_t len = 0;
	char *buf = NULL, *value, *pathname, **arv;
	size_t size = 0;
	list_path *head = '\0';
	void (*f)(char **);

	signal(SIGINT, sighandle_r);
	while (len != EOF)
	{
		_isatty();
		len = getline(&buf, &size, stdin);
		_EOF_(len, buf);
		arv = splitsting(buf, "\n");

		if (!arv || !arv[0])
		execute(arv);

		else
		{
		value = _getenv("PATH");
		head = linkpath(value);
		pathname = _which(arv[0], head);
		f = checkbuild(arv);

		if (f)
		{
			free(buf);
			f(arv);
		}
		else if (!pathname)
		{
			free(arv[0]);
			arv[0] = pathname;
			execute(arv);
		}
		}
	}
	free_list(head);
	freearv(arv);
	free(buf);
	return (0);
}
