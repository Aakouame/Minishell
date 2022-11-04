/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 07:59:26 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 01:09:16 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	init_var_tokenizer(t_data *data)
{
	data->error_lexer = 0;
	data->chk_hrdoc = 0;
	data->n_line = data->beg_line;
	data->t_token = 0;
	data->qot_aftr_dolla = 0;
	data->hrdoc_delimiter_dolla = 0;
}

void	parser_phase(t_data *data)
{
	if (lexer_pt2(data))
	{
		data->chk_dolla = 258;
		data->error_lexer = 1;
		return ;
	}
	join_t_token(data);
	parser(data);
	return ;
}
