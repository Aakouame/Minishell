/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:22:17 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 22:58:45 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
		exit_status(&data->exit_status, status);
	}
}

void	close_fds_of_pipeline(t_cmd *trav)
{
	if (trav->f_in > 0)
		close(trav->f_in);
	if (trav->f_out > 1)
		close(trav->f_out);
}

int	pipeline_helper(t_data *data)
{
	if (plug_pipes_in_node(data))
	{
		error_close_pipes(data);
		return (1);
	}
	return (0);
}

void	pipeline_work(t_data *data, t_cmd *trav, t_cmd *p_trav)
{
	int	pid;

	while (trav)
	{
		pid = fork();
		if (pid < 0)
		{
			error_fork(data);
			error_close_pipes(data);
			return ;
		}
		if (pid == 0)
			child_process_of_pipeline(data, trav);
		if (p_trav)
			close(p_trav->tab_pipe[1]);
		close(trav->tab_pipe[0]);
		close_fds_of_pipeline(trav);
		p_trav = trav;
		trav = trav->next;
	}
}
