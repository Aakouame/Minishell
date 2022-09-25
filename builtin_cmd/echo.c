/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 17:15:12 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/23 13:47:37 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_nline_option(char **cmd)
{
  int i;
  int j;

  i = 1;
  while (!ft_strncmp(cmd[i], "-n", 2))
  {
    j = 2;
    while (cmd[i][j])
    {
      if (cmd[i][j] != 'n')
        return (i);
      j++;
    }
    i++;
  }
  return (i);
}

void  echo_cmd(t_data *data)
{
  //check if echo -n 
  //and then echo args normal use ft_putstr_fd
  int   i;
  int   chk;
  t_cmd *trav;

  trav = data->v_cmd;
  if (trav->cmd[1])
    chk = check_nline_option(trav->cmd);
  else
  {
    ft_putchar_fd('\n', trav->f_out);
    return ;
  }
  i = chk;
  data->chk_dolla = 0;
  //above if 0 all newline if bigger than 0 no newline
  while (trav->cmd[i])
  {
    ft_putstr_fd(trav->cmd[i], trav->f_out);
    ft_putchar_fd(' ', trav->f_out);
    //newline
    //if (chk == 1)
    //  ft_putstr_fd(trav->cmd[i], trav->f_out);
    //else if (chk < 1)
    //  ft_putstr_fd(trav->cmd[i], trav->f_out);
    i++;
  }
  if (chk == 1)
    ft_putchar_fd('\n', trav->f_out);
}
