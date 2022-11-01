/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:29:55 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/17 10:23:19 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	color_desicision(t_data *data, char **clr)
{
	if (data->chk_dolla == 0)
		*clr = CLR1;
	else
		*clr = CLR1ERR;
}

static void	get_me_env_addresses(t_data *data, char **path_h, char **path_pw)
{
	t_env	*pwd;
	t_env	*home;

	pwd = getenv_addr(data, "PWD");
	if (pwd)
		*path_pw = pwd->value;
	else
		*path_pw = data->pwd_of_mysys;
	home = getenv_addr(data, "HOME");
	if (home)
		*path_h = home->value;
	else
		*path_h = getenv("HOME");
}

static void	home_path_and_dir_path(t_data *data, char *clr1, \
		char *home, char *pwd)
{
	int		len;
	int		i;

	i = 0;
	if (ft_strlen(pwd) > ft_strlen(home))
	{
		len = ft_strlen(home);
		data->prompt = allocation(data, len + 3, sizeof(char), 1);
		data->prompt[i++] = '~';
		while (pwd[len])
			data->prompt[i++] = pwd[len++];
		data->prompt = add_join(data, clr1, add_join(data, \
					data->prompt, CLR2, 1), 1);
	}
	else if (ft_strlen(pwd) == ft_strlen(home))
		data->prompt = add_join(data, clr1, add_join(data, \
					"~", CLR2, 1), 1);
}

void	prompt_changer(t_data *data)
{
	char	*path_h;
	char	*path_pw;
	char	*clr1;

	color_desicision(data, &clr1);
	get_me_env_addresses(data, &path_h, &path_pw);
	if (!path_h)
	{
		data->prompt = add_join(data, clr1, add_join(data, \
					path_pw, CLR2, 1), 1);
		return ;
	}
	if (!ft_strncmp(path_pw, path_h, ft_strlen(path_h)))
		home_path_and_dir_path(data, clr1, path_h, path_pw);
	else
		data->prompt = add_join(data, clr1, add_join(data, \
					path_pw, CLR2, 1), 1);
}
