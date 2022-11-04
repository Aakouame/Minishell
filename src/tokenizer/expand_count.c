/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_count.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 17:25:55 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 11:17:00 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	check_if_exist_len_env(t_data *data, char *tmp)
{
	t_env	*env;

	env = getenv_addr(data, tmp);
	if (!env)
		return ;
	else
		data->exp_len += ft_strlen(env->value);
}

static void	count_len_status_and_program(t_data *data, char *value)
{
	char	*tmp;

	if (value[data->i] == '0')
		data->exp_len += ft_strlen(ft_strrchr(data->args[0], '/') + 1);
	else
	{
		tmp = ft_itoa(data->exit_status);
		add_node_p_running(data, tmp);
		data->exp_len += ft_strlen(tmp);
	}
	data->i++;
}

static int	count_len_of_expand_helper(t_data *data, char *value)
{
	if (value[data->i] == '0' || value[data->i] == '?')
	{
		count_len_status_and_program(data, value);
		return (1);
	}
	else if (value[data->i] == '$' || (value[data->i] > '0' \
				&& value[data->i] <= '9'))
	{
		data->i++;
		return (1);
	}
	else if (value[data->i] == 0)
	{
		if (!data->qot_aftr_dolla)
			data->exp_len++;
		return (1);
	}
	return (0);
}

static void	count_len_of_expand(t_data *data, char *value)
{
	char	*tmp;
	int		j;

	data->i++;
	j = 0;
	if (count_len_of_expand_helper(data, value))
		return ;
	else if (value[data->i] == '\"')
	{
		data->exp_len += 2;
		data->i++;
	}
	else if (ft_acceptable_char(value[data->i]))
	{
		while (value[data->i] && ft_acceptable_char(value[data->i]))
		{
			data->i++;
			j++;
		}
		tmp = allocation(data, j + 1, sizeof(char), 1);
		dup_from_addr_to_other(tmp, &value[data->i - j], &value[data->i]);
		check_if_exist_len_env(data, tmp);
	}
	else
		data->exp_len++;
}

int	expand_len(t_data *data, char *value)
{
	data->i = 0;
	data->exp_len = 0;
	while (value[data->i])
	{
		if (value[data->i] == '$')
			count_len_of_expand(data, value);
		else
		{
			data->i++;
			data->exp_len++;
		}
	}
	return (data->exp_len);
}
