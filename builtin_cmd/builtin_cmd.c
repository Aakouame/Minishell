/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 15:54:38 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/25 09:08:47 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//void  if_uppercase_lower_them(char *cmd)
//{
//  //there's alot of prob like pwd "PWd" "Pwd"...
//  if (!ft_strcmp(cmd, ""))
//}

char  *if_upper_lower_them(char *cmd)
{
  int   i;
  char  *ptr;

  i = 0;
  ptr = malloc(sizeof(char) * ft_strlen(cmd) + 1);
  //while (!ft_toupper(cmd[i]) && cmd[i])
  //  i++;
  //if (!cmd[i])
  //  return (cmd);
  //else
  //{
  while (cmd[i])
  {
    if (cmd[i] >= 'A' && cmd[i] <= 'Z')
      ptr[i] = cmd[i] + 32;
    else
      ptr[i] = cmd[i];
    i++;
  }
  ptr[i] = 0;
  //}
  return (ptr);
}

int  check_builtin(char **cmd)
{
  int   i;
  char  **sp;
  //char  b_cmd[] = "cd echo pwd export unset env exit";
  char  *b_cmd;

  b_cmd = "cd export unset exit";
  i = 0;
  sp = ft_split(b_cmd, ' ');
  //no need my shell handle it somehow wtf maybe it uses the system echo and shiit
  //if_uppercase_lower_them(cmd);
  while (sp[i])
  {
    if (!ft_strcmp(sp[i], *cmd))
      return (1);
    i++;
  }
  i = 0;
  //while (!ft_toupper(*cmd[i]) && *cmd[i])
  b_cmd = *cmd;
  while (!(b_cmd[i] >= 'A' && b_cmd[i] <= 'Z') && b_cmd[i])
    i++;
  if (b_cmd[i])
    *cmd = if_upper_lower_them(*cmd);
  b_cmd = "env echo pwd";
  sp = ft_split(b_cmd, ' ');
  i = 0;
  while (sp[i])
  {
    if (!ft_strcmp(sp[i], *cmd))
      return (1);
    i++;
  }

  return (0);
}

void  builtin_cmd(t_data *data, char *cmd)
{
  //printf("im here nigga\n");
  if (!ft_strcmp(cmd, "cd"))
    cd_cmd(data);
  else if (!ft_strcmp(cmd, "echo"))
    echo_cmd(data);
  else if (!ft_strcmp(cmd, "pwd"))
    pwd_cmd(data);
  else if (!ft_strcmp(cmd, "env"))
    env_cmd(data);
  else if (!ft_strcmp(cmd, "export"))
    export_cmd(data);
  else if (!ft_strcmp(cmd, "unset"))
    unset_cmd(data);
  else if (!ft_strcmp(cmd, "exit"))
    exit_cmd(data);
}
//env and echo and pwd
//maybe only normal cmd that should be lowercase if they are uppercase
