/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_hrdoc_data.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 09:05:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 02:03:01 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	heredoc_alloc(t_data *data, char *dolla)
{
	t_env	*env;

	env = getenv_addr(data, dolla);
	if (env)
	{
		free(dolla);
		dolla = env->value;
	}
	else
		return ;
	data->hrdoc_len += ft_strlen(dolla);
}

static void	hrdoc_dolla_count(t_data *data, char *ptr)
{
	int		len;
	char	*dolla;
	t_env	*trav_env;

	trav_env = data->l_env;
	if (ptr[data->i] == '$' && ft_acceptable_char(ptr[data->i + 1]))
	{
		data->i++;
		len = 0;
		while (ft_acceptable_char(ptr[data->i]))
		{
			data->i++;
			len++;
		}
		dolla = ft_calloc(len + 1, sizeof(char));
		data->i -= len;
		len = 0;
		while (ft_acceptable_char(ptr[data->i]))
			dolla[len++] = ptr[data->i++];
		heredoc_alloc(data, dolla);
	}
}

static void	count_len_hrdoc_dolla_helper(t_data *data, char *ptr)
{
	char	*tmp;

	if (ptr[data->i + 1] == '?')
	{
		data->i += 2;
		tmp = ft_itoa(data->chk_dolla);
		data->hrdoc_len += ft_strlen(tmp);
		free(tmp);
	}
	if (ptr[data->i + 1] == '0')
	{
		data->hrdoc_len += ft_strlen(&data->args[0][2]);
		data->i += 2;
	}
}

static void	count_len_hrdoc_dolla(t_data *data, char *ptr)
{
	count_len_hrdoc_dolla_helper(data, ptr);
	if (ptr[data->i + 1] >= '1' && ptr[data->i + 1] <= '9')
		data->i += 2;
	if (ptr[data->i + 1] == '$')
	{
		while (ptr[data->i] == '$')
		{
			if (ptr[data->i + 1] == '$')
				data->i += 2;
			else
				break ;
		}
	}
	if ((ptr[data->i + 1] >= 'A' && ptr[data->i + 1] <= 'Z') || \
			(ptr[data->i + 1] >= 'a' && ptr[data->i + 1] <= 'z') || \
			ptr[data->i + 1] == '_')
		hrdoc_dolla_count(data, ptr);
	if (ptr[data->i + 1] == '\"' || ptr[data->i + 1] == '\'')
		return ;
}

int	len_hrdoc_data(t_data *data, char *ptr)
{
	data->i = 0;
	data->hrdoc_len = 0;
	while (ptr[data->i])
	{
		if (ptr[data->i] == '$')
			count_len_hrdoc_dolla(data, ptr);
		data->i++;
		data->hrdoc_len++;
	}
	return (data->hrdoc_len);
}
