/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:14:33 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:40:15 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	dup_from_addr_to_other(char *ptr, char *begin, char *end)
{
	int	i;

	i = 0;
	while (&begin[i] != &end[0])
	{
		ptr[i] = begin[i];
		i++;
	}
}

int	unacceptable_token(t_data *data, char c)
{
	char	*sp;

	sp = "<|>$\t\v\r\f \"\'";
	data->j = 0;
	while (sp[data->j])
	{
		if (c == sp[data->j])
			return (1);
		data->j++;
	}
	return (0);
}

void	token_linker(t_data *data, t_token *trav)
{
	t_token	*node;

	if (!data->t_token)
		data->t_token = trav;
	else
	{
		node = data->t_token;
		while (node->next)
			node = node->next;
		node->next = trav;
	}
}
