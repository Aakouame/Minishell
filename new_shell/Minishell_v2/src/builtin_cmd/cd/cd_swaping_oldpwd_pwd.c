/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_swaping_oldpwd_pwd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:39:52 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/01 11:51:44 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	execute_cd_swap_init(t_data *data, t_env **pwd, t_env **old)
{
	*pwd = getenv_addr(data, "PWD");
	*old = getenv_addr(data, "OLDPWD");
}

static void	execute_cd_swap_helper(t_data *data, t_env *pwd, char *val)
{
	if (chdir(val) != 0)
	{
		data->chk_dolla = 1;
		dup2(data->s_stdout, STDOUT_FILENO);
		printf("minishell: cd: %s: No such file or directory\n", pwd->value);
		close(data->s_stdout);
		return ;
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
		dup2(data->s_stdout, STDOUT_FILENO);
		printf("minishell: cd: %s: No such file or directory\n", val);
		close(data->s_stdout);
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
	data->chk_dolla = 0;
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

void	execute_cd_two_mines(t_data *data)
{
	t_env	*pwd;
	t_env	*old;
	char	*val;

	execute_cd_swap_init(data, &pwd, &old);
	val = getenv("HOME");
	if (!val)
	{
		error_cd(data, "minishell: cd: HOME not set");
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
	data->chk_dolla = 0;
	execute_cd_swap_helper(data, pwd, val);
}

void	cd_between_pwd_and_oldpwd(t_data *data, char *cmd)
{
	if (!cmd[1])
	{
		if (check_old_pwd(data))
		{
			error_cd(data, "minishell: cd: OLDPWD not set");
			return ;
		}
		else
		{
			execute_cd_swap_old_pwd(data);
			pwd_cmd(data);
		}
	}
	else if (cmd[1] == '-' && !cmd[2])
	{
		if (check_old_pwd(data))
		{
			error_cd(data, "minishell: cd: OLDPWD not set");
			return ;
		}
		else
			execute_cd_two_mines(data);
	}
	else
	{
		//error_cd(data, "minishell: cd: -: invalid option");
		data->chk_dolla = 1;
		printf("minishell: cd: -%c: invalid option\n", cmd[1]);
		return ;
	}
}
