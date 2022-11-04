/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akouame <akouame@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:22:11 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/03 20:06:02 by akouame          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_alloc(void)
{
	ft_putstr_fd("Fatal: error in allocation :/\n", 2);
	exit(30);
}

void	error_fork(t_data *data)
{
	data->chk_dolla = 1;
	ft_putstr_fd("minishell: fork: Resource temporarily unavailable\n", 2);
}

void	error_pipe(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	stdanred_error("\n", msg, 0);
}

void	error_cd(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	ft_putstr_fd(msg, 2);
}

void	stdanred_error(char *msg, char *arg, int chk)
{
	if (chk)
		ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(msg, 2);
}
