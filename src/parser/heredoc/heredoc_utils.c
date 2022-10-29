/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 08:44:51 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 12:23:06 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	heredoc_sig(int c)
{
	printf("\n");
	exit(1);
}

static void	heredoc_alloc(t_data *data, char *dolla, char *ptr)
{
	int		len;
	t_env	*env;

	env = getenv_addr(data, dolla);
	if (env)
	{
		free(dolla);
		dolla = env->value;
	}
	len = 0;
	while (dolla[len])
		ptr[data->j++] = dolla[len++];
}

void	heredoc_dolla_allocate(t_data *data, char *ptr, char *str)
{
	int		len;
	char	*dolla;
	t_env	*trav_env;

	trav_env = data->l_env;
	if (str[data->i] == '$' && ft_acceptable_char(str[data->i + 1]))
	{
		data->i++;
		len = 0;
		while (ft_acceptable_char(str[data->i]))
		{
			data->i++;
			len++;
		}
		dolla = ft_calloc(len + 1, sizeof(char));
		data->i -= len;
		len = 0;
		while (ft_acceptable_char(str[data->i]))
			dolla[len++] = str[data->i++];
		heredoc_alloc(data, dolla, ptr);
	}
}
