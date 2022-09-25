/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 11:38:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/24 17:04:39 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_nbr(char *arg)
{
  while (*arg)
  {
    if (!ft_isdigit(*arg))
      return (0);
    arg++;
  }
  return (1);
}

void  exit_cmd(t_data *data)
{
  //i will change the exit status later with it's number
  int   i;
  t_cmd *trav;

  i = 1;
  trav = data->v_cmd;
  if (!trav->cmd[i])
  {
    printf("exit\n");
    exit(0);
  }
  else
  {
    if (check_nbr(trav->cmd[i]))
    {
      i++;
      if (!trav->cmd[i])
      {
        printf("exit\n");
        exit(255);
      }
      else
      {
        data->chk_dolla = 1;
        printf("exit\n");
        printf("minishell: exit: too many arguments\n");
      }
    }
    else
    {
      printf("exit\n");
      printf("minishell: exit: %s: too many arguments\n", trav->cmd[i]);
      exit(255);
    }
  }
  //exit(0);
}

//exit only exit with printing exit and exit with 0
//if exit with number as args 1 don't exit and error msg
//if exit with 9348 in one arg should exit but 2 args and more with number and char in second args dont exit and status in mishell 1
//if exit with char exit 255 with a error msg
//exit and redirection open file and boom exit
