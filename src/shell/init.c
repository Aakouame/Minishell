/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:15:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 04:25:47 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	make_myown_env(t_data *data)
{
	data->l_env = allocation(data, 1, sizeof(t_env), 0);
	data->l_env->sec = add_dup(data, "PWD", 0);
	data->l_env->value = allocation(data, 1024, sizeof(char), 0);
	getcwd(data->l_env->value, 1024);
	data->pwd_of_mysys = add_dup(data, data->l_env->value, 0);
	data->l_env->next = allocation(data, 1, sizeof(t_env), 0);
	data->l_env->next->sec = add_dup(data, "SHLVL", 0);
	data->l_env->next->value = add_dup(data, "1", 0);
}

static void	add_pwd_if_not_exist(t_data *data)
{
	t_env	*env;

	env = data->l_env;
	while (env->next)
		env = env->next;
	env->next = allocation(data, 1, sizeof(t_env), 0);
	env = env->next;
	env->sec = add_dup(data, "PWD", 0);
	env->value = add_dup(data, data->pwd_of_mysys, 0);
}

static void	check_if_env_exist_and_get_it(t_data *data, char **env)
{
	t_env	*trav;

	if (!env[0])
		make_myown_env(data);
	else
	{
		data->env = env;
		get_env(data);
		trav = getenv_addr(data, "PWD");
		if (!trav)
		{
			data->pwd_of_mysys = allocation(data, 1024, sizeof(char), 0);
			getcwd(data->pwd_of_mysys, 1024);
			add_pwd_if_not_exist(data);
		}
		else
			data->pwd_of_mysys = add_dup(data, trav->value, 0);
		sort_env(data);
	}
}

void	init_shell_elem(t_data *data, char **av, char **env)
{
	data->args = av;
	data->old_pwd_make = 0;
	data->chk_redct_exist = 0;
	data->chk_dolla = 0;
	data->env_exec = 0;
	data->v_cmd = 0;
	data->t_token = 0;
	data->env_exec = 0;
	data->p_die = 0;
	data->p_running = 0;
	data->p_die = allocation(data, 1, sizeof(t_free), 0);
	data->p_running = allocation(data, 1, sizeof(t_free), 1);
	data->old_pwd_value = add_dup(data, "", 0);
	check_if_env_exist_and_get_it(data, env);
}
