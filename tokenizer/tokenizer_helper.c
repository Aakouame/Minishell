/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:45:44 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/04 17:45:48 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_s_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\'')
		return (0);
	else if (n_line[data->i] == '\'')
		is_quote_helper(data, '\'', n_line);
	return (1);
}

int	is_d_quote(t_data *data, char *n_line)
{
	data->i = 0;
	if (n_line[data->i] != '\"')
		return (0);
	else if (n_line[data->i] == '\"')
		is_quote_helper(data, '\"', n_line);
	return (1);
}

int	is_o_redirection(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '<')
		return (0);
	while (n_line[i] == '<')
	{
		if (n_line[1] != '<')
		{
			i++;
			ft_init_tokenizer(data, &n_line[i], i, I_TRNC);
			return (1);
		}
		i++;
	}
	if (n_line[i] != '<')
	{
		ft_init_tokenizer(data, &n_line[i], i, I_APEND);
		data->chk_hrdoc = 1;
	}
	return (1);
}

int	is_i_redirection(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '>')
		return (0);
	while (n_line[i] == '>')
	{
		if (n_line[1] != '>')
		{
			i++;
			ft_init_tokenizer(data, &n_line[i], i, O_TRNC);
			return (1);
		}
		i++;
	}
	if (n_line[i] != '>')
		ft_init_tokenizer(data, &n_line[i], i, O_APEND);
	return (1);
}

int	is_dolla(t_data *data, char *n_line)
{
	int	i;

	i = 0;
	if (n_line[i] != '$')
		return (0);
	if (n_line[i] == '$')
	{
		i++;
		while (n_line[i] != ' ' && !(n_line[i] >= 9 && n_line[i] <= 13) \
				&& n_line[i] != '|' && n_line[i] != '>' && n_line[i] != '<' && n_line[i])
		{
			//if (n_line[i] == '$')
			//{
			//	i++;
			//	break ;
			//}
			i++;
		}
	}
	ft_init_tokenizer(data, &n_line[i], i, DOLLA);
	return (1);
}
