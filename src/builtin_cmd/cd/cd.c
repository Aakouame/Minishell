/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:22:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/13 14:53:28 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	cd_cmd(t_data *data, t_cmd *node)
{
	if (node->cmd[1])
	{
		if (node->cmd[1][0] == '-')
		{
			cd_between_pwd_and_oldpwd(data, node->cmd[1]);
			return ;
		}
	}
	cd_everywhere_at_once(data, node->cmd[1]);
}
