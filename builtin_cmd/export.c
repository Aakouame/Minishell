/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 13:52:18 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/25 14:19:38 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strcspn(const char *s, const char *reject)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		while (reject[j])
		{
			if (s[i] == reject[j])
				return (i);
			j++;
		}
		i++;
	}
	return (i);
}

int len_of_args(char **cmd)
{
  int i;

  i = 0;
  while (cmd[i])
    i++;
  return (i);
}

void  print_env_of_export(t_env *env)
{
  while (env)
  {
    if (!env->value)
      printf("declare -x %s\n", env->sec);
    else
      printf("declare -x %s=\"%s\"\n", env->sec, env->value);
    env = env->next;
  }
}

t_env *alloc_node_of_export(int len)
{
  int   i;
  t_env *head;
  t_env *node;
  t_env *tmp;

  i = 1;
  head = node_allocate();
  tmp = head;
  while (i < len)
  {
    node = node_allocate();
    head->next = node;
    head = node;
    i++;
  }
  return (tmp);
}

int check_if_equal_or_wrd(char *cmd)
{
  int i;

  i = 0;
  while (cmd[i])
  {
    if (cmd[i] == '=')
      return (1);
    i++;
  }
  return (0);
}

int dup_opt_wrd(t_data *data, t_env *env, char *cmd)
{
  t_env *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, cmd) && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, cmd))
    return (0);
  else
    env->sec = ft_strdup(cmd);
  return (1);
}

int check_existence(t_data *data, char *cmd, int hold, t_env *env)
{
  int   i;
  char  *chk;
  t_env *trav;
  char  *n_cmd;

  i = 0;
  trav = data->l_env;
  chk = malloc(sizeof(char) * hold + 1);
  while (i < hold)
  {
    chk[i] = cmd[i];
    i++;
  }
  chk[i] = 0;
  //take_off_the_equalsign(hold,);
  //here problem of new node that i add are empty 0 and strcmp doesnt return shiit i have to fix it 
  //while (ft_strcmp(trav->sec, chk) && trav->next->sec && trav->next)
  while (ft_strcmp(trav->sec, chk) && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, chk))
  {
    //n_cmd = &cmd[++hold];
    if (data->chk_export_plus == 1)
    {
      hold +=2;
      n_cmd = &cmd[hold];
      trav->value = ft_strjoin(trav->value, n_cmd);
    }
    else
    {
      n_cmd = &cmd[++hold];
      trav->value = ft_strdup(n_cmd);
    }
    //if (!ft_strcmp(trav->value, &cmd[++hold]))
    //if (trav->value)
    //{
    //  if (!ft_strcmp(trav->value, n_cmd))
    //    return (1);
    //}
    //if (!trav->value && ft_strcmp(trav->value, n_cmd))
    //{
    //  trav->value = ft_strdup(n_cmd);
    //  //trav->value = ft_strdup(&cmd[++hold]);
    //  //env->value = ft_strdup(&cmd[++hold]);
    //}
    return (1);
  }
  return (0);
}

int dup_opt_equal(t_data *data, t_env *env, char *cmd)
{
  int   i;
  int   hold;

  i = 0;
  //hold = &cmd[ft_strcspn(cmd, "=")];
  if (data->chk_export_plus == 1)
    hold = ft_strcspn(cmd, "+");
  else
    hold = ft_strcspn(cmd, "=");
  if (check_existence(data, cmd, hold, env) == 1)
    return (0);

  //while (&cmd[i] != &hold[0])
  env->sec = malloc(sizeof(char) * hold + 1);
  while (i < hold)
  {
    env->sec[i] = cmd[i];
    i++;
  }
  env->sec[i] = 0;
  if (cmd[hold] == '+')
    hold += 2;
  else
    hold++;
  i = 0;
  //env->value = malloc(sizeof(char) * ft_strlen(&cmd[hold]) + 1);
  env->value = malloc(sizeof(char) * ft_strlen(&cmd[hold]) + 1);
  //if (cmd[hold] == '+')
  //  hold++;
  while (cmd[hold])
    env->value[i++] = cmd[hold++];
  env->value[i] = 0;
  return (1);
}

char  *before_equal(char *cmd)
{
  int   i;
  int   hold;
  char  *chk;

  i = 0;
  if (!check_if_equal_or_wrd(cmd))
    return (cmd);
  else
  {
    hold = ft_strcspn(cmd, "=");
    if (cmd[hold - 1] == '+')
      hold--;
    chk = malloc(sizeof(char) * hold + 1);
    while (i < hold)
    {
      chk[i] = cmd[i];
      i++;
    }
    chk[i] = 0;
  }
  return (chk);
}

int if_exist_or_not(t_data *data, char *cmd)
{
  t_env  *trav;

  trav = data->l_env;
  while (ft_strcmp(trav->sec, before_equal(cmd)) && trav->next)
    trav = trav->next;
  if (!ft_strcmp(trav->sec, before_equal(cmd)))
    return (0);
  return (1);
}

int check_export_error(t_data *data, char *cmd)
{
  //while (*cmd == '=' && *cmd)
  //  cmd++;
  //if ()
  int hold;
  int i;

  i = 0;
  if (cmd[i] == '=' || cmd[i] == '+')
    return (1);
  while (cmd[i] != '=' && cmd[i])
    i++;
  if (cmd[i] == 0)
  {
    i = 0;
    while (cmd[i] != '+' && cmd[i])
      i++;
    if (cmd[i] == 0)
      return (0);
    else
      return (1);
  }
    //return (0);
  hold = ft_strcspn(cmd, "=");
  i = 0;
  if (cmd[hold - 1] == '+')
    hold--;
  while (i < hold)
  {
    if (cmd[i] == '+')
      return (1);
    i++;
  }
  if (cmd[hold] == '+')
    data->chk_export_plus = 1;
  return (0);
}

void  sort_env(t_data *data)
{
  
}

void  export_cmd(t_data *data)
{
  int   i;
  //int   len;
  int   chk;
  t_env *trav_e;
  t_env *head;
  //t_env *hold;
  t_cmd *trav_c;

  i = 1;
  head = 0;
  trav_e = data->l_env;
  trav_c = data->v_cmd;
  //len = len_of_args(trav_c->cmd) - 1;
  if (!trav_c->cmd[i])
    print_env_of_export(trav_e);
  else
  {
    while (trav_e->next)
      trav_e = trav_e->next;
    while (trav_c->cmd[i])
    {
      data->chk_export_plus = 0;
      if (!check_export_error(data, trav_c->cmd[i]))
      {
        chk = if_exist_or_not(data, trav_c->cmd[i]);
        if (chk == 1)
          head = node_allocate();
        if (!check_if_equal_or_wrd(trav_c->cmd[i]))
          chk = dup_opt_wrd(data, head, trav_c->cmd[i]);
        else
          chk = dup_opt_equal(data, head, trav_c->cmd[i]);
        if (chk == 1)
        {
          trav_e->next = head;
          trav_e = trav_e->next;
        }
      }
      else
      {
        data->chk_dolla = 1;
        printf("minishell: export: '%s': not a valid identifier\n", trav_c->cmd[i]);
      }
      i++;
    }
    //here sort them
    sort_env(data);
    //trav_e->next = head;
  }
  //here func should sort the env
  //sort_env();
}
//pseudo of how to make export env
//first enter the args that have = on them to env
//then the one that don't have = put them in a double array
//finally make a double array and put the env on it and add the args that don't have =
//then sort them 

//void  export_cmd(t_data *data)
//{
//  int   i;
//  int   len;
//  int   chk;
//  t_env *trav_e;
//  t_env *head;
//  t_env *hold;
//  t_cmd *trav_c;
//
//  i = 1;
//  head = 0;
//  trav_e = data->l_env;
//  trav_c = data->v_cmd;
//  len = len_of_args(trav_c->cmd) - 1;
//  if (!len)
//    print_env_of_export(trav_e);
//  else
//  {
//    if_exist_or_not(data, &trav_c->cmd[i], &len);
//    while (trav_e->next)
//      trav_e = trav_e->next;
//    if (len > 0)
//    {
//      head = alloc_node_of_export(len);
//      hold = head;
//    }
//    //trav_e = trav_e->next;
//    //while (trav_c->cmd[i] && trav_e)
//    while (trav_c->cmd[i])
//    {
//      if (!check_if_equal_or_wrd(trav_c->cmd[i]))
//        chk = dup_opt_wrd(data, hold, trav_c->cmd[i]);
//      else
//        chk = dup_opt_equal(data, hold, trav_c->cmd[i]);
//      i++;
//      if (chk == 1)
//        hold = hold->next;
//        //trav_e = trav_e->next;
//    }
//    trav_e->next = head;
//  }
//  //here func should sort the env
//  //sort_env();
//}

//we have two option export the cmd and options are wrd || wrd=wrd
//wrd only just enter it with null in the value
//wrd=wrd get the sec and value by spliting it with =
//but first have to get the end of env to start entering args
//i have to loop for export args and = split and wrd not
//alloc a node and enter args and go to next one 
//lastly but not least sort the env uppercasse then lowercase
//export only should print the env
//EXPORT if is big dirha sghira
