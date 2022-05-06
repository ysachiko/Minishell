/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/05/06 18:59:15 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft/libft.h"
#include "string.h"

void	lexer(char *line) // берет линию сплитит по вайтспейсам потом по аргументам делает односвязный список
{
	char		**str;
	int			i;
	t_list		*arg_list;

	i = 1;
	str = split_args(line);
	arg_list = ft_lstnew(str[0]);
	while (str[i])
	{
		ft_lstadd_back(&arg_list, ft_lstnew(str[i]));
		i++;
	}
	t_list	*temp;
	temp = arg_list;
	while (temp != NULL)
	{
		printf("%s\n", temp->content);
		temp = temp->next;
	}
}

int main(void)
{
	char *line;
	char **args;
	//int status;


	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	while(1)
	{
		line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(line);
		lexer(line);
		if (!line)
			exit(EXIT_FAILURE);
		// rl_redisplay();
	}
	// free(line);
	// free(args);
}
