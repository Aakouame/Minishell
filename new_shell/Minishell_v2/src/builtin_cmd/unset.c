/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:18:49 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 05:03:26 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	find_that_element(t_data *data, char *elem)
{
	t_env	*trav;
	t_env	*trav_prev;

	if (!data->l_env)
		return ;
	trav = data->l_env;
	trav_prev = data->l_env;
	while (ft_strcmp(trav->sec, elem) && trav->next)
	{
		trav_prev = trav;
		trav = trav->next;
	}
	if (!ft_strcmp(trav->sec, elem))
	{
		if (trav == data->l_env)
			data->l_env = trav->next;
		else
			trav_prev->next = trav->next;
		if (!data->env)
			return ;
	}
}

int	unset_error_checking(t_data *data, char *cmd)
{
	int	i;

	i = 1;
	if (ft_isdigit(cmd[0]) || (!ft_isalnum(cmd[0]) \
				&& cmd[0] != '_'))
		return (1);
	while (cmd[i])
	{
		if (!ft_isdigit(cmd[i]) && !ft_isalnum(cmd[i]) \
				&& cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

void	unset_cmd(t_data *data, t_cmd *trav_c)
{
	int		i;

	i = 1;
	if (!trav_c->cmd[1])
		return ;
	while (trav_c->cmd[i])
	{
		if (!unset_error_checking(data, trav_c->cmd[i]))
			find_that_element(data, trav_c->cmd[i]);
		else
		{
			data->chk_dolla = 1;
			dup2(data->s_stdout, STDOUT_FILENO);
			printf("minishell: unset: `%s': not a valid identifier\n", \
					trav_c->cmd[i]);
			close(data->s_stdout);
		}
		i++;
	}
}
