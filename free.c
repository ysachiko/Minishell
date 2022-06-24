/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:42:51 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/24 16:59:55 by ysachiko         ###   ########.fr       */
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
	while (split && split[i])
		free (split[i++]);
	free (split);
	split = NULL;
}

void	clean_env_node(t_env *envp)
{
	free(envp->key);
	free(envp->value);
	free(envp);
}

void	clean_env(t_env *envp)
{
	t_env	*curr;
	t_env	*tmp;

	curr = envp;
	while (curr)
	{
		tmp = curr->next;
		free(curr->key);
		free(curr->value);
		free(curr);
		curr = tmp;
	}
	free(curr);
	envp = NULL;
}

void	free_hash(t_hash *head)
{
	t_hash	*head_tmp;
	t_hash	*tmp;

	head_tmp = head;
	while (head_tmp)
	{
		if (head_tmp->value)
			free (head_tmp->value);
		tmp = head_tmp;
		head_tmp = head_tmp->next;
		free(tmp);
	}
}

/*void	clean_up(t_main all)
{

}*/
