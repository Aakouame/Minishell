/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 12:22:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/03 19:26:58 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	pwd_cmd_helper(t_data *data, char **cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd[i])
	{
		if (cmd[i][0] == '-' && cmd[i][1] != '-')
		{
			j = 1;
			while (cmd[i][j])
			{
				if (cmd[i][j] != 'L' && cmd[i][j] != 'P')
				{
					stdanred_error("pwd: -", 0, 1);
					stdanred_error(": invalid option\n", &cmd[i][j], 0);
					ft_putstr_fd("pwd: usage: pwd [-LP]\n", 2);
					return (1);
				}
				j++;
			}
		}
		i++;
	}
	return (0);
}

void	pwd_cmd(t_data *data)
{
	t_env	*trav;
	char	**cmd;

	trav = data->l_env;
	cmd = &data->v_cmd->cmd[1];
	if (cmd)
	{
		if (pwd_cmd_helper(data, cmd))
			return ;
	}
	printf("%s\n", data->pwd_of_mysys);
}
