/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 01:44:45 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 04:51:51 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dup_opt_equal_helper(t_env **env, char *cmd, int *hold)
{
	int	i;

	i = 0;
	while (i < *hold)
	{
		env[0]->sec[i] = cmd[i];
		i++;
	}
	env[0]->sec[i] = 0;
	if (cmd[*hold] == '+')
		*(hold) += 2;
	else
		*(hold) += 1;
}

int	check_existence_helper(t_data *data, char *cmd, char *chk, int hold)
{
	t_env	*trav;
	char	*n_cmd;
	char	*hld;

	trav = getenv_addr(data, chk);
	if (trav)
	{
		hld = trav->value;
		if (data->chk_export_plus == 1)
		{
			hold += 2;
			n_cmd = &cmd[hold];
			trav->value = add_join(data, trav->value, n_cmd, 0);
		}
		else
		{
			n_cmd = &cmd[++hold];
			trav->value = add_dup(data, n_cmd, 0);
		}
		return (1);
	}
	return (0);
}

int	check_existence(t_data *data, char *cmd, int hold, t_env *env)
{
	int		i;
	char	*chk;

	i = 0;
	chk = allocation(data, hold + 1, sizeof(char), 1);
	ft_strlcpy(chk, cmd, hold + 1);
	if (check_existence_helper(data, cmd, chk, hold))
		return (1);
	return (0);
}

int	dup_opt_wrd(t_data *data, t_env *env, char *cmd)
{
	t_env	*trav;

	trav = data->l_env;
	trav = getenv_addr(data, cmd);
	if (trav)
		return (0);
	else
	{
		env->sec = add_dup(data, cmd, 0);
		env->value = add_dup(data, "", 0);
	}
	return (1);
}

int	check_if_equal_or_wrd(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i] == '=')
			return (1);
		i++;
	}
	return (0);
}
