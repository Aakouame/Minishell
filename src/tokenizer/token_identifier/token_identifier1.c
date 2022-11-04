/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:48:01 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 14:24:46 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	is_s_quote_helper(t_data *data, char *n_line)
{
	t_token	*trav;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = S_QUOT;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	if (quotes_lexer('\'', trav->value))
	{
		data->error_lexer = 1;
		return (1);
	}
	trav->value = ft_strtrim(trav->value, "'");
	add_node_p_running(data, trav->value);
	token_linker(data, trav);
	return (0);
}

int	is_s_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\'')
		return (0);
	else if (n_line[data->i++] == '\'')
	{
		while (n_line[data->i])
		{
			if (n_line[data->i] == '\'')
			{
				data->i++;
				break ;
			}
			data->i++;
		}
		if (is_s_quote_helper(data, n_line))
			return (1);
	}
	return (1);
}

static int	is_d_quote_helper(t_data *data, char *n_line)
{
	t_token	*trav;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = D_QUOT;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	if (quotes_lexer('\"', trav->value))
	{
		data->error_lexer = 1;
		return (1);
	}
	expand_the_value(data, trav->value);
	trav->value = ft_strtrim(data->buff_expnd, "\"");
	add_node_p_running(data, trav->value);
	token_linker(data, trav);
	return (0);
}

int	is_d_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\"')
		return (0);
	else if (n_line[data->i++] == '\"')
	{
		while (n_line[data->i])
		{
			if (n_line[data->i] == '\"')
			{
				data->i++;
				break ;
			}
			data->i++;
		}
		if (is_d_quote_helper(data, n_line))
			return (1);
	}
	return (1);
}

int	is_word(t_data *data, char *n_line)
{
	t_token	*trav;

	data->i = 0;
	while (n_line[data->i])
	{
		if (unacceptable_token(data, n_line[data->i]))
			break ;
		data->i++;
	}
	if (data->i == 0)
		return (0);
	else
	{
		data->n_line = &n_line[data->i];
		trav = allocation(data, 1, sizeof(t_token), 1);
		trav->type = WRD;
		trav->value = allocation(data, data->i + 1, sizeof(char), 1);
		dup_from_addr_to_other(trav->value, n_line, data->n_line);
		token_linker(data, trav);
		if (word_lexer(trav->value))
			data->error_lexer = 1;
	}
	return (1);
}
