/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/29 11:15:35 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  split_cmd(t_data *data)
{
  int     i;
  int     j;
  t_token *trav;

  i = 0;
  j = 0;
  trav = data->t_token;
  while (trav)
  {
    if (trav->type == PIPE)
      i++;
    trav = trav->next;
  }
  data->split_cmd = malloc(sizeof(char *) * i + 2);
  trav = data->t_token;
  i = 0;
  while (trav)
  {
    while (trav->type != PIPE && trav)
    {
      data->split_cmd[j] = ft_strdup(trav->value);
      trav = trav->next;
    }
    trav = trav->next;
    j++;
  }
  data->split_cmd[j] = NULL;

}

void  parser(t_data *data)
{
  split_cmd(data);
  int i;

  i = 0;
  while (data->split_cmd[i])
  {
    printf("%s\n", data->split_cmd[i]);
    i++;
  }
}
