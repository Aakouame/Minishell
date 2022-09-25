/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 19:35:09 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/05 09:43:23 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	pipe_grammar(t_token *trav, int i)
{
	//check if | was the last element in the list and not in the first
	if (trav->next && i != 0)
	{
		if (trav->next->type == W_SPACE)
		{
			trav = trav->next;
			if (trav->next->type != PIPE)
				return (1);
			return (0);
		}
		else
		{
			if (trav->next->type != PIPE)
				return (1);
			return (0);
		}

	}
	else
		return (0);
	//if (trav->type == PIPE && i != 0 && trav)
	//{

	//}
}

static int	redirection_grammar(t_token *trav)
{
	if (trav->next)
	{
		if (trav->next->type == W_SPACE)
		{
			trav = trav->next;
			if (trav->next->type == WRD || trav->next->type == D_QUOT\
					|| trav->next->type == S_QUOT || trav->next->type == DOLLA)
				return (1);
			return (0);
		}
		else
		{
			if (trav->next->type == WRD || trav->next->type == D_QUOT\
					|| trav->next->type == S_QUOT || trav->next->type == DOLLA)
				return (1);
			return (0);
		}
	}
	else
		return (0);
}

int	lexer_pt2(t_data *data)
{
	t_token *trav;
	int			i;

	i = 0;
	trav = data->t_token;
	while (trav)
	{
		if (trav->type == PIPE)
		{
			if (!pipe_grammar(trav, i))
			{
				free_token_node(data);
				printf("minishell: syntax error near unexpected token '|'\n");
				return (1);
			}
		}
		else if (trav->type == O_TRNC || trav->type == O_APEND \
				|| trav->type == I_TRNC || trav->type == I_APEND)
		{
			if (!redirection_grammar(trav))
			{
				free_token_node(data);
				if (trav->type == O_TRNC)
					printf("minishell: syntax error near unexpected token '>'\n");
				else if (trav->type == O_APEND)
					printf("minishell: syntax error near unexpected token '>>'\n");
				else if (trav->type == I_TRNC)
					printf("minishell: syntax error near unexpected token '<'\n");
				else if (trav->type == I_APEND)
					printf("minishell: syntax error near unexpected token '<<'\n");
				return (1);
			}
		}
		trav = trav->next;
		i++;
		//if (pipe_grammar(trav, i))
		//{
		//}
		//if (redirection_grammar(trav, i))
		//{
		//	free_token_node(data);
		//	return (1);
		//}
	}
	return (0);
}
//redirection should not be in the end with no file name 
