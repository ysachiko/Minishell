#include "includes/parser.h"

char *builtins[] = {"cd", "exit", "pwd", "env", "export", "unset", "echo"};
int (*built[]) (char **, t_main *) = {&sh_cd, &sh_exit, &sh_pwd, &sh_env, &sh_export, &sh_unset, &sh_echo};

//EXECUTE
int execute(char **args, t_main *all)
{
	int i;

	i = 0;
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

int launch(char **args, t_main *all)
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

int num_builtins()
{
	return sizeof(builtins) / sizeof(char *);
}

int sh_export(char **args, t_main *all)
{
	t_env *tmp;
	t_env	*tmp_2;
	
	// CHECK FOR MULTIPLE VARS
	// CHECK VARS
	/*if (check_export(args[0]))
	{
		printf("export: '%s': not a valid identifier", args[0]);
		return (1);
	}*/
	if (args[1])
	{
		char **vals = ft_split(args[1], '=');
		tmp = search_env(all->env_list, vals[0]);
		if (tmp)
		{
			tmp->value = vals[1];
			return (0);
		}
		add_env(&(all->env_list), new_env(ft_strdup(vals[0]), ft_strdup(vals[1])));
		free_split(vals);
		return (0);
	}

	// PUT IT IN SEPARATE FUNC ↓
	tmp = copy_env(all->env_list);
	sort_env(tmp);
	while (tmp)
	{
		printf("%s=", tmp->key);		
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	//clean_env(&tmp);
	return (0);
}

int	sh_unset(char **args, t_main *all)
{
	t_env	*cpy;
	t_env	*prev;

	if (!args[1])
	{
		printf("unset: not enough arguments\n");	// ERROR
		return (1);
	}

	prev = NULL;
	cpy = all->env_list;
	while (cpy)
	{
		if (!ft_strcmp(cpy->key, args[1]))
		{
			if (!prev)
				all->env_list = cpy->next;
			else
				prev->next = cpy->next;
			clean_env_node(cpy);
			return (0);
		}
		prev = cpy;
		cpy = cpy->next;
	}
	return (0);
}

int	sh_env(char **args, t_main *all)
{
	(void)args;
	t_env	*tmp;

	tmp = all->env_list;
	while (tmp)
	{
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int sh_pwd(char **args, t_main *all)
{
	char	*pwd;

	if (*args == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50); // ERROR CODE AN STUFF
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

// DOPILIT'
int	oldpwd(t_main *all)
{
	char	*pwd;
	t_env	*tmp;

	tmp = search_env(all->env_list, "OLDPWD");
	pwd = getcwd(NULL, 0);
	free(tmp->value);
	tmp->value = ft_strdup(pwd);
	free(pwd);
	return 0;
}

int sh_cd(char **args, t_main *all)
{
	t_env	*tmp;

	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "-")) 
	{
		if (!args[1] || !ft_strcmp(args[1], "~"))
		{
			tmp = search_env(all->env_list, "HOME");
			if (tmp)
			{
				oldpwd(all);
				chdir(tmp->value);
				return 0;
			}
			printf("HOME not set\n");
			return 1;
		}
		if (!ft_strcmp(args[1], "-"))
		{
			tmp = search_env(all->env_list, "OLDPWD");
			if (tmp)
			{
				chdir(tmp->value);
				return 0;
			}
			printf("OLDPWD not set\n");
			return 1;
		}
	}
	oldpwd(all);
	if (chdir(args[1]) != 0)	
			perror("cd");
	return 0;
}

int sh_exit(char **args, t_main *all)
{
	(void)args;
	// CLEAR EXIT
	exit(EXIT_SUCCESS);
	return 0;
}
