/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_token_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 01:21:06 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:55:31 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static t_token	*count_len_join_token_helper(t_data *data, t_token *trav)
{
	if (trav->type == O_TRNC || trav->type == O_APEND || \
			trav->type == I_TRNC || trav->type == I_APEND)
	{
		data->i++;
		if (trav->next->type == W_SPACE)
			trav = trav->next->next;
		else
			trav = trav->next;
		while (trav->type == WRD || trav->type == DOLLA || \
				trav->type == S_QUOT || trav->type == D_QUOT)
		{
			trav = trav->next;
			if (!trav)
				break ;
		}
	}
	else if (trav->type == PIPE)
	{
		data->i++;
		trav = trav->next;
	}
	return (trav);
}

static int	count_len_join_token(t_data *data)
{
	t_token	*trav;

	data->i = 0;
	trav = data->t_token;
	while (trav)
	{
		if (trav->type == WRD || trav->type == DOLLA || \
				trav->type == S_QUOT || trav->type == D_QUOT)
		{
			data->i++;
			while (trav->type == WRD || trav->type == DOLLA || \
					trav->type == S_QUOT || trav->type == D_QUOT)
			{
				trav = trav->next;
				if (!trav)
					break ;
			}
		}
		else if (trav->type == W_SPACE)
			trav = trav->next;
		else
			trav = count_len_join_token_helper(data, trav);
	}
	return (data->i);
}

void	allocate_join_token(t_data *data)
{
	int		len;
	t_token	*head;
	t_token	*node;

	len = count_len_join_token(data) - 1;
	head = allocation(data, 1, sizeof(t_token), 1);
	data->t_join = head;
	while (len--)
	{
		node = allocation(data, 1, sizeof(t_token), 1);
		head->next = node;
		head = node;
	}
}
