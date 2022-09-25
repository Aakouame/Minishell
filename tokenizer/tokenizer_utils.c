/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:54 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/05 10:06:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_token_node(t_data *data)
{
	t_token	*trav;

	trav = data->t_token;
	while (trav)
	{
		if (trav->value != NULL)
			free(trav->value);
		free(trav);
		trav = trav->next;
	}
}

int	ft_acceptable_char(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	else if (c >= 65 && c <= 90)
		return (1);
	else if (c >= 97 && c <= 122)
		return (1);
	else if (c == '_')
		return (1);
	else
		return (0);
}

void	is_quote_helper(t_data *data, int c, char *n_line)
{
	data->i++;
	while (n_line[data->i])
	{
		if (n_line[data->i] == c)
		{
			data->i++;
			while (n_line[data->i])
			{
				if (n_line[data->i] == ' ' || (n_line[data->i] >= 9 && n_line[data->i] <= 13)\
						|| n_line[data->i] == '|' || n_line[data->i] == '>' || n_line[data->i] == '<')
				{
					ft_init_tokenizer(data, &n_line[data->i], data->i, S_QUOT);
					return ;
				}
				data->i++;
				if (n_line[data->i] == c)
					break ;
			}
		}
		data->i++;
	}
	ft_init_tokenizer(data, &n_line[data->i], data->i, D_QUOT);
}
