/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 03:11:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/11/04 03:12:52 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

void	execute_cd_swap_init(t_data *data, t_env **pwd, t_env **old)
{
	*pwd = getenv_addr(data, "PWD");
	*old = getenv_addr(data, "OLDPWD");
}
