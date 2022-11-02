/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:38:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 03:31:32 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	exit_stat(t_data *data, char *cmd, int stat, int chk)
{
	//dup2(data->s_stdout, STDOUT_FILENO);
	printf("exit\n");
	if (chk == 1)
		printf("minishell: exit: %s: numeric argument required\n", cmd);
	//close(data->s_stdout);
	free_data_die_process(data);
	//data->chk_dolla = stat;
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

int	status_len(int stat)
{
	int	i;

	i = 0;
	while (stat)
	{
		stat /= 10;
		i++;
	}
	return (i);
}

static void	exit_number(t_data *data, char *nbr)
{
	//long long	nb_exit;
	int	nb_exit;
	//int	len;

	//nb_exit = ft_atoi(nbr);
	////if (nb)
	//len = 19;
	//if (nb_exit < 0)
	//	len++;
	//printf("%d | %d\n", status_len(nb_exit), len);
	//if (status_len(nb_exit) >= len)
	//{
	int	i;

	i = 0;
	if (nbr[i] == '+')
		i++;
	while (nbr[i] && nbr[i] == '0')
		i++;
	printf("%s\n", &nbr[i]);
	if (check_if_llong(&nbr[i]))
		exit_stat(data, nbr, 255, 1);
	//}
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
				data->chk_dolla = 1;
				dup2(data->s_stdout, STDOUT_FILENO);
				printf("exit\n");
				printf("minishell: exit: too many arguments\n");
				close(data->s_stdout);
			}
		}
		else
			exit_stat(data, trav->cmd[1], 255, 1);
	}
}
