/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:15:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 14:43:27 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_nline_option(char **cmd)
{
	int	i;
	int	j;

	i = 1;
	while (!ft_strncmp(cmd[i], "-n", 2))
	{
		j = 2;
		while (cmd[i][j])
		{
			if (cmd[i][j] != 'n')
				return (i);
			j++;
		}
		i++;
		if (!cmd[i])
			return (i);
	}
	return (i);
}

static void	echo_home_env(t_data *data, t_cmd *trav, int i)
{
	char	*home;

	home = getenv("HOME");
	if (home)
		home = add_join(data, home, &trav->cmd[i][1], 1);
	else
		home = add_dup(data, &trav->cmd[i][1], 1);
	printf("%s ", home);
}

static void	echo_helper(t_data *data, t_cmd *trav, int i)
{
	if (trav->cmd[i][0] == '~' && \
			(trav->cmd[i][1] == '/' || !trav->cmd[i][1]))
		echo_home_env(data, trav, i);
	else
	{
		printf("%s", trav->cmd[i]);
		if (trav->cmd[i + 1])
			printf(" ");
	}
}

void	echo_cmd(t_data *data, t_cmd *trav)
{
	int		i;
	int		chk;

	if (trav->cmd[1])
		chk = check_nline_option(trav->cmd);
	else
	{
		printf("\n");
		return ;
	}
	i = chk;
	data->exit_status = 0;
	while (trav->cmd[i])
	{
		echo_helper(data, trav, i);
		i++;
	}
	if (chk == 1)
		printf("\n");
}
