/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pt1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/27 17:15:30 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 14:26:25 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	word_lexer(char *token)
{
	int	semi_colum;

	semi_colum = 0;
	while (*token)
	{
		if (*token == ';')
			semi_colum++;
		token++;
	}
	if (semi_colum >= 2)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `;;'\n", 2);
		return (1);
	}
	return (0);
}

int	pipe_lexer(char *token)
{
	if (token[0] == '|')
	{
		if (token[1] == '|')
		{
			ft_putstr_fd(\
					"minishell: syntax error near unexpected token `|'\n", 2);
			return (1);
		}
	}
	return (0);
}

int	quotes_lexer(char quote, char *token)
{
	int	count;

	count = 0;
	while (*token)
	{
		if (*token == quote)
			count++;
		token++;
	}
	if (count % 2 != 0)
	{
		ft_putstr_fd("minishell: unclosed quotes\n", 2);
		return (1);
	}
	return (0);
}

int	redirection_lexer(char redirect, char *token)
{
	if (ft_strlen(token) > 2)
	{
		if (redirect == '>')
			ft_putstr_fd(\
					"minishell: syntax error near unexpected token `>>'\n", 2);
		if (redirect == '<')
			ft_putstr_fd(\
					"minishell: syntax error near unexpected token `<<'\n", 2);
		return (1);
	}
	return (0);
}
