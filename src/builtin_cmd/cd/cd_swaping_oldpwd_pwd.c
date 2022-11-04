/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_swaping_oldpwd_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:39:52 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 10:44:02 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	execute_cd_swap_helper(t_data *data, t_env *pwd, char *val)
{
	data->chk_dolla = 0;
	if (chdir(val) != 0)
	{
		data->chk_dolla = 1;
		stdanred_error("cd: ", 0, 1);
		stdanred_error(": No such file or directory\n", pwd->value, 0);
	}
}

static void	execute_cd_swap_old_pwd(t_data *data)
{
	t_env	*pwd;
	t_env	*old;
	char	*val;

	execute_cd_swap_init(data, &pwd, &old);
	val = old->value;
	if (access(val, F_OK) != 0)
	{
		data->chk_dolla = 1;
		stdanred_error("cd: ", 0, 1);
		stdanred_error(": No such file or directory\n", val, 0);
		return ;
	}
	if (pwd)
	{
		old->value = pwd->value;
		pwd->value = val;
		data->pwd_of_mysys = add_dup(data, val, 0);
	}
	else
	{
		old->value = data->pwd_of_mysys;
		data->pwd_of_mysys = val;
	}
	execute_cd_swap_helper(data, pwd, val);
}

static int	check_old_pwd(t_data *data)
{
	t_env	*old;

	old = data->l_env;
	old = getenv_addr(data, "OLDPWD");
	if (old)
		return (0);
	return (1);
}

static void	execute_cd_two_mines(t_data *data)
{
	t_env	*pwd;
	t_env	*old;
	char	*val;

	execute_cd_swap_init(data, &pwd, &old);
	val = getenv("HOME");
	if (!val)
	{
		error_cd(data, "minishell: cd: HOME not set\n");
		return ;
	}
	if (pwd)
	{
		old->value = pwd->value;
		pwd->value = add_dup(data, val, 0);
		data->pwd_of_mysys = add_dup(data, val, 0);
	}
	else
	{
		old->value = data->pwd_of_mysys;
		data->pwd_of_mysys = add_dup(data, val, 0);
	}
	execute_cd_swap_helper(data, pwd, val);
}

void	cd_between_pwd_and_oldpwd(t_data *data, char *cmd)
{
	if (!cmd[1])
	{
		if (check_old_pwd(data))
			error_cd(data, "minishell: cd: OLDPWD not set\n");
		else
		{
			execute_cd_swap_old_pwd(data);
			pwd_cmd(data);
		}
	}
	else if (cmd[1] == '-' && !cmd[2])
	{
		if (check_old_pwd(data))
			error_cd(data, "minishell: cd: OLDPWD not set\n");
		else
			execute_cd_two_mines(data);
	}
	else
	{
		data->chk_dolla = 1;
		stdanred_error(&cmd[1], "cd: -", 1);
		stdanred_error(": invalid option\n", 0, 0);
	}
}
