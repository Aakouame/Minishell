/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 02:54:40 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:37:32 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*before_equal(t_data *data, char *cmd)
{
	int		i;
	int		hold;
	char	*chk;

	i = 0;
	hold = ft_strcspn(cmd, "=");
	if (cmd[hold - 1] == '+')
		hold--;
	chk = allocation(data, hold + 1, sizeof(char), 1);
	ft_strlcpy(chk, cmd, hold + 1);
	return (chk);
}

int	if_exist_or_not(t_data *data, char *cmd)
{
	t_env	*trav;
	char	*ptr;

	ptr = cmd;
	if (check_if_equal_or_wrd(cmd))
		ptr = before_equal(data, cmd);
	trav = getenv_addr(data, ptr);
	if (trav)
		return (0);
	return (1);
}

static int	only_accepted_char(char *cmd, int hold)
{
	int	i;

	i = 1;
	if (ft_isdigit(cmd[0]) || (!ft_isalnum(cmd[0]) \
				&& cmd[0] != '_'))
		return (1);
	while (i < hold)
	{
		if (!ft_isdigit(cmd[i]) && !ft_isalnum(cmd[i]) \
				&& cmd[i] != '+' && cmd[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

static int	check_export_error_helper(t_data *data, char *cmd, int hold)
{
	int	i;

	i = 0;
	if (cmd[hold - 1] == '+')
		hold--;
	while (i < hold)
	{
		if (cmd[i] == '+')
			return (1);
		i++;
	}
	if (cmd[hold] == '+')
		data->chk_export_plus = 1;
	return (0);
}

int	check_export_error(t_data *data, char *cmd)
{
	int	hold;
	int	i;

	i = 0;
	hold = ft_strcspn(cmd, "=");
	if (only_accepted_char(cmd, hold))
		return (1);
	while (cmd[i] != '=' && cmd[i])
		i++;
	if (cmd[i] == 0)
	{
		i = 0;
		while (cmd[i] != '+' && cmd[i])
			i++;
		if (cmd[i] == 0)
			return (0);
		else
			return (1);
	}
	if (check_export_error_helper(data, cmd, hold))
		return (1);
	return (0);
}
