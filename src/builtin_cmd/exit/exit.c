/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:38:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 11:17:00 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	exit_stat(t_data *data, char *cmd, int stat, int chk)
{
	ft_putstr_fd("exit\n", 2);
	if (chk == 1)
	{
		stdanred_error("exit: ", 0, 1);
		stdanred_error(": numeric argument required\n", cmd, 0);
	}
	free_data_die_process(data);
	exit(stat);
}

static int	check_nbr(char *arg)
{
	if (*arg == '-' || *arg == '+')
		arg++;
	while (*arg)
	{
		if (!ft_isdigit(*arg))
			return (0);
		arg++;
	}
	return (1);
}

static int	check_if_llong(char *nbr)
{
	int		i;
	char	*ll;

	if (nbr[0] == '-')
	{
		if (ft_strlen(nbr) < 20)
			return (0);
		else if (ft_strlen(nbr) > 20)
			return (1);
		i = 1;
		ll = LL_MIN;
	}
	else
	{
		if (ft_strlen(nbr) < 19)
			return (0);
		else if (ft_strlen(nbr) > 19)
			return (1);
		i = 0;
		ll = LL_MAX;
	}
	if (check_if_llong_helper(nbr, &i, &ll))
		return (1);
	else
		return (0);
}

static void	exit_number(t_data *data, char *nbr)
{
	int	nb_exit;
	int	i;

	i = 0;
	if (nbr[i] == '+')
		i++;
	while (nbr[i] && nbr[i] == '0')
		i++;
	if (check_if_llong(&nbr[i]))
		exit_stat(data, nbr, 255, 1);
	nb_exit = ft_atoi(nbr);
	exit_stat(data, 0, (nb_exit % 256), 0);
}

void	exit_cmd(t_data *data, t_cmd *trav)
{
	if (!trav->cmd[1])
		exit_stat(data, 0, 0, 0);
	else
	{
		if (check_nbr(trav->cmd[1]))
		{
			if (!trav->cmd[2])
				exit_number(data, trav->cmd[1]);
			else
			{
				data->exit_status = 1;
				ft_putstr_fd("exit\nminishell: exit: too many arguments\n", 2);
			}
		}
		else
			exit_stat(data, trav->cmd[1], 255, 1);
	}
}
