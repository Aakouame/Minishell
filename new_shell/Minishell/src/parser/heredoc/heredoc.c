/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:40:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:11:57 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	heredoc_sig(int c)
{
	printf("\n");
	exit(1);
}

static void	heredoc_process_helper(t_data *data, char *hold, char *heredoc)
{
	hold = ft_strjoin(heredoc, "\n");
	free(heredoc);
	heredoc = data->buff;
	data->buff = ft_strjoin(data->buff, hold);
	free(heredoc);
	free(hold);
}

static void	heredoc_process(t_data *data, char *det)
{
	char	*heredoc;
	char	*hold;

	data->buff = ft_strdup("");
	signal(SIGINT, heredoc_sig);
	while (1)
	{
		rl_catch_signals = 1;
		heredoc = readline("> ");
		if (!heredoc)
			exit(0);
		if (!ft_strcmp(heredoc, det))
			break ;
		hold = heredoc;
		if (!data->chk_q_hrdoc)
		{
			expand_the_value(data, heredoc);
			heredoc = data->buff_expnd;
			free(hold);
		}
		heredoc_process_helper(data, hold, heredoc);
	}
	ft_putstr_fd(data->buff, data->hrdoc_fd[1]);
}

void	heredoc_implement(t_data *data, char *det)
{
	int		status;
	int		pid;

	if (pipe(data->hrdoc_fd) < 0)
		error_pipe(data, "minishell: pipe: error");
	pid = fork();
	if (pid < 0)
		error_fork(data);
	if (pid == 0)
	{
		close(data->hrdoc_fd[0]);
		heredoc_process(data, det);
		close(data->hrdoc_fd[1]);
		exit(0);
	}
	if (pid > 1)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		if (status == 256)
			data->chk_hrdoc_exit = 1;
		close(data->hrdoc_fd[1]);
	}
}
