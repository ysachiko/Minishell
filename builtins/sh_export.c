/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:17:58 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/28 18:17:59 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

int	sh_export(char **args, t_main *all)
{
	t_env	*tmp;
	t_env	*tmp_2;
	int		i;
	int		ret;
	char	**vals;

	ret = 0;
	if (args[1])
	{	
		i = 0;
		while (args[++i])
		{
			vals = ft_split(args[i], '=');
			if (!check_export(vals[0]))
			{	
				if (!vals[0])
				{
					printf("export: '=': not a valid identifier\n");
					ret = 1;
					continue ;
				}
				printf("export: '%s': not a valid identifier\n", vals[0]);
				ret = 1;
				continue ;
			}
			if (!vals[1])
			{
				free_split(vals);
				continue ;
			}
			tmp = search_env(all->env_list, vals[0]);
			if (tmp)
			{
				tmp->value = ft_strdup(vals[1]);
				free_split(vals);
				continue ;
			}
			add_env(&(all->env_list), new_env(ft_strdup(vals[0]), \
				ft_strdup(vals[1])));
			free_split(vals);
		}
		return (ret);
	}
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
