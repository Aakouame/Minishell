/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_everywhere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:53:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/31 22:09:28 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	cd_to_home(t_data *data, char **cmd)
{
	t_env	*home;

	home = getenv_addr(data, "HOME");
	if (!home)
	{
		error_cd(data, "minishell: cd: HOME not set");
		return (1);
	}
	*cmd = add_dup(data, home->value, 1);
	return (0);
}

static int	join_home_and_path(t_data *data, char **cmd)
{
	t_env	*e_home;
	char	*home;

	e_home = getenv_addr(data, "HOME");
	if (!e_home)
	{
		home = getenv("HOME");
		if (!home)
		{
			error_cd(data, "minishell: cd: HOME not set");
			return (1);
		}
		*cmd = add_join(data, home, &cmd[0][1], 1);
		return (0);
	}
	*cmd = add_join(data, e_home->value, &cmd[0][1], 1);
	return (0);
}

static void	execute_cmd_cd(t_data *data, char *cmd)
{
	char	*path;

	if (chdir(cmd) != 0)
	{
		data->chk_dolla = 1;
		dup2(data->s_stdout, STDOUT_FILENO);
		printf("minishell: cd: %s: No such file or directory\n", cmd);
		close(data->s_stdout);
		return ;
	}
	path = allocation(data, 1024, sizeof(char), 1);
	getcwd(path, 1024);
	if (access(path, F_OK) != 0)
	{
		dup2(data->s_stdout, STDOUT_FILENO);
		printf("cd: error retrieving current directory\n");
		close(data->s_stdout);
	}
	if (data->old_pwd_make == 0)
		old_pwd_alloc(data);
	change_pwd(data, path);
	change_oldpwd(data);
	data->chk_dolla = 0;
}

void	cd_everywhere_at_once(t_data *data, char *cmd)
{
	int	i;

	i = 0;
	if (!cmd)
	{
		if (cd_to_home(data, &cmd))
			return ;
	}
	else if (cmd[0] == '~')
	{
		if (join_home_and_path(data, &cmd))
			return ;
	}
	execute_cmd_cd(data, cmd);
}
