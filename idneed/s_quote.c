/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_quote.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/21 13:46:15 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/23 10:37:00 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void  token_s_quote(t_data *data)
{
  int   i;
  int   j;
  int   len;
  int   keep;
  char  *ptr;
  char  *dolla;
  t_env *trav;

  i = 0;
  j = 0;
  trav = data->l_env;
  ptr = malloc(sizeof(char) * 100);
  while (data->line[i])
  {
    if (data->line[i] == '\'')
    {
      i++;
      while (data->line[i] != '\'' && data->line[i])
      {
        ptr[j] = data->line[i];
        i++;
        j++;
      }
      if (data->line[i] == '\'')
        i++;
    }
    if (data->line[i] == '\"')
    {
      i++;
      //while (data->line[i] != '$' && data->line[i] != '\'' && data->line[i] != '\"' && data->line[i])
      while (data->line[i] != '$' && data->line[i] != '\"' && data->line[i])
      {
        ptr[j] = data->line[i];
        i++;
        j++;
      }
      while (data->line[i] == '$')
      {
        //****
        if (data->line[i + 1] == ' ' || data->line[i + 1] == '\"' \
            || data->line[i + 1] == '\'')
        {
          ptr[j] = data->line[i];
          i++;
          j++;
          //break ;
        }
        else if (data->line[i + 1] == 0)
        {
          ptr[j] = data->line[i];
          i++;
          j++;
          //break ;
        }
        else if (data->line[i + 1] == '?')
        {
          keep = i + 1;
          while (i <= keep)
          {
            ptr[j] = data->line[i];
            i++;
            j++;
          }
          //break ;
        }
        else if (data->line[i + 1] == '$')
        {
          while (data->line[i] == '$')
          {
            if (data->line[i + 1] == '$')
              i += 2;
            else
              break ;
          }
          //take this one off
          //break ;
        }
        //****
        //if (data->line[i] == '$')
        //  i++;
        //maybe here too data->line[i + 1] what if was NULL 
        if (data->line[i] == '$' && ft_acceptable_char(data->line[i + 1]))
        {
          i++;
          len = 0;
          while (ft_acceptable_char(data->line[i]))
          {
            i++;
            len++;
          }
          dolla = malloc(sizeof(char) * len + 1);
          i -= len;
          len = 0;
          while (ft_acceptable_char(data->line[i]))
          {
            dolla[len] = data->line[i];
            i++;
            len++;
          }
          dolla[len] = 0;
          while (ft_strncmp(trav->sec, dolla, len) && trav->next != NULL)
            trav = trav->next;
          //here a problemo with dolla = '\0'
          if (!ft_strncmp(trav->sec, dolla, len))
          {
            free(dolla);
            dolla = ft_strdup(trav->value);
          }
          else
          {
            free(dolla);
            dolla = ft_strdup("");
          }
          len = 0;
          while (dolla[len])
          {
            ptr[j] = dolla[len];
            j++;
            len++;
          }
          trav = data->l_env;
          //while (data->line[i] != '$' && data->line[i] != '\"' && data->line[i])
          //{
          //  ptr[j] = data->line[i];
          //  i++;
          //  j++;
          //}
        }
        else if (data->line[i] == '$' && !ft_acceptable_char(data->line[i + 1]))
        {
          ptr[j++] = data->line[i++];
          while (data->line[i] && data->line[i] != '$' && !ft_acceptable_char(data->line[i + 1]))
          {
            ptr[j] = data->line[i];
            i++;
            j++;
          }
        }
        while (data->line[i] != '$' && data->line[i] != '\"' && data->line[i])
        {
          ptr[j] = data->line[i];
          i++;
          j++;
        }
      }
      if (data->line[i] == '\"' || data->line[i] == '\'')
      {
        if (data->line[i] == '\'')
        {
          ptr[j] = data->line[i];
          i++;
          j++;
        }
        else if (data->line[i] == '\"')
          i++;
      }
    }
    //here check if the end of string or down this while
    while (data->line[i] == '$')
    {
      //****
      if (data->line[i + 1] == ' ' || data->line[i + 1] == '\"' \
          || data->line[i + 1] == '\'')
      {
        ptr[j] = data->line[i];
        i++;
        j++;
        //break ;
      }
      else if (data->line[i + 1] == 0)
      {
        ptr[j] = data->line[i];
        i++;
        j++;
        //break ;
      }
      else if (data->line[i + 1] == '?')
      {
        keep = i + 1;
        while (i <= keep)
        {
          ptr[j] = data->line[i];
          i++;
          j++;
        }
        //break ;
      }
      else if (data->line[i + 1] == '$')
      {
        while (data->line[i] == '$')
        {
          if (data->line[i + 1] == '$')
            i += 2;
          else
            break ;
        }
        //take this one off
        //break ;
      }
      //****
      //add this one
      if (data->line[i] == '$' && ft_acceptable_char(data->line[i + 1]))
      {
        i++;
        len = 0;
        while (ft_acceptable_char(data->line[i]))
        {
          i++;
          len++;
        }
        dolla = malloc(sizeof(char) * len + 1);
        i -= len;
        len = 0;
        while (ft_acceptable_char(data->line[i]))
        {
          dolla[len] = data->line[i];
          i++;
          len++;
        }
        dolla[len] = 0;
        while (ft_strncmp(trav->sec, dolla, len) && trav->next != NULL)
          trav = trav->next;
        if (!ft_strncmp(trav->sec, dolla, len))
        {
          free(dolla);
          dolla = ft_strdup(trav->value);
        }
        else
        {
          free(dolla);
          dolla = ft_strdup("");
        }
        len = 0;
        while (dolla[len])
        {
          ptr[j] = dolla[len];
          j++;
          len++;
        }
        trav = data->l_env;
      }
      else if (data->line[i] == '$' && !ft_acceptable_char(data->line[i + 1]))
      {
        ptr[j++] = data->line[i++];
        while (data->line[i] && data->line[i] != '$' && !ft_acceptable_char(data->line[i + 1]))
        {
          ptr[j] = data->line[i];
          i++;
          j++;
        }
      }
    }
    //else
    //{
      //while (data->line[i] != '\'' && data->line[i] != '\"' && data->line[i])
      //{
    if (data->line[i] != '\"' && data->line[i] != '\'' && data->line[i])
    {
      ptr[j] = data->line[i];
      i++;
      j++;
    }
      //}
    //}
    //i++;
  }
  ptr[j] = 0;
  printf("%s\n", ptr);
}
//'$cool'





//if (data->line[i] == '$')
//{
//  i++;
//  k = 0;
//  while (ft_acceptable_char(data->line[i]))
//  {
//    i++;
//    k++;
//    //dolla[k] = data->line[i];
//  }
//  dolla = malloc(sizeof(char) * k + 1);
//  i = i - k;
//  k = 0;
//  while (ft_acceptable_char(data->line[i]))
//  {
//    dolla[k] = data->line[i];
//    k++;
//    i++;
//  }
//}
