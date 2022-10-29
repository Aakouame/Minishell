/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:59:26 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/29 14:36:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_var_tokenizer(t_data *data)
{
	data->index = 0;
	data->check = 1;
	data->error_lexer = 0;
	data->chk_hrdoc = 0;
	data->n_line = data->beg_line;
	//ft_init_tokenizer(data, data->beg_line, 0, 0);
}

 void	parser_phase(t_data *data)
 {
 	if (lexer_pt2(data))
 	{
 		data->chk_dolla = 258;
 		data->error_lexer = 1;
 		return ;
 	}
	join_t_token(data);
 	parser(data);
	//t_cmd	*cmd;
	//t_red	*red;
	//int	i;
	//
	//cmd = data->v_cmd;
	//while (cmd)
	//{
	//	i = 0;
	//	printf("cmd :\n");
	//	while (cmd->cmd[i])
	//		printf("	%s\n", cmd->cmd[i++]);
	//	red = cmd->redirect;
	//	while (red)
	//	{
	//		printf("%d\n", red->typ);
	//		if (red->typ == I_APEND)
	//			printf("	%s\n", red->determiner);
	//		else
	//			printf("	%s\n", red->file);
	//		red = red->next;
	//	}
	//	printf("%d\n", cmd->f_in);
	//	printf("%d\n", cmd->f_out);
	//	//printf("%d	%d\n", cmd->tab_pipe[0], cmd->tab_pipe[1]);
	//	printf("%d\n", cmd->hrdoc_fd);
	//	cmd = cmd->next;
	//}
 	return ;
 }
