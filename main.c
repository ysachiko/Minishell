#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

int sh_cd(char **args);
int sh_exit(char **args);
int sh_pwd(char **args);
int launch(char **args);

//PUT IT INTO STRUCT
char *builtins[] = {"cd", "exit", "pwd"};
int (*built[]) (char **) = {&sh_cd, &sh_exit, &sh_pwd};

//int sig

//BUILTINS
int num_builtins()
{
	return sizeof(builtins) / sizeof(char *);
}

int sh_pwd(char **args)
{
	(void) args;
	char dir[1024];

	getcwd(dir, 1024);
	printf("%s\n", dir);
	return 1;
}

int sh_cd(char **args)
{
	if (args[1] == NULL)
		printf("expected argument: cd <dir_path>");
	else
	{
		if (chdir(args[1]) != 0)	
		{
			perror("cd: ");
		}
	}
	return 1;
}

int sh_exit(char **args)
{
	(void)args;
	exit(EXIT_SUCCESS);
	return 0;
}

//EXEC
int execute(char **args)
{
	int i = 0;

	if (args[0] == NULL)
		return 1;

	while(i < num_builtins())
	{
		if (strcmp(args[0], builtins[i]) == 0)
			return (*built[i])(args);
		i++;
	}

	return launch(args);
}

//EXEC
int launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		//CHILD
		if (execvp(args[0], args) == -1)
			perror("exec failure");
		rl_on_new_line();
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		perror("error forking");
	else
	{
		//PARENT
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return 1;
}

int main(void)
{
	char *line;
	char **args;
	//int status;

	
	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(line);
		if (!line)
			exit(EXIT_FAILURE);
		args = ft_split(line, ' ');
		execute(args);
		rl_redisplay();
		free(line);
		free(args);
	}
}
