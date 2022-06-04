#include "libft/libft.h"
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
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

//SIGNALS
void handler(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

void handler2(int sig)
{
	//exit_status += sig;
	if (sig == SIGINT)
	{
		//exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();
	}
}

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
			perror("cd");
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

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
	{
		//CHILD
		signal(SIGINT, SIG_DFL);
		signal(SIGINT, SIG_DFL);
		if (execvp(args[0], args) == -1)
			perror("exec failure");
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

	
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		signal(SIGINT, handler);
		line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(line);
		if (!line)
			exit(EXIT_FAILURE);
		args = ft_split(line, ' ');
		execute(args);
		/*printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();*/
		free(line);
		free(args);
	}
}
