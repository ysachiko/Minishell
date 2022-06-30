/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:13 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/30 15:16:51 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

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
	return (NULL);
}

int	check_export(char *name)
{
	int	i;

	if (!name)
		return (0);
	if (name && ft_isdigit(name[0]))
		return (0);
	i = 0;
	while (name && name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	check_input(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			ft_putstr_fd("minishell: syntax error near \
unexpected token `|'\n", STDERR_FILENO);
			g_exit_status = 2;
			return (0);
		}
		if (*input == ' ' || *input == '\t')
			input++;
		else
			return (1);
	}
	return (0);
}

void	display_ctrl_c(int display)
{
	struct termios	t;

	tcgetattr(0, &t);
	if (display == 0)
		t.c_lflag |= ECHOCTL;
	else
		t.c_lflag &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &t);
}

void	clean_up(t_main *main, t_bt *bts)
{
	clean_env(main->env_list);
	free(main);
	free(bts);
}
