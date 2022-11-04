/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 00:31:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:39:56 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_pipe(t_data *data, char *n_line)
{
	t_token	*trav;

	data->i = 0;
	if (n_line[data->i] != '|')
		return (0);
	while (n_line[data->i] == '|')
		data->i++;
	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = PIPE;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	token_linker(data, trav);
	if (pipe_lexer(trav->value))
		data->error_lexer = 1;
	return (1);
}

int	is_space(t_data *data, char *n_line)
{
	t_token	*trav;

	data->i = 0;
	if (n_line[data->i] != ' ' && !(n_line[data->i] >= 9 && \
				n_line[data->i] <= 13))
		return (0);
	while (n_line[data->i] == ' ' || (n_line[data->i] >= 9 && \
				n_line[data->i] <= 13))
		data->i++;
	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = W_SPACE;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	token_linker(data, trav);
	return (1);
}
