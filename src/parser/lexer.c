/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/06 13:25:20 by ysachiko          #+#    #+#             */
/*   Updated: 2022/06/01 17:16:17 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"
// #include "libft/libft.h"
#include "string.h"

// void	lexer(char *line) // берет линию сплитит по вайтспейсам потом по аргументам делает односвязный список
// {
// 	char		**str;
// 	int			i;
// 	t_list		*arg_list;

// 	i = 1;
// 	str = split_args(line);
// 	arg_list = ft_lstnew(str[0]);
// 	while (str[i])
// 	{
// 		ft_lstadd_back(&arg_list, ft_lstnew(str[i]));
// 		i++;
// 	}
// 	t_list	*temp;
// 	temp = arg_list;
// 	while (temp != NULL)
// 	{
// 		printf("%s\n", temp->content);
// 		temp = temp->next;
// 	}
// }

int main(int argc, char **argv, char **env)
{
	char	*line;
	char	**args;
	t_main	*main;
	//int status;


	//signal(SIGINT, handler);
	//signal(SIGQUIT, SIG_IGN);
	main = malloc(sizeof(t_main));
	while(1)
	{
		main->line = readline("\e[1;32mbash$ \e[0;37m");
		add_history(main->line);
		parser(main);
		if (!main->line)
			exit(EXIT_FAILURE);
		// rl_redisplay();
	}
	// free(line);
	// free(args);
}
