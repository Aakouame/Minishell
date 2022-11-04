/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_everywhere_helper.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 22:57:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/16 14:13:01 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	old_pwd_alloc(t_data *data)
{
	t_env	*node;
	t_env	*trav;

	trav = data->l_env;
	node = allocation(data, 1, sizeof(t_env), 0);
	node->sec = add_dup(data, "OLDPWD", 0);
	while (trav->next)
		trav = trav->next;
	trav->next = node;
	sort_env(data);
	data->old_pwd_make = 1;
}

void	change_pwd(t_data *data, char *path)
{
	t_env	*pwd;

	pwd = getenv_addr(data, "PWD");
	if (!pwd)
	{
		data->old_pwd_value = add_dup(data, data->pwd_of_mysys, 0);
		data->pwd_of_mysys = add_dup(data, path, 0);
	}
	else
	{
		data->old_pwd_value = add_dup(data, pwd->value, 0);
		if (!ft_strcmp(pwd->value, path))
			return ;
		else
		{
			pwd->value = add_dup(data, path, 0);
			data->pwd_of_mysys = add_dup(data, path, 0);
		}
	}
}

void	change_oldpwd(t_data *data)
{
	t_env	*old;

	old = getenv_addr(data, "OLDPWD");
	if (old)
		old->value = add_dup(data, data->old_pwd_value, 0);
}
