/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:22:11 by hkaddour          #+#    #+#             */
/*   Updated: 2022/10/21 15:26:02 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_alloc(void)
{
	printf("Fatal: error in allocation :/\n");
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
	printf("%s\n", msg);
}

void	error_cd(t_data *data, char *msg)
{
	data->chk_dolla = 1;
	printf("%s\n", msg);
}
