/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_stuff.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:16:57 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/29 13:29:58 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	sh_env(char **args, t_main *all)
{
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

int	sh_pwd(char **args, t_main *all)
{
	char	*pwd;

	if (*args == NULL)
		return (0);
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
		return (50);
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
