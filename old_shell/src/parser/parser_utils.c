/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:12:08 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/29 14:34:28 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	allocate_red_node(t_data *data, int red_len)
{
	t_red	*head;
	t_red	*node;
	int		i;

	i = 1;
	if (red_len != 0)
	{
		head = allocation(data, 1, sizeof(t_red), 1);
		data->trav_cmd->redirect = head;
	}
	while (i < red_len)
	{
		node = allocation(data, 1, sizeof(t_red), 1);
		head->next = node;
		head = node;
		i++;
	}
}

void	allocate_cmd_node(t_data *data)
{
	t_cmd	*head;
	t_cmd	*node;
	int		i;
	int		len;

	i = 1;
	len = count_cmd(data) + 1;
	head = allocation(data, 1, sizeof(t_cmd), 1);
	head->f_out = 1;
	data->v_cmd = head;
	while (i < len)
	{
		node = allocation(data, 1, sizeof(t_cmd), 1);
		node->f_out = 1;
		head->next = node;
		head = node;
		i++;
	}
}
