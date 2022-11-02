/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 10:24:53 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/02 03:16:50 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

int	check_if_llong_helper(char *nbr, int *index, char **ll)
{
	int	j;
	int	i;

	i = *(index);
	if (nbr[i] < '9')
		return (0);
	i++;
	j = i;
	while (nbr[i])
	{
		if (nbr[i] < (*ll)[j])
			return (0);
		else if (nbr[i++] > (*ll)[j++])
			return (1);
	}
	return (0);
}
