/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 04:54:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:06:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exec_file(t_data *data, t_cmd *cmd)
{
	char	*exec;

	if (find_slash(*cmd->cmd))
	{
		exec = *cmd->cmd;
		if (access(exec, F_OK) == 0)
		{
			if (access(exec, X_OK) == 0)
				execve(exec, cmd->cmd, data->env_exec);
			else
			{
				stdanred_error(": Permission denied\n", exec, 1);
				exit(126);
			}
		}
		stdanred_error(": command not found\n", cmd->cmd[0], 1);
		exit(127);
	}
}

static void	exec_cmd_path(t_data *data, t_cmd *cmd, char **sp)
{
	int		i;
	char	*path;
	char	*slash;

	i = 0;
	while (sp[i])
	{
		slash = ft_strjoin(sp[i], "/");
		path = ft_strjoin(slash, cmd->cmd[0]);
		if (access(path, F_OK) == 0)
			check_if_x_ok(data, cmd, path);
		free(path);
		free(slash);
		free(sp[i]);
		i++;
	}
	free(sp);
	stdanred_error(": command not found\n", cmd->cmd[0], 1);
	exit(127);
}

void	execute_sys_cmd(t_data *data, t_cmd *cmd)
{
	int		i;
	char	**sp;
	t_env	*env;

	i = 0;
	exec_file(data, cmd);
	env = getenv_addr(data, "PATH");
	if (!env)
	{
		data->chk_dolla = 1;
		stdanred_error(": No such file or directory\n", cmd->cmd[0], 1);
		exit(127);
	}
	sp = ft_split(env->value, ':');
	exec_cmd_path(data, cmd, sp);
}

static void	child_process_run_one_cmd(t_data *data)
{
	if (check_builtin(data, &data->v_cmd->cmd[0]))
		exit(0);
	if (data->chk_redct_exist == 1)
	{
		dup2(data->v_cmd->f_in, STDIN_FILENO);
		dup2(data->v_cmd->f_out, STDOUT_FILENO);
	}
	execute_sys_cmd(data, data->v_cmd);
}

void	run_one_cmd(t_data *data)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
		error_fork(data);
	if (pid == 0)
	{
		if (data->v_cmd->cmd[0])
			child_process_run_one_cmd(data);
	}
	if (pid >= 1)
	{
		signal(SIGINT, SIG_IGN);
		waitpid(pid, &status, 0);
		exit_status(&data->chk_dolla, status);
		if (data->v_cmd->cmd[0])
		{
			if (check_builtin(data, &data->v_cmd->cmd[0]))
			{
				dup2(data->v_cmd->f_out, STDOUT_FILENO);
				builtin_cmd(data, data->v_cmd);
			}
		}
	}
}
