/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:17:58 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/29 17:13:26 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static void	export_err(char **vals, int *ret)
{
	if (!vals[0])
	{
		printf("export: '=': not a valid identifier\n");
		*ret = 1;
		return ;
	}
	printf("export: '%s': not a valid identifier\n", vals[0]);
	*ret = 1;
	return ;
}

static void	export_positive(char **vals, t_main *all)
{
	t_env	*tmp;

	tmp = search_env(all->env_list, vals[0]);
	if (tmp)
	{
		if (tmp->value)
			free(tmp->value);
		tmp->value = ft_strdup(vals[1]);
		free_split(vals);
		return ;
	}
	add_env(&(all->env_list), new_env(ft_strdup(vals[0]), \
					ft_strdup(vals[1])));
	free_split(vals);
}

static void	export_loop(t_main *all, char **args, int *ret, int i)
{
	char	**vals;

	while (args[++i])
	{
		vals = ft_split(args[i], '=');
		if (!check_export(vals[0]))
		{	
			export_err(vals, ret);
			free_split(vals);
			continue ;
		}
		if (vals[1])
		{
			export_positive(vals, all);
			continue ;
		}
		free_split(vals);
	}
}	

int	sh_export(char **args, t_main *all)
{
	t_env	*tmp;
	t_env	*tmp_2;
	int		i;
	int		ret;
	char	**vals;

	ret = 0;
	i = 0;
	if (args[1])
	{
		export_loop(all, args, &ret, i);
		return (ret);
	}
	tmp = copy_env(all->env_list);
	sort_env(tmp);
	tmp_2 = tmp;
	while (tmp_2)
	{
		printf("%s=", tmp_2->key);
		printf("%s\n", tmp_2->value);
		tmp_2 = tmp_2->next;
	}
	clean_env(tmp);
	return (0);
}
