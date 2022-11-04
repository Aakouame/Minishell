/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 05:11:04 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 00:08:11 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	process_kill(t_data *data)
{
	printf("exit\n");
	free_data_die_process(data);
	exit(0);
}

void	*allocation(t_data *data, size_t count, size_t size, int chk)
{
	void		*ptr;

	ptr = ft_calloc(count, size);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_dup(t_data *data, char *s, int chk)
{
	char	*ptr;

	ptr = ft_strdup(s);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}

char	*add_join(t_data *data, char *s, char *s1, int chk)
{
	char	*ptr;

	ptr = ft_strjoin(s, s1);
	if (chk)
		add_node_p_running(data, ptr);
	else
		add_node_p_die(data, ptr);
	return (ptr);
}
