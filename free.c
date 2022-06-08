#include "includes/parser.h"

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

/*void	clean_up(t_main all)
{
	
}*/
