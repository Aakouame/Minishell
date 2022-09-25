/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 16:18:49 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/23 16:43:12 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  find_that_element(t_data *data, char *elem)
{
  t_env *trav;
  t_env *trav_prev;

  trav = data->l_env;
  trav_prev = data->l_env;
  while (ft_strcmp(trav->sec, elem) && trav->next)
  {
    trav_prev = trav;
    trav = trav->next;
  }
  if (!ft_strcmp(trav->sec, elem))
  {
    trav_prev->next = trav->next;
    free(trav->sec);
    free(trav->value);
    free(trav);
  }
  else
    return ;
}

void  unset_cmd(t_data *data)
{
  int   i;
  t_cmd *trav_c;

  i = 1;
  trav_c = data->v_cmd;
  if (!trav_c->cmd[1])
    return ;
  while (trav_c->cmd[i])
  {
    find_that_element(data, trav_c->cmd[i]);
    i++;
  }
}
//first i have loop for the args 
//unset only don't do shiit
//index one of the args i will make a func that searches that arg and free it and link the pointers
//and so on and finally sort the env
