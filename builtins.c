/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:37:23 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/26 23:30:50 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

char	*builtins[] = {"cd", "exit", "pwd", "env", "export", "unset", "echo"};
int		(*built[])(char **, t_main *) = {&sh_cd, &sh_exit, &sh_pwd, &sh_env, &sh_export, &sh_unset, &sh_echo};

//EXECUTE

static int	ft_wexitstatus(int x)
{
	return ((x >> 8) & 0x000000ff);
}

int	execute(char **args, t_main *all, char **env)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (1);
	while (i < num_builtins())
	{
		if (ft_strcmp(args[0], builtins[i]) == 0)
			return  g_exit_status = (*built[i])(args,all);
		i++;
	}
	return (launch(args, all, env));
}

void	child_handler(int signum)
{
	if (signum == SIGINT)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (signum == SIGQUIT)
		ft_putstr_fd("Quit: 3\n", STDOUT_FILENO);
	exit(130);
}

int launch(char **args, t_main *all, char **env)
{
	pid_t	child;
	int	status;
	char	**path;
	char	*cmd;
	
	path = path_parser(all->env_list);
	cmd = search_paths(path, args[0]);
	child = fork();
	if (!child)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler);
		if (execve(cmd, args, env) == -1)
			perror("exec failure");
		exit(EXIT_FAILURE);
	}
	else if (child < 0)
		perror("error forking");
	else
		waitpid(child, &status, WUNTRACED);
	g_exit_status = ft_wexitstatus(status);
	free_split(path);
	return (g_exit_status);
}

int	num_builtins()
{
	return (sizeof(builtins) / sizeof(char *));
}

int	sh_export(char **args, t_main *all)
{
	t_env	*tmp;
	t_env	*tmp_2;
	int	i;
	int	ret;

	ret = 0;
	if (args[1])
	{	
		i = 0;
		while (args[++i])
		{
			
			char **vals = ft_split(args[i], '=');
			if (!check_export(vals[0]))
			{	
				if (!vals[0])
				{
					printf("export: '=': not a valid identifier\n");
					ret = 1;
					continue;	
				}
				printf("export: '%s': not a valid identifier\n", vals[0]);
				ret = 1;
				continue;
			}
			if (!vals[1])
			{
				free_split(vals);
				continue;
			}
			tmp = search_env(all->env_list, vals[0]);
			if (tmp)
			{
				tmp->value = ft_strdup(vals[1]);
				free_split(vals);
				continue;
			}
			add_env(&(all->env_list), new_env(ft_strdup(vals[0]), \
				ft_strdup(vals[1])));
			free_split(vals);
		}
		return (ret);
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
	clean_env(tmp);
	return (0);
}

int	sh_unset(char **args, t_main *all)
{
	t_env	*cpy;
	t_env	*prev;

	if (!args[1])
		return (0);
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
	t_env	*tmp;

	(void)args;
	tmp = all->env_list;
	while (tmp)
	{
		printf("%s=", tmp->key);
		printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	return (0);
}

int	sh_pwd(char **args, t_main *all)
{
	char	*pwd;

	if (*args == NULL)
		return (1);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50); // ERROR CODE AN STUFF
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}

// DOPILIT'
int	oldpwd(t_main *all, char *pwd)
{
	t_env	*tmp;

	tmp = search_env(all->env_list, "OLDPWD");
	if (tmp)
	{
		free(tmp->value);
		tmp->value = ft_strdup(pwd);
		return (0);
	}
	return (1);
}

int	sh_cd(char **args, t_main *all)
{
	t_env	*tmp;
	t_env	*tmp2;
	char	*pwd;


	tmp2 = search_env(all->env_list, "PWD");
	pwd = getcwd(NULL, 0);
	if (!args[1] || !ft_strcmp(args[1], "~") || !ft_strcmp(args[1], "-"))
	{
		if (!args[1] || !ft_strcmp(args[1], "~"))
		{
			tmp = search_env(all->env_list, "HOME");
			if (tmp)
			{
				oldpwd(all, pwd);
				chdir(getenv("HOME"));
				free(tmp2->value);
				tmp2->value = getcwd(NULL, 0);
				return (0);
			}
			printf("HOME not set\n");
			return (1);
		}
		else if (!ft_strcmp(args[1], "-"))
		{
			tmp = search_env(all->env_list, "OLDPWD");
			if (tmp)
			{
				chdir(tmp->value);
				oldpwd(all, pwd);
				free(tmp2->value);
				tmp2->value = getcwd(NULL, 0);
				return (0);
			}
			printf("OLDPWD not set\n");
			return (1);
		}
	}
	oldpwd(all, pwd);
	if (chdir(args[1]) != 0)
		perror("cd");
	tmp2->value = getcwd(NULL, 0);
	free(pwd);
	return (0);
}

int	ft_strisnum(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	sh_exit(char **args, t_main *main)
{
	// STATUS == int(args[1])
	// printf("\n %s %s %s \n", args[0], args[1], args[2]);
	if (args[1] && args[2])
	{
		g_exit_status = 1;
		printf("bash: exit: too many arguments\n");
	}
	else if (args[1] && ft_strisnum(args[1]) == 0)
	{
		g_exit_status = 255;
		ft_putstr_fd("bash: exit: ", STDERR);
		ft_putstr_fd(args[1], STDERR);
		ft_putendl_fd(": numeric argument required", STDERR);
	}
	else if (args[1])
	{
		main->exit_flag = 0;
		g_exit_status = ft_atoi(args[1]);
	}
	else
	{
		g_exit_status = 0;
		main->exit_flag = 0;
	}
	return (0);
}
