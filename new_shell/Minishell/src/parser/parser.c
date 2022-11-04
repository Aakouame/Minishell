/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:49:56 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static t_token	*parsing_alloc_red(t_data *data, t_token *trav, \
		t_red *trav_red)
{
	trav_red->typ = trav->type;
	if (trav->type != I_APEND)
		trav_red->file = add_dup(data, trav->value, 1);
	else
	{
		trav_red->determiner = add_dup(data, trav->value, 1);
		if (data->chk_hrdc_cls != 0)
			close(data->hrdoc_fd[0]);
		heredoc_implement(data, trav_red->determiner);
		if (data->chk_hrdoc_exit == 1)
			return (trav);
		data->chk_hrdc_cls = 1;
	}
	trav = trav->next;
	return (trav);
}

static int	get_cmd_parsing_helper(t_data *data, t_token **trav, \
		t_red **trav_red, int *i)
{
	if (trav[0]->type == WRD)
	{
		data->trav_cmd->cmd[*i] = add_dup(data, trav[0]->value, 1);
		*trav = trav[0]->next;
		*(i) += 1;
	}
	else if (trav[0]->type == O_TRNC || trav[0]->type == O_APEND \
			|| trav[0]->type == I_TRNC || trav[0]->type == I_APEND)
	{
		*trav = parsing_alloc_red(data, *trav, *trav_red);
		if (data->chk_hrdoc_exit == 1)
		{
			close(data->hrdoc_fd[0]);
			return (1);
		}
		*trav_red = trav_red[0]->next;
	}
	return (0);
}

static void	get_cmd_parsing(t_data *data)
{
	t_token	*trav;
	t_red	*trav_red;
	int		red_len;
	int		cmd_len;
	int		i;

	trav = init_var_get_cmd_parsing(data, &i, &red_len, &cmd_len);
	parsing_get_len_alloc_cmd_arr(data, &cmd_len, &red_len);
	data->trav_cmd->cmd = allocation(data, cmd_len + 1, sizeof(char *), 1);
	allocate_red_node(data, red_len);
	trav_red = data->trav_cmd->redirect;
	while (trav)
	{
		if (trav->type != PIPE)
		{
			if (get_cmd_parsing_helper(data, &trav, &trav_red, &i))
				return ;
		}
		else if (trav->type == PIPE)
			break ;
	}
	data->trav_cmd->hrdoc_fd = data->hrdoc_fd[0];
	data->trav_cmd = data->trav_cmd->next;
}

void	parser(t_data *data)
{
	allocate_cmd_node(data);
	data->chk_hrdoc_exit = 0;
	data->trav_cmd = data->v_cmd;
	data->trav = data->t_join;
	while (data->trav)
	{
		get_cmd_parsing(data);
		if (data->chk_hrdoc_exit == 1)
		{
			data->error_lexer = 1;
			return ;
		}
		if (!data->trav)
			break ;
		else if (data->trav->type == PIPE)
			data->trav = data->trav->next;
	}
}
