/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 10:32:56 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/24 19:13:45 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//static int  len_cmd(t_token *trav)
//{
//  int i;
//  int j;
//
//  i = 0;
//  while (trav)
//  {
//    if (trav->type == PIPE)
//      break ;
//    j = 0;
//    while (trav->value[j])
//    {
//      j++;
//      i++;
//    }
//    trav = trav->next;
//  }
//  return (i);
//}
//
//static void  split_cmd(t_data *data)
//{
//  int     i;
//  int     j;
//  int     k;
//  //int     check;
//  t_token *trav;
//  t_token *hold;
//
//  i = 0;
//  j = 0;
//  //check = 1;
//  trav = data->t_token;
//  hold = data->t_token;
//  while (trav)
//  {
//    if (trav->type == PIPE && &trav->type != &hold->type)
//      i++;
//    trav = trav->next;
//  }
//  data->split_cmd = malloc(sizeof(char *) * i + 2);
//  trav = data->t_token;
//  while (trav)
//  {
//    i = 0;
//    data->split_cmd[j] = malloc(sizeof(char) * len_cmd(trav));
//    while (trav->type != PIPE)
//    {
//      k = 0;
//      while (trav->value[k])
//        data->split_cmd[j][i++] = trav->value[k++];
//      trav = trav->next;
//      if (!trav)
//        break ;
//    }
//    if (trav)
//    {
//      if (trav->type == PIPE && &trav->type == &hold->type)
//      {
//        //check--;
//        trav = trav->next;
//        continue ;
//      }
//    }
//    data->split_cmd[j][i] = 0;
//    j++;
//    if (!trav)
//      break ;
//    trav = trav->next;
//  }
//  data->split_cmd[j] = NULL;
//}
//
//static char *str_put(char *arg, int len)
//{
//  int   i;
//  char  *ptr;
//
//  i = 0;
//  ptr = malloc(sizeof(char) * len + 1);
//  while (&arg[i] != &arg[len])
//  {
//    ptr[i] = arg[i];
//    i++;
//  }
//  ptr[i] = 0;
//  return (ptr);
//}

//static void  allocate_parsing(t_data *data)
//{
//  int     i;
//  int     j;
//  int     cmd_len;
//  int     file_len;
//  //char    *arg;
//  t_types typ;
//
//  i = 0;
//  j = 0;
//  cmd_len = 0;
//  file_len = 0;
//  while (data->split_cmd[i])
//  {
//    while (data->split_cmd[i][j])
//    {
//      if (data->split_cmd[i][j] != '>')
//      {
//        //arg = str_put(data->split_cmd[i], j);
//        j++;
//        if (data->split_cmd[i][j] == '>')
//        {
//          typ = O_APEND;
//          j += 2;
//          while (data->split_cmd[i][j] != ' ')
//          {
//            file_len++;
//            j++;
//          }
//          //if (data->split_cmd[i][j] == ' ')
//        }
//        else if (data->split_cmd[i][j] != '>')
//        {
//          typ = O_TRNC;
//
//        }
//      }
//      if (data->split_cmd[i][j] == '<')
//      {
//        j++;
//        if (data->split_cmd[i][j] == '<')
//        {
//
//        }
//      }
//      cmd_len++;
//      j++;
//    }
//    i++;
//  }
//}

static int  count_cmd(t_data *data)
{
  t_token *trav;
  int     i;
  int     j;

  i = 0;
  j = 0;
  trav = data->t_token;
  while (trav)
  {
    //maybe here i will face a problem if | was at first of the cmd
    if (trav->type == PIPE && j != 0 && trav->next)
      i++;
    trav = trav->next;
    j++;
  }
  return (i);
}

static void allocate_cmd_node(t_data *data)
{
  int   i;
  int   len;
  t_cmd *head;
  t_cmd *node;

  i = 1;
  len = count_cmd(data) + 1;
  head = malloc(sizeof(t_cmd));
  head->cmd = NULL;
  head->f_in = 0;
  head->f_out = 1;
  head->redirect = NULL;
  head->next = NULL;
  data->v_cmd = head;
  while (i < len)
  {
    node = malloc(sizeof(t_cmd));
    node->cmd = NULL;
    node->f_in = 0;
    node->f_out = 1;
    node->redirect = NULL;
    node->next = NULL;
    head->next = node;
    head = node;
    i++;
  }
}

static void allocate_red_node(t_data *data, int red_len)
{
  int i;
  t_red *head;
  t_red *node;

  i = 1;
  //here check if there's redirection in the cmd node
  if (red_len != 0)
  {
    head = malloc(sizeof(t_red));
    head->typ = 0;
    head->file = 0;
    head->determiner = 0;
    head->next = 0;
    data->trav_cmd->redirect = head;
  }
  while (i < red_len)
  {
    node = malloc(sizeof(t_red));
    node->typ = 0;
    node->file = 0;
    node->determiner = 0;
    node->next = 0;
    head->next = node;
    head = node;
    i++;
  }
}

static void get_cmd_parsing(t_data *data)
{
  t_token *trav;
  int     len;
  int     i;
  int     j;
  int     chk;

  j = 0;
  len = 0;
  //trav = data->t_token;
  trav = data->trav;
  while (data->trav)
  {
    if (data->trav->type == WRD || data->trav->type == D_QUOT \
        || data->trav->type == S_QUOT || data->trav->type == DOLLA)
    {
      //len += ft_strlen(data->trav->value);
      //here count len of big ptr to allocate the double array
      len++;
      data->trav = data->trav->next;
    }
    else if (data->trav->type == W_SPACE)
      data->trav = data->trav->next;
    else if (data->trav->type == O_TRNC || data->trav->type == O_APEND \
        || data->trav->type == I_TRNC || data->trav->type == I_APEND)
    {
      //data->trav = data->trav->next;
      if (data->trav->next->type == W_SPACE)
        data->trav = data->trav->next->next->next;
      else
        data->trav = data->trav->next->next;
      j++;
    }
    else if (data->trav->type == PIPE)
      break ;
  }
  //data->trav = trav;
  //trav = data->t_token;
  data->trav_cmd->cmd = malloc(sizeof(char *) * len + 1);
  allocate_red_node(data, j);
  t_red *trav_red;
  trav_red = data->trav_cmd->redirect;
  i = 0;
  chk = 0;
  //len = 0;
  while (trav)
  {
    if (trav->type == WRD || trav->type == D_QUOT \
        || trav->type == S_QUOT || trav->type == DOLLA)
    {
      //len = ft_strlen(trav->value);
      data->trav_cmd->cmd[i++] = ft_strdup(trav->value);
      trav = trav->next;
    }
    else if (trav->type == W_SPACE)
      trav = trav->next;
    //else if (trav->type != WRD && trav->type != W_SPACE && trav->type != PIPE && trav)
    else if (trav->type == O_TRNC || trav->type == O_APEND \
        || trav->type == I_TRNC || trav->type == I_APEND)
    {
      //trav = trav->next;
      if (trav->next->type == W_SPACE)
      {
        trav_red->typ = trav->type;
        if (trav->type != I_APEND)
          trav_red->file = ft_strdup(trav->next->next->value);
        else
        {
          trav_red->determiner = ft_strdup(trav->next->next->value);
          if (chk != 0)
            close(data->hrdoc_fd[0]);
          heredoc_implement(data, trav_red->determiner);
          if (data->chk_hrdoc_exit == 1)
            return ;
          chk = 1;
        }
        trav = trav->next->next->next;
      }
      else
      {
        trav_red->typ = trav->type;
        if (trav->type != I_APEND)
          trav_red->file = ft_strdup(trav->next->value);
        else
        {
          trav_red->determiner = ft_strdup(trav->next->value);
          if (chk != 0)
            close(data->hrdoc_fd[0]);
          heredoc_implement(data, trav_red->determiner);
          if (data->chk_hrdoc_exit == 1)
            return ;
          chk = 1;
        }
        trav = trav->next->next;
      }
      trav_red = trav_red->next;
    }
    else if (trav->type == PIPE)
      break ;
  }
  data->trav_cmd->cmd[i] = 0;
  data->trav_cmd = data->trav_cmd->next;
}

void  parser(t_data *data)
{
  //t_cmd *head;
  //maybe here i will loop in len of pipe + 1
  //head = malloc(sizeof(t_cmd));
  //count_cmd(data);
  //t_token *trav;

  //trav = data->t_token;
  allocate_cmd_node(data);
	data->chk_hrdoc_exit = 0;
  data->trav_cmd = data->v_cmd;
  data->trav = data->t_token;
  while (data->trav)
  {
    get_cmd_parsing(data);
    if (data->chk_hrdoc_exit == 1)
      return ;
    if (!data->trav)
      break ;
    //here i should see the next too "ls | cool |"
    else if (data->trav->type == PIPE)
      data->trav = data->trav->next;
  }
  //printf("**\n%d\n**", data->du.ok);
	//printf("&&%d\n", data->nm);
  //printf("\n%s\n", data->ch);



  //this one for printing the parsing cmd
  //t_cmd *c_trav;
  //c_trav = data->v_cmd;
  //while (c_trav)
  //{
  //**int i;
  //**t_cmd *trav;

  //**trav = data->v_cmd;
  //**while (trav)
  //**{
  //**  i = 0;
  //**  printf("CMD:\n");
  //**  while (trav->cmd[i])
  //**    printf("    %s\n", trav->cmd[i++]);
  //**  printf("Redirection:\n");
  //**  while (trav->redirect)
  //**  {
  //**    printf("    %d\n", trav->redirect->typ);
  //**    printf("    %s\n", trav->redirect->file);
  //**    printf("    %s\n", trav->redirect->determiner);
  //**    //printf("\n|||redirection|||\n");
  //**    trav->redirect = trav->redirect->next;
  //**  }
  //**  printf("\n*next cmd*\n");
  //**  trav = trav->next;
  //**}
  //printf("%d\n", data->chk_q_hrdoc);
  //}

//the idea is to loop for the tokenizer and break in PIPE then allocate the first node and start after the PIPE and like that goes to allocate everything 








  //split_cmd(data);
  //allocate_parsing(data);
  //this fucntion i should allocate the cmd with the file and in and out file
  //int i;

  //i = 0;
  //while (data->split_cmd[i])
  //{
  //  printf("%s\n", data->split_cmd[i]);
  //  i++;
  //}
}
