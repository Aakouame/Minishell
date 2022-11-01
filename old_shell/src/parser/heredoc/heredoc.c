/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:40:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/24 20:07:52 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	heredoc_dolla_helper(t_data *data, char *str, char *ptr)
{
	int		i;
	char	*tmp;

	if (str[data->i + 1] == '?')
	{
		data->i += 2;
		tmp = ft_itoa(data->chk_dolla);
		i = 0;
		while (tmp[i])
			ptr[data->j++] = tmp[i++];
		free(tmp);
	}
	if (str[data->i + 1] == '0')
	{
		i = 2;
		while (data->args[0][i])
			ptr[data->j++] = data->args[0][i++];
		data->i += 2;
	}
}

static void	heredoc_dolla(t_data *data, char *ptr, char *str)
{
	heredoc_dolla_helper(data, str, ptr);
	if (str[data->i + 1] >= '1' && str[data->i + 1] <= '9')
		data->i += 2;
	if (str[data->i + 1] == '$')
	{
		while (str[data->i] == '$')
		{
			if (str[data->i + 1] == '$')
				data->i += 2;
			else
				break ;
		}
	}
	if ((str[data->i + 1] >= 'A' && str[data->i + 1] <= 'Z') || \
			(str[data->i + 1] >= 'a' && str[data->i + 1] <= 'z') || \
			str[data->i + 1] == '_')
		heredoc_dolla_allocate(data, ptr, str);
	if (str[data->i + 1] == '\"' || str[data->i + 1] == '\'')
		return ;
}

static char	*fill_data(t_data *data, char *str)
{
	char	*ptr;

	ptr = ft_calloc(len_hrdoc_data(data, str) + 1, sizeof(char));
	if (!ptr)
		error_alloc();
	data->i = 0;
	data->j = 0;
	while (str[data->i])
	{
		if (str[data->i] == '$')
			heredoc_dolla(data, ptr, str);
		ptr[data->j++] = str[data->i++];
	}
	return (ptr);
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
		if (data->chk_q_hrdoc == 0)
			heredoc = fill_data(data, heredoc);
		free(hold);
		hold = ft_strjoin(heredoc, "\n");
		free(heredoc);
		heredoc = data->buff;
		data->buff = ft_strjoin(data->buff, hold);
		free(heredoc);
		free(hold);
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
