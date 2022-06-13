/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:42:51 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/12 14:44:06 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

void	end_prog(char *err, int code, int mode)
{
	//clear_exit
	if (mode == 0 && err)
		ft_putstr_fd(err, STDERR_FILENO);
	else if (mode == 1)
		perror(err);
	exit(code);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	if (split)
	{
		while (split[i])
		{
			free(split[i]);
			i++;
		}
	}
	if (split)
		free(split);
}

void	clean_env_node(t_env *envp)
{
	free(envp->key);
	free(envp->value);
	free(envp);
}

void	clean_env(t_env **envp)
{
	t_env	*tmp;

	tmp = *envp;
	while (*envp)
	{
		tmp = *envp;
		*envp = (*envp)->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	free(envp);
}

void	free_hash(t_main *main)
{
	t_hash	*head;
	t_hash	*tmp;

	head = main->hash_head;
	while (head)
	{
		if (head->value)
			free (head->value);
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/*void	clean_up(t_main all)
{

}*/
