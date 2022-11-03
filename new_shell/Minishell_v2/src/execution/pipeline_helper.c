/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:22:17 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 22:58:27 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pipeline_helper(t_data *data)
{
	//error_fork(data);
	error_close_pipes(data);
}

void	error_close_pipes(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->v_cmd;
	while (cmd)
{
		if (cmd->tab_pipe)
		{
			close(cmd->tab_pipe[0]);
			close(cmd->tab_pipe[1]);
		}
		else
			break ;
		cmd = cmd->next;
	}
}

void	pipeline_parent(t_data *data)
{
	int		status;

	while (1)
	{
		signal(SIGINT, SIG_IGN);
		if (waitpid(-1, &status, 0) == -1)
			break ;
		exit_status(&data->chk_dolla, status);
	}
}
