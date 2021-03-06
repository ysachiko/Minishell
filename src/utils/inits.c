/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysachiko <ysachiko@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:28:48 by kezekiel          #+#    #+#             */
/*   Updated: 2022/07/01 15:34:16 by ysachiko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

void	init_bts(t_bt *bts)
{
	bts->builtins[0] = "cd";
	bts->builtins[1] = "export";
	bts->builtins[2] = "unset";
	bts->builtins[3] = "env";
	bts->builtins[4] = "pwd";
	bts->builtins[5] = "exit";
	bts->builtins[6] = "echo";
	bts->built[0] = &sh_cd;
	bts->built[1] = &sh_export;
	bts->built[2] = &sh_unset;
	bts->built[3] = &sh_env;
	bts->built[4] = &sh_pwd;
	bts->built[5] = &sh_exit;
	bts->built[6] = &sh_echo;
}

void	null_smth(t_main *main, t_hash **tmp, t_hash **head)
{
	*tmp = main->tmp2;
	*head = NULL;
}
