/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:56:31 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/28 17:57:14 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/parser.h"

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
