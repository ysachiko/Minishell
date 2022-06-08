#include "includes/parser.h"

t_env	*env_last(t_env *head);
void	add_env(t_env **env, t_env *new);
t_env	*new_env(char *key, char *value);
t_env	*copy_env(t_env *head);
void	sort_env(t_env *copy);
t_env		*search_env(t_env *head, char *key);

int sh_unset(char **args, t_main *all);
int sh_export(char **args, t_main *all);
int sh_cd(char **args, t_main *all);
int sh_exit(char **args, t_main *all);
int sh_pwd(char **args, t_main *all);
int sh_env(char **args, t_main *all);
int launch(char **args, t_main *all);

//PUT IT INTO STRUCT
char *builtins[] = {"cd", "exit", "pwd", "env", "export", "unset"};
int (*built[]) (char **, t_main *) = {&sh_cd, &sh_exit, &sh_pwd, &sh_env, &sh_export, &sh_unset};

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

int sh_export(char **args, t_main *all)
{
	t_env *tmp;
	t_env	*tmp_2;
	char **vals = ft_split(args[1], '=');
	
	if (args[1])
	{
		tmp = search_env(all->env_list, vals[0]);
		if (tmp)
		{
			tmp->value = vals[1];
			return (0);
		}	
		add_env(&(all->env_list), new_env(vals[0], vals[1]));
		//free_split(vals);
		return (0);
	}
	
	// PUT IT IN SEPARATE FUNC ↓
	tmp = all->env_list; 
	tmp = copy_env(all->env_list); 
	sort_env(tmp);
	while (tmp->next != NULL)
	{
		tmp_2 = tmp->next;
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp_2;
	}
	printf("%s=", tmp->key);
	printf("%s\n", tmp->value);
	//clean_env(&tmp);
	return (0);
}

int	sh_unset(char **args, t_main *all)
{
	t_env *tmp;
	t_env *curr = all->env_list;

	if (args[1] == NULL)
		printf("unset: not enough arguments\n");
	if (curr->key == args[1])
	{
		tmp = curr;
		curr = curr->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	else
	{
		t_env *curr = all->env_list;
		while (curr->next != NULL)
		{
			if (curr->key == args[1])
			{
				tmp = curr->next;
				curr->next = curr->next->next;
				free(tmp->key);
				free(tmp->value);
				free(tmp);
				return 0;
			}
			else
				curr = curr->next;
		}
	}
	return 0;
}

int	sh_env(char **args, t_main *all)
{
	(void)args;
	t_env	*tmp;
	t_env	*tmp_2;

	tmp = all->env_list;
	while (tmp->next != NULL)
	{
		tmp_2 = tmp->next;
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp_2;
	}
	printf("%s=", tmp->key);
	printf("%s\n", tmp->value);
	return (0);
}

int sh_pwd(char **args, t_main *all)
{
	(void) args;
	char dir[1024];

	getcwd(dir, 1024);
	printf("%s\n", dir);
	return 1;
}

int sh_cd(char **args, t_main *all)
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

int sh_exit(char **args, t_main *all)
{
	(void)args;
	exit(EXIT_SUCCESS);
	return 0;
}

//EXEC
int execute(char **args, t_main *all)
{
	int i = 0;

	if (args[0] == NULL)
		return 1;

	while(i < num_builtins())
	{
		if (ft_strcmp(args[0], builtins[i]) == 0)
			return (*built[i])(args,all);
		i++;
	}
		
	return launch(args, all);
}

//EXEC
int launch(char **args, t_main *all)
{
	pid_t pid, wpid;
	int status;

	signal(SIGINT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	pid = fork();
	rl_on_new_line();
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

// UTILS 
t_env	*search_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0) // FIX THIS
			return (tmp);
		tmp = tmp->next;
	}
	return NULL;
}

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->key = key;
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env != NULL && env != NULL)
	{
		tmp = *env;
		tmp = env_last(*env);
		tmp->next = new;
		return;
	}
	*env = new;
}

t_env	*env_last(t_env *head)
{
	t_env	*tmp;

	if (head == NULL)
		return (NULL);

	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_env	*copy_env(t_env *head)
{
	if (head == NULL)
		return NULL;
	t_env *node = malloc(sizeof(t_env));

	node->key = head->key;
	node->value = head->value;

	node->next = copy_env(head->next);

	return node;
}

void	sort_env(t_env *copy)
{
	t_env *curr = copy;
	t_env *tmp;
	char *tmp_key;
	char *tmp_value;


	if (curr == NULL)
		return;
	while (curr->next != NULL)
	{
		tmp = curr->next;
		while (tmp->next != NULL)
		{	
			if (ft_strcmp(curr->key, tmp->key) > 0)
			{
				tmp_key = curr->key;
				tmp_value = curr->value;
				curr->key = tmp->key;
				curr->value = tmp->value;
				tmp->key = tmp_key;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}

int main(int ac, char **av, char **env)
{
	char *line;
	char **args;
	t_main	*main;
	
	main = malloc(sizeof(t_main));
	init_env(main, env);
	signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		signal(SIGINT, handler);
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(main->line);
		if (!main->line)
			exit(EXIT_FAILURE);
		args = ft_split(main->line, ' ');
		execute(args, main);
		/*printf("\n");
		rl_on_new_line();
		rl_replace_line("",0);
		rl_redisplay();*/
		free(main->line);
		free_split(args);
	}
	clean_env(&(main->env_list));
	//clean_up();
}
