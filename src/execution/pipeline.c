/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 22:56:17 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_tab_pipe(t_cmd *trav, int *fd)
{
	trav->tab_pipe[0] = fd[1];
	trav->tab_pipe[1] = fd[0];
}

int	plug_pipes_in_node(t_data *data)
{
	t_cmd	*trav;
	int		fd[2];

	trav = data->v_cmd;
	while (trav->next)
	{
		if (pipe(fd) < 0)
		{
			error_fork(data);
			return (1);
		}
		trav->tab_pipe = allocation(data, 2, sizeof(int), 1);
		init_tab_pipe(trav, fd);
		trav->f_out = fd[1];
		trav = trav->next;
		trav->f_in = fd[0];
	}
	trav->tab_pipe = allocation(data, 2, sizeof(int), 1);
	init_tab_pipe(trav, fd);
	trav = data->v_cmd;
	return (0);
}

static void	plug_redirection_in_node(t_data *data)
{
	t_cmd	*trav;

	trav = data->v_cmd;
	while (trav)
	{
		check_redirection(data, trav);
		trav = trav->next;
	}
}

void	child_process_of_pipeline(t_data *data, t_cmd *trav)
{
	signal(SIGINT, SIG_DFL);
	if (check_builtin(data, &trav->cmd[0]))
	{
		dup2(trav->f_out, STDOUT_FILENO);
		builtin_cmd(data, trav);
		close(trav->tab_pipe[0]);
		close(trav->tab_pipe[1]);
		exit(0);
	}
	else
	{
		dup2(trav->f_out, STDOUT_FILENO);
		dup2(trav->f_in, STDIN_FILENO);
		data->i = 3;
		while (data->i < ((data->size_cmd -1) * 2) + 3)
			close (data->i++);
		execute_sys_cmd(data, trav);
	}
}

void	pipeline(t_data *data)
{
	t_cmd	*trav;
	t_cmd	*p_trav;

	if (pipeline_helper(data))
		return ;
	plug_redirection_in_node(data);
	trav = data->v_cmd;
	p_trav = 0;
	pipeline_work(data, trav, p_trav);
	pipeline_parent(data);
}
