/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_collector.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 04:51:31 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 00:06:53 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	add_node_p_die(t_data *data, void *addr)
{
	t_free	*head;

	head = data->p_die;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_free));
	head->next->value = addr;
}

void	add_node_p_running(t_data *data, void *addr)
{
	t_free	*head;

	head = data->p_running;
	if (!head)
		return ;
	while (head->next)
		head = head->next;
	head->next = ft_calloc(1, sizeof(t_free));
	head->next->value = addr;
}

void	free_data_running_process(t_data *data, int chk)
{
	t_free	*node;

	node = data->p_running;
	if (chk)
		node = data->p_running->next;
	while (node)
	{
		free(node->value);
		free(node);
		node = node->next;
	}
	if (chk)
		data->p_running->next = 0;
}

void	free_data_die_process(t_data *data)
{
	t_free	*node;

	node = data->p_die;
	free_data_running_process(data, 0);
	while (node)
	{
		free(node->value);
		free(node);
		node = node->next;
	}
}
