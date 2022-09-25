/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 16:42:42 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/24 11:59:10 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_acceptable_char(int c)
{
  if (c >= 48 && c <= 57)
    return (1);
  else if (c >= 65 && c <= 90)
    return (1);
  else if (c >= 97 && c <= 122)
    return (1);
  else
    return (0);
}

static void  ft_init_tokenizer(t_data *data, char *n_line, int i, t_types typ)
{
  data->typ = typ;
  data->n_line = n_line;
  data->i_line = i;
  data->index += i;
}

static void add_s_quote(t_data *data)
{
  data->i++;
  while (data->beg_line[data->i] != '\'' && data->beg_line[data->i])
    data->node->value[data->j++] = data->beg_line[data->i++];
  if (data->beg_line[data->i] == '\'')
    data->i++;
}

static void add_dolla_helper(t_data *data, int len)
{
  char  *dolla;
  t_env *trav_env;

  trav_env = data->l_env;
  dolla = malloc(sizeof(char) * len + 1);
  data->i -= len;
  len = 0;
  while (ft_acceptable_char(data->beg_line[data->i]))
    dolla[len++] = data->beg_line[data->i++];
  dolla[len] = 0;
  while (ft_strncmp(trav_env->sec, dolla, len) && trav_env->next != NULL)
    trav_env = trav_env->next;
  if (!ft_strncmp(trav_env->sec, dolla, len))
  {
    free(dolla);
    dolla = ft_strdup(trav_env->value);
  }
  else
  {
    free(dolla);
    dolla = ft_strdup("");
  }
  len = 0;
  while (dolla[len])
    data->node->value[data->j++] = dolla[len++];
}

static  void  add_dolla(t_data *data)
{
  int   len;

  if (data->beg_line[data->i] == '$' && ft_acceptable_char(data->beg_line[data->i + 1]))
  {
    data->i++;
    len = 0;
    while (ft_acceptable_char(data->beg_line[data->i]))
    {
      data->i++;
      len++;
    }
    add_dolla_helper(data, len);
  }
  else if (data->beg_line[data->i] == '$' && !ft_acceptable_char(data->beg_line[data->i + 1]))
  {
    data->node->value[data->j++] = data->beg_line[data->i++];
    while (data->beg_line[data->i] && data->beg_line[data->i] != '$' && !ft_acceptable_char(data->beg_line[data->i + 1]))
      data->node->value[data->j++] = data->beg_line[data->i++];
  }
}

static void add_dolla_begin(t_data *data)
{
  int keep;

  if (data->beg_line[data->i + 1] == ' ' || data->beg_line[data->i + 1] == '\"' \
      || data->beg_line[data->i + 1] == '\'')
    data->node->value[data->j++] = data->beg_line[data->i++];
  else if (data->beg_line[data->i + 1] == 0)
    data->node->value[data->j++] = data->beg_line[data->i++];
  else if (data->beg_line[data->i + 1] == '?')
  {
    keep = data->i + 1;
    while (data->i <= keep)
      data->node->value[data->j++] = data->beg_line[data->i++];
  }
  else if (data->beg_line[data->i + 1] == '$')
  {
    while (data->beg_line[data->i] == '$')
    {
      if (data->beg_line[data->i + 1] == '$')
        data->i += 2;
      else
        break ;
    }
  }
}

static void add_d_quote(t_data *data)
{
  data->i++;
  while (data->beg_line[data->i] != '$' && data->beg_line[data->i] != '\"' && data->beg_line[data->i])
    data->node->value[data->j++] = data->beg_line[data->i++];
  while (data->beg_line[data->i] == '$')
  {
    add_dolla_begin(data);
    add_dolla(data);
    while (data->beg_line[data->i] != '$' && data->beg_line[data->i] != '\"' && data->beg_line[data->i])
      data->node->value[data->j++] = data->beg_line[data->i++];
  }
  if (data->beg_line[data->i] == '\"' || data->beg_line[data->i] == '\'')
  {
    if (data->beg_line[data->i] == '\'')
      data->node->value[data->j++] = data->beg_line[data->i++];
    else if (data->beg_line[data->i] == '\"')
      data->i++;
  }
}

static void add_node_helper(t_data *data, int check)
{
  if (check == 0)
  {
    if (data->beg_line[data->i] == '\'')
      add_s_quote(data);
    if (data->beg_line[data->i] == '\"')
      add_d_quote(data);
    while (data->beg_line[data->i] == '$')
    {
      add_dolla_begin(data);
      add_dolla(data);
    }
  }
  if (check == 1)
  {
    if (data->check == 0)
    {
      data->trav = data->t_token;
      while (data->trav->next)
        data->trav = data->trav->next;
      data->trav->next = data->node;
    }
    if (data->check == 1)
      data->check--;
  }
}


static void  add_node(t_data *data, t_types typ)
{
  t_env *trav_env;

  data->i = 0;
  data->j = 0;
  trav_env = data->l_env;
  data->node = (t_token *) malloc(sizeof(t_token));
  if (data->check == 1)
    data->t_token = data->node;
  data->node->type = typ;
  //i gotta count the lenght for this node
  data->node->value = malloc(sizeof(char) * 100);
  while (&data->beg_line[data->i] != &data->n_line[0] && data->beg_line[data->i])
  {
    add_node_helper(data, 0);
    if (&data->beg_line[data->i] == &data->n_line[0])
      break ;
    if (data->beg_line[data->i] != '\"' && data->beg_line[data->i] != '\'' && data->beg_line[data->i])
      data->node->value[data->j++] = data->beg_line[data->i++];
  }
  data->beg_line = &data->beg_line[data->i];
  data->node->value[data->j] = 0;
  data->node->next = NULL;
  add_node_helper(data, 1);
}

int is_word(t_data *data, char *beg_line)
{
  char  sp[] = "<|\">'$ ";

  data->i = 0;
  while (beg_line[data->i])
  {
    data->j = 0;
    while (sp[data->j])
    {
      if (beg_line[data->i] == sp[data->j])
        break;
      data->j++;
    }
    if (beg_line[data->i] == sp[data->j])
      break ;
    data->i++;
  }
  if (data->i == 0)
    return (0);
  ft_init_tokenizer(data, &beg_line[data->i], data->i, WRD);
  return (1);
}

int is_space(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != ' ')
    return (0);
  while (n_line[i] == ' ')
    i++;
  ft_init_tokenizer(data, &n_line[i], i, W_SPACE);
  return (1);
}

int is_pipe(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != '|')
    return (0);
  while (n_line[i] == '|')
    i++;
  ft_init_tokenizer(data, &n_line[i], i, PIPE);
  return (1);
}

int is_o_redirection(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != '<')
    return (0);
  while (n_line[i] == '<')
  {
    if (n_line[1] != '<')
    {
      i++;
      ft_init_tokenizer(data, &n_line[i], i, I_TRNC);
      return (1);
    }
    i++;
  }
  if (n_line[i] != '<')
    ft_init_tokenizer(data, &n_line[i], i, I_APEND);
  return (1);
}

int is_i_redirection(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != '>')
    return (0);
  while (n_line[i] == '>')
  {
    if (n_line[1] != '>')
    {
      i++;
      ft_init_tokenizer(data, &n_line[i], i, O_TRNC);
      return (1);
    }
    i++;
  }
  if (n_line[i] != '>')
    ft_init_tokenizer(data, &n_line[i], i, O_APEND);
  return (1);
}

static void is_quote_helper(t_data *data, int c, char *n_line)
{
  data->i++;
  while (n_line[data->i])
  {
    if (n_line[data->i] == c)
    {
      data->i++;
      while (n_line[data->i])
      {
        if (n_line[data->i] == ' ' || n_line[data->i] == '|' ||\
            n_line[data->i] == '>' || n_line[data->i] == '<')
        {
          ft_init_tokenizer(data, &n_line[data->i], data->i, S_QUOT);
          return ;
        }
        data->i++;
        if (n_line[data->i] == c)
          break ;
      }
    }
    data->i++;
  }
  ft_init_tokenizer(data, &n_line[data->i], data->i, D_QUOT);
}

int is_s_quote(t_data *data, char *n_line)
{
  data->i = 0;
  if (n_line[data->i] != '\'')
    return (0);
  else if (n_line[data->i] == '\'')
    is_quote_helper(data, '\'', n_line);
  return (1);
}

int is_d_quote(t_data *data, char *n_line)
{
  data->i = 0;
  if (n_line[data->i] != '\"')
    return (0);
  else if (n_line[data->i] == '\"')
    is_quote_helper(data, '\"', n_line);
  return (1);
}

int is_dolla(t_data *data, char *n_line)
{
  int i;

  i = 0;
  if (n_line[i] != '$')
    return (0);
  if (n_line[i] == '$')
  {
    i++;
    while (n_line[i] != ' ' && n_line[i] != '|' && n_line[i] != '>' \
        && n_line[i] != '<' && n_line[i])
    {
      if (n_line[i] == '$')
      {
        i++;
        break ;
      }
      i++;
    }
  }
  ft_init_tokenizer(data, &n_line[i], i, DOLLA);
  return (1);
}

void  tokenizer(t_data *data)
{
  //here maybe i should check all whitespace also in is_space
  if (data->line[0] == ' ')
    data->beg_line = ft_strchr(data->line, ' ');
  else
    data->beg_line = data->line;
  data->index = 0;
  data->check = 1;
  ft_init_tokenizer(data, data->beg_line, 0, 0);
  while (data->line[data->index])
  {
    if (is_word(data, data->n_line) || is_space(data, data->n_line) || \
        is_pipe(data, data->n_line) || is_o_redirection(data, data->n_line) || \
        is_i_redirection(data, data->n_line) || is_s_quote(data, data->n_line) || \
        is_d_quote(data, data->n_line) || is_dolla(data, data->n_line))
      add_node(data, data->typ);
  }
  //here to write the arg that i entred in the nodes
  t_token *trav;

  trav = data->t_token;
  while (trav)
  {
    printf("| %d |\n", trav->type);
    printf("| %s |\n", trav->value);
    printf("\n");
    trav = trav->next;
  }
}
