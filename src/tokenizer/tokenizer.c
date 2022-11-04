/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:39 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 02:04:39 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	tokenizer_init(t_data *data)
{
	add_node_p_running(data, data->line);
	data->beg_line = ft_strtrim(data->line, "\t\v\r\f ");
	add_node_p_running(data, data->beg_line);
	if (!data->beg_line[0])
	{
		data->error_lexer = 1;
		return (1);
	}
	init_var_tokenizer(data);
	return (0);
}

void	tokenizer(t_data *data)
{
	if (tokenizer_init(data))
		return ;
	while (*data->n_line)
	{
		if (is_word(data, data->n_line) || is_s_quote(data, data->n_line) || \
				is_d_quote(data, data->n_line) || is_space(data, data->n_line) \
				|| is_dolla(data, data->n_line) || is_pipe(data, data->n_line) \
				|| is_i_redirection(data, data->n_line) || \
				is_o_redirection(data, data->n_line))
		{
			if (data->error_lexer)
			{
				data->chk_dolla = 258;
				return ;
			}
		}
	}
	parser_phase(data);
}
