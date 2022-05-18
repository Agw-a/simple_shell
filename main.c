#include "shell.h"

/**
 * main - creates a prompt that reads input, parses it, executes it and waits
 * for another command unless told to exit
 * @ac: number of args
 * @av: argument vector
 * @env: environment variable
 * Return: EXIT_SUCCESS
 */
int main(int ac __attribute__((unused)), char **av, char **env)
{
	char *line;
	char **args, **path;
	int count = 0, status = 0;
	(void) av;
	signal(SIGINT, handle_signal);
	while (1)
	{
		prompt();
		/*read input and return string*/
		line = read_input();
		/*separates string to get command and atgs*/
		args = toparse_str(line, env);

		if ((_strcmp(args[0], "\n") != 0) && (_strcmp(args[0], "env") != 0))
		{
			count += 1;
			path = search_path(env); /*search environment var*/
			status = _stat(args, path);
			child_process(av, args, env, status, count);
		}
		else
		{
			free(args);
		}
		free(line);
	}
	return (EXIT_SUCCESS);
}

/**
 * read_input - stores whatever is passed to it as standard input
 * Return: string containing the input
 */
char *read_input(void)
{
	char *line = NULL;
	ssize_t signal;
	size_t bufsize = 0;
	int i;

	signal = getline(&line, &bufsize, stdin);
	if (!line)
	{
		perror("Error allocating memory for buffer");
		return (0);
	}
	if (signal == 1)
	{
		free(line);
		return (NULL);
	}
	else if (signal == EOF)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "\n", 1);
		free(line);
		exit(0);
	}
	else
	{
		for (i = 0; line[i] == ' ' && line[i + 1] == ' '; i++)
			;
		if (!line[i] && line[i + 1] == '\n')
		{
			free(line);
			return (0);
		}
	}
	return (line);
}

/**
 * toparse_str - divides a string into and array of strings
 * @line: the string to be separated
 * @env: environment variable
 * Return: tokens(array of strings) on succes or EXIT_FAILURE if fails
 */
char **toparse_str(char *line, char **env)
{
	int bufsize = N_BUFSIZE, i = 0;
	char **tokens;
	char *token;

	if (line == NULL)
	{
		return (0);
	}
	tokens = _calloc(sizeof(char *), bufsize);
	if (!tokens)
	{
		perror("error");
		exit(EXIT_FAILURE);
	}
	token = strtok(line, TOK_DELIM);
	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, TOK_DELIM);
	}
	if (tokens[0] == NULL)
		tokens[i] = "\n"; /*if null put in new line*/

	/*COMPARE TOKENS*/
	if ((_strcmp(tokens[0], "exit") == 0) && tokens[1] == NULL)
	{
		free(line); /* free memory */
		free(tokens);
		exit(0);
	}
	if ((_strcmp(tokens[0], "env") == 0) && tokens[1] == NULL)
		func_printenv(env);      
	return (tokens);
}


/**
 * prompt - prints '$' and waits for a user's input
 */
void prompt(void)
{
	char *prompt = {"$ "};
	char *buffer = getcwd(NULL, 0);

	if (isatty(STDIN_FILENO))
	{
		write(STDOUT_FILENO, prompt, _strlen(prompt));
	}
	free(buffer);
}

/**
 * handle_signal - prints new line and prompt when CTRL + C is passed as input
 * @signal: name of sig
 */
void handle_signal(int signal)
{
	char *prompt = {"\n$ "};
	(void) signal;

	write(STDOUT_FILENO, prompt, _strlen(prompt));
	fflush(stdout);
}
