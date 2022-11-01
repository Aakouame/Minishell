/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:02:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/01 10:25:46 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_tab_pipe(t_cmd *trav, int *fd)
{
	trav->tab_pipe[0] = fd[1];
	trav->tab_pipe[1] = fd[0];
}

static int	plug_pipes_in_node(t_data *data)
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

static void	child_process_of_pipeline(t_data *data, t_cmd *trav)
{
	signal(SIGINT, SIG_DFL);
	if (check_builtin(data, &trav->cmd[0]))
	{
		data->s_stdout = dup(1);
		dup2(trav->f_out, STDOUT_FILENO);
		builtin_cmd(data, trav);
		dup2(data->s_stdout, STDOUT_FILENO);
		close(data->s_stdout);
		//
		close(trav->tab_pipe[0]);
		close(trav->tab_pipe[1]);
		//exit depend of the error
		exit(0);
	}
	else
	{
		data->s_stdout = dup(1);
		dup2(trav->f_out, STDOUT_FILENO);
		dup2(trav->f_in, STDIN_FILENO);

		//close(data->s_stdout);
		close(trav->tab_pipe[0]);
		close(trav->tab_pipe[1]);
		execute_sys_cmd(data, trav);
	}
}

void	pipeline(t_data *data)
{
	int		pid;
	t_cmd	*trav;
	t_cmd	*p_trav;

	if (plug_pipes_in_node(data))
		pipeline_helper(data);
	plug_redirection_in_node(data);
	trav = data->v_cmd;
	p_trav = 0;
	while (trav)
	{
		pid = fork();
		if (pid < 0)
			error_fork(data);
		if (pid == 0)
			child_process_of_pipeline(data, trav);
		if (p_trav)
			close(p_trav->tab_pipe[1]);
		close(trav->tab_pipe[0]);

		//close(data->s_stdout);
		//close(trav->tab_pipe[1]);

		if (trav->f_in > 0)
			close(trav->f_in);
		if (trav->f_out > 1)
			close(trav->f_out);
		p_trav = trav;
		trav = trav->next;
	}
	pipeline_parent(data);
}
