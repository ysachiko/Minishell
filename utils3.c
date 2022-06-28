/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kezekiel <kezekiel@student.21-schoo>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:24:13 by kezekiel          #+#    #+#             */
/*   Updated: 2022/06/28 18:30:42 by kezekiel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parser.h"

int	check_input(char *input)
{
	while (*input)
	{
		if (*input == '|')
		{
			ft_putstr_fd("minishell: syntax error near \
unexpected token `|'\n", STDERR_FILENO);
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
