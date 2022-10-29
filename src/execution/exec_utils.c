/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 04:58:13 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/08 12:01:44 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	check_if_x_ok(t_data *data, t_cmd *cmd, char *path)
{
	if (access(path, X_OK) == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		execve(path, cmd->cmd, data->env_exec);
	}
	else
	{
		printf("minishell: %s: Permission denied\n", path);
		exit(126);
	}
}

int	find_slash(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '/')
			return (1);
		i++;
	}
	return (0);
}

void	exit_status(int *exit_stat, int status)
{
	if (status == 256)
		*exit_stat = 1;
	else if (status == 32256)
		*exit_stat = 126;
	else if (status == 32512 || status == 13)
		*exit_stat = 127;
	else
		*exit_stat = 0;
}

void	fds_closer(t_cmd *cmd, t_red *red)
{
	if (red->typ == O_TRNC || red->typ == O_APEND)
	{
		if (cmd->f_out > 1)
			close(cmd->f_out);
	}
	else if (red->typ == I_TRNC)
	{
		if (cmd->f_in > 0)
			close(cmd->f_in);
	}
}
