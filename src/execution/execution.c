/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:42:55 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	size_cmd(t_data *data)
{
	data->size_cmd = 0;
	data->trav_cmd = data->v_cmd;
	while (data->trav_cmd)
	{
		data->size_cmd++;
		data->trav_cmd = data->trav_cmd->next;
	}
}

static void	close_fds_one_cmd(t_data *data)
{
	if (data->v_cmd->f_in > 0)
		close(data->v_cmd->f_in);
	if (data->v_cmd->f_out > 1)
		close(data->v_cmd->f_out);
}

void	execution(t_data *data)
{
	t_cmd	*cmd;

	size_cmd(data);
	if (data->size_cmd == 1)
	{
		if (!check_redirection(data, data->v_cmd))
		{
			if (data->v_cmd->cmd[0])
				run_one_cmd(data);
		}
		if (data->chk_redct_exist == 1)
			close_fds_one_cmd(data);
	}
	else
	{
		pipeline(data);
		cmd = data->v_cmd;
		while (cmd)
		{
			if (cmd->hrdoc_fd > 0)
				close(cmd->hrdoc_fd);
			cmd = cmd->next;
		}
	}
}
