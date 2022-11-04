/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 23:17:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/17 10:31:21 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static char	*get_sec(t_data *data, char *str)
{
	int		eqal;
	char	*ptr;

	eqal = ft_strcspn(str, "=");
	ptr = allocation(data, eqal + 1, sizeof(char), 1);
	ft_strlcpy(ptr, str, eqal + 1);
	return (ptr);
}

static void	allocate_all_nodes(t_data *data)
{
	int		i;
	t_env	*head;
	t_env	*next;

	i = 1;
	head = allocation(data, 1, sizeof(t_env), 0);
	data->l_env = head;
	while (data->env[i])
	{
		if (!ft_strcmp(get_sec(data, data->env[i]), "OLDPWD"))
			i++;
		else
		{
			next = allocation(data, 1, sizeof(t_env), 0);
			head->next = next;
			head = head->next;
			i++;
		}
	}
}

static void	env_shlvl(t_data *data)
{
	t_env	*env;
	t_env	*shlvl;

	env = getenv_addr(data, "SHLVL");
	if (env)
		env_shlvl_helper(data, env);
	else
	{
		shlvl = allocation(data, 1, sizeof(t_env), 0);
		shlvl->sec = add_dup(data, "SHLVL", 0);
		shlvl->value = add_dup(data, "1", 0);
		if (data->l_env)
		{
			env = data->l_env;
			while (env->next)
				env = env->next;
			env->next = shlvl;
			sort_env(data);
		}
		else
			data->l_env = shlvl;
	}
}

static void	fill_nodes_env(t_data *data, t_env **env, int i)
{
	int	j;
	int	k;

	j = ft_strcspn(data->env[i], "=");
	env[0]->sec = allocation(data, j + 1, sizeof(char), 0);
	j = 0;
	while (data->env[i][j] && data->env[i][j] != '=')
	{
		env[0]->sec[j] = data->env[i][j];
		j++;
	}
	j++;
	env[0]->value = allocation(data, (ft_strlen(data->env[i]) + 1) - j, \
			sizeof(char), 0);
	k = 0;
	while (data->env[i][j] && data->env[i][j] != 0)
		env[0]->value[k++] = data->env[i][j++];
	env[0] = env[0]->next;
}

void	get_env(t_data *data)
{
	int		i;
	t_env	*env;

	allocate_all_nodes(data);
	i = 0;
	env = data->l_env;
	while (data->env[i])
	{
		if (ft_strcmp(get_sec(data, data->env[i]), "OLDPWD"))
			fill_nodes_env(data, &env, i);
		i++;
	}
	env_shlvl(data);
}
