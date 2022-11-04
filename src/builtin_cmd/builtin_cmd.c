/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 19:09:06 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	cmd_only_exec_lower(t_data *data, char *cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	i = 0;
	b_cmd = "cd export unset exit";
	sp = ft_split(b_cmd, ' ');
	free_sp(data, sp);
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

static int	check_builtin_helper(t_data *data, char *cmd)
{
	int		i;
	char	**sp;
	char	*b_cmd;

	i = 0;
	b_cmd = "env echo pwd";
	sp = ft_split(b_cmd, ' ');
	free_sp(data, sp);
	while (sp[i])
	{
		if (!ft_strcmp(sp[i], cmd))
			return (1);
		i++;
	}
	return (0);
}

int	check_builtin(t_data *data, char **cmd)
{
	int		i;

	if (cmd_only_exec_lower(data, *cmd))
		return (1);
	i = 0;
	while (cmd[0][i])
		ft_tolower(cmd[0][i++]);
	if (check_builtin_helper(data, cmd[0]))
		return (1);
	return (0);
}

void	builtin_cmd(t_data *data, t_cmd *node)
{
	if (!ft_strcmp(node->cmd[0], "cd"))
		cd_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "echo"))
		echo_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "pwd"))
		pwd_cmd(data);
	else if (!ft_strcmp(node->cmd[0], "env"))
		env_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "export"))
		export_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "unset"))
		unset_cmd(data, node);
	else if (!ft_strcmp(node->cmd[0], "exit"))
		exit_cmd(data, node);
}
