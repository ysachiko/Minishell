/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:52:59 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/08 17:30:06 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	str_env_pars(t_main *main, char **str)
{
	int	i;

	i = 0;
	main->tmp = malloc(sizeof(t_hash));
	main->tmp->value = ft_strdup(*str);
	free(*str);
	while (main->tmp->value[i])
	{
		if (main->tmp->value[i] == '$')
		{
			i = str_refactor(main, main->tmp, i);
			i--;
		}
		i++;
	}
	*str = ft_strdup(main->tmp->value);
	free(main->tmp->value);
	free(main->tmp);
}

void	realloc_argument(char **arg, char *tmp)
{
	char	*tmp_2;

	tmp_2 = ft_strjoin(*arg, tmp);
	free(*arg);
	*arg = ft_strdup(tmp_2);
	free(tmp_2);
}
