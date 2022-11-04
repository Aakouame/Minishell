/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 09:38:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 12:34:48 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	free_sp(t_data *data, char **sp)
{
	int	i;

	i = 0;
	add_node_p_running(data, sp);
	while (sp[i])
		add_node_p_running(data, sp[i++]);
}
