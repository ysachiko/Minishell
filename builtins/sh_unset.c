/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:56:31 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/29 20:45:38 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

static int	print_me(char **args)
{
	printf("unset: '%s': not a valid identifier\n", args[1]);
	return (1);
}

int	sh_unset(char **args, t_main *all)
{
	t_env	*cpy;
	t_env	*prev;

	if (!args[1])
		return (0);
	if (!check_export(args[1]))
		return (print_me(args));
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
