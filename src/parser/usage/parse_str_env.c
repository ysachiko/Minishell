/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 18:52:59 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/05 20:33:59 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/parser.h"

void	str_env_pars(t_main *main, char **str)
{
	int	i;

	i = 0;
	main->tmp = malloc(sizeof(t_hash));
	main->tmp->value = *str;
	while (main->tmp->value[i])
	{
		if (main->tmp->value[i] == '$')
		{
			i = str_refactor(main, main->tmp, i);
			i--;
		}
		i++;
	}
	*str = main->tmp->value;
	free(main->tmp);
}
