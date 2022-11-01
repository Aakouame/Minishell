/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_identifier2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 06:55:34 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/27 11:41:40 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	is_i_redirection(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;
	int			typ;

	data->i = 0;
	if (n_line[data->i] != '<')
		return (0);
	typ = I_APEND;
	while (n_line[data->i] == '<')
		data->i++;
	if (data->i == 1)
		typ = I_TRNC;
	//{
	//	if (n_line[1] != '>')
	//	{
	//		data->i++;
	//		typ = O_TRNC;
	//		//ft_init_tokenizer(data, &n_line[i], i, O_TRNC);
	//		return (1);
	//	}
	//	data->i++;
	//}
	//if (n_line[data->i] != '>')
	//	typ = O_APEND;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = typ;
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
	//same function for other redirection check if < are multiple redirect
	if (typ == I_APEND)

	{
		redirection_lexer('<', trav->value);
		data->hrdoc_delimiter_dolla = 1;
	}
		//ft_init_tokenizer(data, &n_line[i], i, O_APEND);
	return (1);
}

int	is_o_redirection(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;
	int			typ;

	data->i = 0;
	if (n_line[data->i] != '>')
		return (0);
	typ = O_APEND;
	while (n_line[data->i] == '>')
		data->i++;
	if (data->i == 1)
		typ = O_TRNC;
	//{
	//	if (n_line[1] != '>')
	//	{
	//		data->i++;
	//		typ = O_TRNC;
	//		//ft_init_tokenizer(data, &n_line[i], i, O_TRNC);
	//		return (1);
	//	}
	//	data->i++;
	//}
	//if (n_line[data->i] != '>')
	//	typ = O_APEND;

	data->n_line = &n_line[data->i];
	trav = allocation(data, 1, sizeof(t_token), 1);
	trav->type = typ;
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
	if (typ == O_APEND)
		redirection_lexer('>', trav->value);
	//same function for other redirection check if < are multiple redirect
	//redirection_lexer(trav->value, '>');
		//ft_init_tokenizer(data, &n_line[i], i, O_APEND);
	return (1);
}

int	is_dolla(t_data *data, char *n_line)
{
	t_token	*trav;
	t_token	*node;

	data->i = 0;
	if (n_line[data->i] != '$')
		return (0);
	else
	{
		data->i++;
		while (n_line[data->i] != ' ' && !(n_line[data->i] >= 9 && n_line[data->i] <= 13) \
				&& n_line[data->i] != '|' && n_line[data->i] != '>' && n_line[data->i] != '<' \
				&& n_line[data->i] != '\"' && n_line[data->i] != '\'' && n_line[data->i])
			data->i++;
	}
	if (n_line[data->i] == '\"' || n_line[data->i] == '\'')
		data->qot_aftr_dolla = 1;
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
	if (!data->t_token)
		data->t_token = trav;
	else
	{
		node = data->t_token;
		while (node->next)
			node = node->next;
		node->next = trav;
	}
	//ft_init_tokenizer(data, &n_line[i], i, DOLLA);
	return (1);
}
