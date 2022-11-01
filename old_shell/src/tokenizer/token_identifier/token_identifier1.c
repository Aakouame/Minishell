/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:48:01 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/27 13:51:50 by akouame          ###   ########.fr       */
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

int	is_s_quote(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

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
	return (1);
}

int	is_d_quote(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

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
		if (!data->t_token)
			data->t_token = trav;
		else
		{
			node = data->t_token;
			while (node->next)
				node = node->next;
			node->next = trav;
		}
		//if (quotes_lexer('\"', trav->value))
		//	data->error_lexer = 1;
	}
	return (1);
}

int	is_pipe(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

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
	if (!data->t_token)
		data->t_token = trav;
	else
	{
		node = data->t_token;
		while (node->next)
			node = node->next;
		node->next = trav;
	}
	if (pipe_lexer(trav->value))
		data->error_lexer = 1;
	return (1);
}

int	is_space(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

	data->i = 0;
	if (n_line[data->i] != ' ' && !(n_line[data->i] >= 9 && n_line[data->i] <= 13))
		return (0);
	while (n_line[data->i] == ' ' || (n_line[data->i] >= 9 && n_line[data->i] <= 13))
		data->i++;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = W_SPACE;
	trav->value = allocation(data, data->i + 1, sizeof(char), 1);
	dup_from_addr_to_other(trav->value, n_line, data->n_line);
	if (!data->t_token)
		data->t_token = trav;
	else
	{
		node = data->t_token;
		while (node->next)
			node = node->next;
		node->next = trav;
	}
	return (1);
}

int	unacceptable_token(t_data *data, char c)
{
	char *sp;

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

int	is_word(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

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
		if (!data->t_token)
			data->t_token = trav;
		else
		{
			node = data->t_token;
			while (node->next)
				node = node->next;
			node->next = trav;
		}
		if (word_lexer(trav->value))
			data->error_lexer = 1;
	}
	return (1);
}
