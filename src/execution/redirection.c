/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 04:55:08 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 15:58:35 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	red_o_trnc(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
	if (access(red->file, F_OK) == 0)
	{
		if (access(red->file, W_OK) == 0)
		{
			*fd = open(red->file, O_WRONLY | O_TRUNC);
			if (*fd < 0)
				stdanred_error(": file failed to open\n", 0, 1);
		}
		else
		{
			data->exit_status = 126;
			stdanred_error(": Permission denied\n", red->file, 1);
			return (1);
		}
	}
	else
	{
		*fd = open(red->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (*fd < 0)
			stdanred_error(": file failed to open\n", 0, 1);
	}
	cmd->f_out = *fd;
	return (0);
}

static int	red_o_apend(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
	if (access(red->file, F_OK) == 0)
	{
		if (access(red->file, W_OK) == 0)
		{
			*fd = open(red->file, O_WRONLY | O_APPEND);
			if (*fd < 0)
				stdanred_error(": file failed to open\n", 0, 1);
		}
		else
		{
			data->exit_status = 126;
			stdanred_error(": Permission denied\n", red->file, 1);
			return (1);
		}
	}
	else
	{
		*fd = open(red->file, O_RDWR | O_APPEND | O_CREAT, 0644);
		if (*fd < 0)
			stdanred_error(": file failed to open\n", 0, 1);
	}
	cmd->f_out = *fd;
	return (0);
}

static int	red_i_trnc(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
	if (access(red->file, F_OK) == 0)
	{
		if (access(red->file, R_OK) == 0)
		{
			*fd = open(red->file, O_RDONLY);
			if (*fd < 0)
				stdanred_error(": file failed to open\n", 0, 1);
		}
		else
		{
			data->exit_status = 126;
			stdanred_error(": Permission denied\n", red->file, 1);
			return (1);
		}
	}
	else
	{
		data->exit_status = 1;
		stdanred_error(": No such file or directory\n", red->file, 1);
		return (1);
	}
	cmd->f_in = *fd;
	return (0);
}

static int	redirection_changer(t_data *data, t_red *red, t_cmd *cmd, int *fd)
{
	if (red->typ == O_TRNC)
	{
		if (red_o_trnc(data, red, cmd, fd))
			return (1);
	}
	else if (red->typ == O_APEND)
	{
		if (red_o_apend(data, red, cmd, fd))
			return (1);
	}
	else if (red->typ == I_TRNC)
	{
		if (red_i_trnc(data, red, cmd, fd))
			return (1);
	}
	return (0);
}

int	check_redirection(t_data *data, t_cmd *cmd)
{
	t_red	*trav;
	int		i;
	int		fd;

	i = 0;
	trav = cmd->redirect;
	if (trav)
	{
		data->chk_redct_exist = 1;
		while (trav)
		{
			if (i > 0)
				fds_closer(cmd, trav);
			if (redirection_changer(data, trav, cmd, &fd))
				return (1);
			else if (trav->typ == I_APEND)
				cmd->f_in = cmd->hrdoc_fd;
			trav = trav->next;
			i++;
		}
	}
	return (0);
}
