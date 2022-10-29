/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:35:09 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/27 14:35:00 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static int	pipe_grammar(t_token *trav, int i)
{
	if (trav->next && i != 0)
	{
		if (trav->next->type == W_SPACE)
			trav = trav->next;
		if (trav->next->type != PIPE)
			return (1);
	}
	return (0);
}

static int	redirection_grammar(t_token *trav)
{
	if (trav->next)
	{
		if (trav->next->type == W_SPACE)
			trav = trav->next;
		if (trav->next->type == WRD || trav->next->type == D_QUOT \
				|| trav->next->type == S_QUOT || trav->next->type == DOLLA)
			return (1);
	}
	return (0);
}

static int	lexer_pt2_helper(t_token *trav)
{
	if (!redirection_grammar(trav))
	{
		if (trav->type == O_TRNC)
			printf("minishell: syntax error near unexpected token `>'\n");
		else if (trav->type == O_APEND)
			printf("minishell: syntax error near unexpected token `>>'\n");
		else if (trav->type == I_TRNC)
			printf("minishell: syntax error near unexpected token `<'\n");
		else if (trav->type == I_APEND)
			printf("minishell: syntax error near unexpected token `<<'\n");
		return (1);
	}
	return (0);
}

int	lexer_pt2(t_data *data)
{
	t_token	*trav;
	int		i;

	i = 0;
	trav = data->t_token;
	while (trav)
	{
		if (trav->type == PIPE)
		{
			if (!pipe_grammar(trav, i))
			{
				printf("minishell: syntax error near unexpected token `|'\n");
				return (1);
			}
		}
		else if (trav->type == O_TRNC || trav->type == O_APEND \
				|| trav->type == I_TRNC || trav->type == I_APEND)
		{
			if (lexer_pt2_helper(trav))
				return (1);
		}
		trav = trav->next;
		i++;
	}
	return (0);
}
