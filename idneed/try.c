/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   try.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:49:22 by hkaddour          #+#    #+#             */
/*   Updated: 2022/08/09 16:48:14 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

int main()
{
  int   i;
  char  *p;
  char  *goat;
  char  ptr[]= "\"okay son\" l";

  i = 0;
  if (ptr[i] == '\"')
  {
    i++;
    while (ptr[i])
    {
      if (ptr[i] == '\"')
        break ;
      i++;
    }
    if (ptr[i] == '\"')
    {
      i++;
      //p = &ptr[i];
    }
    //p = &ptr[i];
  }
  p = &ptr[i];
  goat = malloc(sizeof(char) * i + 1);
  int j = 0;
  while (&ptr[j] != &p[0])
  {
    goat[j] = ptr[j];
    j++;
  }
  goat[j] = 0;
}

//int main(int ac, char **av)
//{
//  int   i;
//  int   j;
//  char  *ptr;
//
//  i = 0;
//  //printf("%s", av[1]);
//  if (ac == 1)
//  {
//    printf("add the args");
//    return (0);
//  }
//  if (av[1][i] == '\"')
//  {
//    printf("hey\n");
//    i++;
//    while (av[1][i])
//    {
//      if (av[1][i] == '\"')
//      {
//        i++;
//        break ;
//      }
//      i++;
//    }
//    //ptr = &av[1][i];
//  }
//  //else if ()
//  //  printf("error");
//  j = 0;
//  ptr = malloc(sizeof(char) * i + 1);
//  if (!ptr)
//    return (0);
//  while (av[1][j] != av[1][i])
//  {
//    ptr[j] = av[1][j];
//    j++;
//  }
//  ptr[j] = 0;
//  printf("%s", ptr);
//  return (0);
//}



//program i built
//int main()
//{
//  int   i;
//  int   j;
//  int   quote;
//  char  *ptr;
//  char  av[]= "\"hey cool |>>\"";
//
//  i = 0;
//  quote = 0;
//  if (av[i] == '\"')
//  {
//    quote++;
//    i++;
//    while (av[i])
//    {
//      if (av[i] == '\"')
//      {
//        quote++;
//        i++;
//        break ;
//      }
//      i++;
//    }
//    //ptr = &av[1][i];
//  }
//  else
//    printf("error");
//  j = 0;
//  int len;
//  len = i - quote;
//  ptr = malloc(sizeof(char) * len + 1);
//  if (!ptr)
//    return (0);
//  int k = 0;
//  while (av[j] != av[i] && j < len)
//  {
//    if (av[k] == '"')
//      k++;
//    ptr[j] = av[k];
//    j++;
//    k++;
//  }
//  ptr[j] = 0;
//  printf("%s\n", ptr);
//  return (0);
//}
