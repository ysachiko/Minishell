#include "includes/parser.h"

int	check_export(char *s)
{
	int i;

	i = 0;
	if (ft_isdigit(s[i]))
		return (1);
	return (0);
}

t_env	*search_env(t_env *head, char *key)
{
	t_env	*tmp;

	tmp = head;
	while (tmp)
	{
		if (ft_strcmp(tmp->key, key) == 0)
			return (tmp);
		tmp = tmp->next;
	}
	return NULL;
}

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
		return;
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

t_env	*copy_env(t_env *head)
{
	if (head == NULL)
		return NULL;
	t_env *node = malloc(sizeof(t_env));

	node->key = head->key;
	node->value = head->value;

	node->next = copy_env(head->next);

	return node;
}

void	sort_env(t_env *copy)
{
	t_env *curr = copy;
	t_env *tmp;
	char *tmp_key;
	char *tmp_value;


	if (curr == NULL)
		return;
	while (curr->next != NULL)
	{
		tmp = curr->next;
		while (tmp->next != NULL)
		{	
			if (ft_strcmp(curr->key, tmp->key) > 0)
			{
				tmp_key = curr->key;
				tmp_value = curr->value;
				curr->key = tmp->key;
				curr->value = tmp->value;
				tmp->key = tmp_key;
				tmp->value = tmp_value;
			}
			tmp = tmp->next;
		}
		curr = curr->next;
	}
}

int		lst_size(t_hash *lst)
{
	int	i;

	i = 0;
	if (lst == NULL)
		return (i);
	while (lst)
	{
		if (lst->key == 1 || lst->key == 2)
			i++;
		lst = lst->next;
	}
	return (i);
}

char	**hash_parser(t_hash *head)
{
	char	**args;
	t_hash	*tmp;
	int		i;

	
	args = malloc(sizeof(char *) * lst_size(head) + 1);

	tmp = head;
	i = 0;
	while (tmp)
	{
		if (tmp->key == 1 || tmp->key == 2)
		{
			args[i] = tmp->value;
			i++;
		}
		tmp = tmp->next;
	}
	args[i] = NULL;
	return (args);
}
