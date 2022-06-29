/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:15:41 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/28 18:16:04 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
				free(pwd);
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
				free(pwd);
				free(tmp2->value);
				tmp2->value = getcwd(NULL, 0);
				return (0);
			}
			printf("OLDPWD not set\n");
			return (1);
		}
	}
	oldpwd(all, pwd);
	free(pwd);
	if (chdir(args[1]) != 0)
	{
		perror("cd");
		return (1);
	}
	tmp2->value = getcwd(NULL, 0);
	return (0);
}
