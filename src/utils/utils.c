/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 14:46:37 by ysachiko          #+#    #+#             */
/*   Updated: 2022/07/01 15:29:24 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_env	*new_env(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (new)
	{
		new->key = key;
		new->value = value;
		new->next = NULL;
	}
	return (new);
}

void	add_env(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (*env != NULL && env != NULL)
	{
		tmp = *env;
		tmp = env_last(*env);
		tmp->next = new;
		return ;
	}
	*env = new;
}

t_env	*env_last(t_env *head)
{
	t_env	*tmp;

	if (head == NULL)
		return (NULL);
	tmp = head;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

void	push_node(t_env **head, char *key, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *head;
	*head = new;
}

t_env	*copy_env(t_env *head)
{
	t_env	*curr;
	t_env	*new;
	t_env	*tail;

	curr = head;
	new = NULL;
	tail = NULL;
	while (curr)
	{
		if (!new)
		{
			push_node(&new, curr->key, curr->value);
			tail = new;
		}
		else
		{
			push_node(&(tail->next), curr->key, curr->value);
			tail = tail->next;
		}
		curr = curr->next;
	}
	return (new);
}
