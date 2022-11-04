/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:55:34 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:38:55 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_i_redirection(t_data *data, char *n_line)
{
	t_token	*trav;
	int		typ;

	data->i = 0;
	if (n_line[data->i] != '<')
		return (0);
	typ = I_APEND;
	while (n_line[data->i] == '<')
		data->i++;
	if (data->i == 1)
		typ = I_TRNC;
	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = typ;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	token_linker(data, trav);
	if (typ == I_APEND)
	{
		redirection_lexer('<', trav->value);
		data->hrdoc_delimiter_dolla = 1;
	}
	return (1);
}

int	is_o_redirection(t_data *data, char *n_line)
{
	t_token	*trav;
	int		typ;

	data->i = 0;
	if (n_line[data->i] != '>')
		return (0);
	typ = O_APEND;
	while (n_line[data->i] == '>')
		data->i++;
	if (data->i == 1)
		typ = O_TRNC;
	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = typ;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	token_linker(data, trav);
	if (typ == O_APEND)
		redirection_lexer('>', trav->value);
	return (1);
}

static void	is_dolla_helper(t_data *data, char *n_line)
{
	t_token	*trav;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = DOLLA;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	if (!data->hrdoc_delimiter_dolla)
	{
		expand_the_value(data, trav->value);
		trav->value = data->buff_expnd;
	}
	token_linker(data, trav);
}

int	is_dolla(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '$')
		return (0);
	else
	{
		data->i++;
		while (n_line[data->i] != ' ' && !(n_line[data->i] >= 9 && \
					n_line[data->i] <= 13) && n_line[data->i] != '|' && \
				n_line[data->i] != '>' && n_line[data->i] != '<' && \
				n_line[data->i] != '\"' && n_line[data->i] != '\'' && \
				n_line[data->i])
			data->i++;
	}
	if (n_line[data->i] == '\"' || n_line[data->i] == '\'')
		data->qot_aftr_dolla = 1;
	is_dolla_helper(data, n_line);
	return (1);
}
