/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:11:41 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/03 19:42:50 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	env_shlvl_helper(t_data *data, t_env *env)
{
	char	*hold;

	hold = env->value;
	env->value = ft_itoa(ft_atoi(env->value) + 1);
	add_node_p_die(data, env->value);
}

t_env	*getenv_addr(t_data *data, char *sec)
{
	t_env	*env;

	if (!data->l_env)
		return (0);
	env = data->l_env;
	while (ft_strcmp(env->sec, sec) && env->next)
		env = env->next;
	if (!ft_strcmp(env->sec, sec))
		return (env);
	else
		return (0);
}

void	env_cmd(t_data *data, t_cmd *cmd)
{
	t_env	*trav;

	trav = data->l_env;
	if (cmd->cmd[1] != 0)
	{
		data->chk_dolla = 1;
		ft_putstr_fd("env: ", 2);
		stdanred_error(": No such file or directory\n", cmd->cmd[1], 0);
	}
	else
	{
		data->chk_dolla = 0;
		while (trav)
		{
			if (!trav->value[0])
				trav = trav->next;
			else
				printf("%s=%s\n", trav->sec, trav->value);
			if (!trav)
				break ;
			trav = trav->next;
		}
	}
}
