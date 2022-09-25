/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 18:34:24 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/24 17:18:36 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  sig_c(int c)
{
  //(void)c;
  //ft_putendl_fd("", 0);
  if (c == SIGINT) {
    printf("\n");
    rl_on_new_line();
    //char *cmd[] = {"/bin/stty", 0 };
    //char *cmd_args[] = {" ", "-echoctl", 0};
    //execve(cmd[0], cmd_args, NULL);
    rl_replace_line("", 0);
    rl_redisplay();

    //rl_redisplay();
    //rl_on_new_line();
  }
  else if (c == SIGQUIT)
  {
    printf("\n");
    //rl_on_new_line();
    //rl_redisplay();
    exit(0);
  }
}

//t_env *node_allocate(t_data *data)
//{
//  (void)data;
//  t_env *node;
//
//  node = (t_env *) malloc(sizeof(t_env));
//  node->sec = NULL;
//  node->value = NULL;
//  node->next = NULL;
//  return (node);
//}
//
//void  get_env(t_data *data)
//{
//  int   i;
//  int   j;
//  int   k;
//  t_env *env;
//  t_env *next;
//  t_env *trav;
//
//  i = 1;
//  env = (t_env *)malloc(sizeof(t_env));
//  //data->l_env = env;
//  trav = env;
//  while (data->env[i])
//  {
//    next = node_allocate(data);
//    env->next = next;
//    env = env->next;
//    i++;
//  }
//  i = 0;
//  env = trav;
//  while (data->env[i])
//  {
//    j = 0;
//    while (data->env[i][j] && data->env[i][j] != '=')
//      j++;
//    env->sec = malloc(sizeof(char) * j + 1);
//    j = 0;
//    while (data->env[i][j] && data->env[i][j] != '=')
//    {
//      env->sec[j] = data->env[i][j];
//      j++;
//    }
//    env->sec[j] = 0;
//    k = ft_strlen(data->env[i]) + 1;
//    //here pass the equal sign
//    j++;
//    env->value = malloc(sizeof(char) * k - j);
//    k = 0;
//    while (data->env[i][j] && data->env[i][j] != 0)
//    {
//      env->value[k] = data->env[i][j];
//      j++;
//      k++;
//    }
//    env->value[k] = 0;
//    //why did u add another node allocate this one just added leaks and i didn't use it
//    //node_allocate(data);
//    env = env->next;
//    i++;
//  }
//  env = trav;
//  data->l_env = env;
//  //add one to the indent level
//  while (ft_strncmp(trav->sec, "SHLVL", 5))
//    trav = trav->next;
//  //i = ft_strlen(trav->value) - 1;
//  //trav->value[i] += 1;
//  int shlvl;
//  data->shlvl_ptr = trav;
//  shlvl = ft_atoi(trav->value);
//  shlvl++;
//  free(trav->value);
//  data->shlvl_ptr->value = ft_itoa(shlvl);
//  //trav->value = ft_itoa(shlvl);
//
//  //while (trav->next)
//  //{
//  //  printf("%s=%s\n", trav->sec, trav->value);
//  //  trav = trav->next;
//  //}
//}

//I have to take this one off and work with my env
//void  get_path(t_data *data)
//{
//  int   i;
//  int   j;
//  int   k;
//
//  i = 0;
//  j = 5;
//  while (data->env[i] && ft_strncmp(data->env[i], "PATH=", 5))
//    i++;
//  while (data->env[i][j] && data->env[i][j])
//    j++;
//  data->w_path = malloc(sizeof(char) * j + 1);
//  if (!data->w_path)
//    return ;
//  //ft_strdup(data->env[i]);
//  j = 5;
//  k = 0;
//  while (data->env[i][j])
//  {
//    data->w_path[k] = data->env[i][j];
//    j++;
//    k++;
//  }
//  data->w_path[k] = 0;
//}

//void  excute(t_data *data)
//{
//  int i;
//
//  i = 0;
//  get_path(data);
//  data->cmd = ft_split(data->line, ' ');
//  data->split = ft_split(data->w_path, ':');
//  while (data->split[i])
//  {
//    data->abs_path = ft_strjoin(ft_strjoin(data->split[i], "/"), data->cmd[0]);
//    //printf("%s\n", data->abs_path);
//    if (!access(data->abs_path, F_OK))
//    {
//      execve(data->abs_path, data->cmd, data->env);
//    }
//    free(data->abs_path);
//    i++;
//  }
//}

//void  execute_cmd(t_data *data)
//{
//  int pid;
//
//  //here check if the cmd working then check fork
//  pid = fork();
//  if (pid < 0)
//    exit(2);
//  else if (pid == 0)
//  {
//    excute(data);
//  }
//  else
//  {
//    wait(0);
//    return ;
//  }
//}

//**int check_builtin(t_data *data)
//**{
//**  t_token *trav;
//**  int   i;
//**  char  **sp;
//**  char  cmd[] = "cd echo pwd export unset env exit";
//**
//**  //i = 0;
//**  trav = data->t_token;
//**  sp = ft_split(cmd, ' ');
//**  //while (trav)
//**  //{
//**  //get the commad u want to check
//**  //this var of trav should be in struct so i can rememver the value
//**  //while (trav)
//**  //{
//**  //  if (trav->type == WRD)
//**  //    break ;
//**  //  trav = trav->next;
//**  //}
//**  //i = 0;
//**  while (trav)
//**  {
//**    i = 0;
//**    if (trav->type == WRD)
//**    {
//**      while (sp[i])
//**      {
//**        if (!strncmp(trav->value, sp[i], ft_strlen(sp[i]) + 1))
//**        {
//**          data->built_cmd = trav;
//**          return (1);
//**        }
//**        i++;
//**      }
//**    }
//**    trav = trav->next;
//**  }
//**  //**here free
//**  //i = 0;
//**  //while (sp[i])
//**  //{
//**  //  free(sp[i]);
//**  //  i++;
//**  //}
//**  //free(sp);
//**  //free(cmd);
//**  //while (sp[i])
//**  //{
//**  //  if (!strncmp(trav->value, sp[i], ft_strlen(sp[i])))
//**  //  {
//**  //    data->built_cmd = data->t_token;
//**  //    return (1);
//**  //  }
//**  //  i++;
//**  //}
//**  return (0);
//**  //}
//**  //while (trav->type != WRD)
//**  //  trav = trav->next;
//**  //if (ft_strncmp(trav->value, "cd", 2))
//**  //  cd_cmd(data);
//**  //else if (ft_strncmp(trav->value, "echo", 4))
//**  //  echo_cmd(data);
//**  //else if (ft_strncmp(trav->value, "pwd", 3))
//**  //  pwd_cmd(data);
//**  //else if (ft_strncmp(trav->value, "export", 6))
//**  //  export_cmd(data);
//**  //else if (ft_strncmp(trav->value, "unset", 5))
//**  //  unset_cmd(data);
//**  //else if (ft_strncmp(trav->value, "env", 3))
//**  //  env_cmd(data);
//**  //else if (ft_strncmp(trav->value, "exit", 4))
//**  //  exit_cmd(data);
//**  //return (0);
//**}

//void  exit_cmd(t_data *data)
//{
//  (void)data;
//  //(void)data;
//  //free(data->line);
//  //free other shiit
//  //exit(2);
//  exit(0);
//}

void  *put_str(char *str, int len)
{
  int   i;
  char  *ptr;

  i = 0;
  //if (!str)
  //  str = "/";
  //if (len < i)
  //{
  //  ptr = malloc(2);
  //  ptr[i++] = '/';
  //  ptr[i] = 0;
  //}
  ptr = malloc(sizeof(char) * len + 1);
  if (!ptr)
    return (NULL);
  while (i <= len)
  {
    ptr[i] = str[i];
    i++;
  }
  ptr[i] = 0;
  return (ptr);
}

//void  cd_cmd(t_data *data)
//{
//  //(void)data;
//  t_env *trav;
//  t_env *home;
//  //char  *path;
//
//  //trav = data->l_env;
//  //maybe i have to put get env here cuz everytime i change the path the PWD change
//  //get_env(data);
//  trav = data->l_env;
//  home = data->l_env;
//  while (ft_strncmp(home->sec, "HOME", 4))
//    home = home->next;
//  if (data->built_cmd->next == NULL || data->built_cmd->next->next == NULL)
//  {
//    //just use HOME
//    //while (ft_strncmp(trav->sec, "HOME", 4))
//    //  trav = trav->next;
//    //data->cd_path = trav->value;
//    data->cd_path = home->value;
//    //if (chdir(trav->value) != 0)
//    if (chdir(data->cd_path) != 0)
//    {
//      error("minishell: no command found", 1);
//      return ;
//    }
//    reinit_env(data);
//    return ;
//  }
//  while (ft_strncmp(trav->sec, "PWD", 3))
//    trav = trav->next;
//  //gad blan just cd only
//  if (data->built_cmd->next->type != W_SPACE)
//    error(data->built_cmd->value, 2);
//  else if (data->built_cmd->next->type == W_SPACE)
//  {
//    //printf("ok");
//    //check if there are more spaces or empty
//    data->built_cmd = data->built_cmd->next->next;
//    if (data->built_cmd->type == WRD)
//    {
//      if (!ft_strncmp(data->built_cmd->value, "..", 2))
//      {
//        int i;
//
//        i = ft_strlen(trav->value) - 1;
//        //check if trav->value equal to '/'
//        while (trav->value[i] != '/')
//          i--;
//        if (i > 0)
//          i--;
//        data->cd_path = put_str(trav->value, i);
//        //put this one in a if so if a error happen or something
//        //chdir(data->cd_path);
//        if (chdir(data->cd_path) != 0)
//        {
//          error("minishell: no directory matched :v", 1);
//          return ;
//        }
//        //data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//      }
//      //path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//      else if (!ft_strncmp(data->built_cmd->value, "/", 1))
//      {
//        int   i;
//        int   len;
//        char  *no_slash;
//
//        i = 0;
//        len = ft_strlen(data->built_cmd->value) - 1;
//        //here if the cmd was "/User/jfkjfk"
//        if (data->built_cmd->value[1] != 0 && data->built_cmd->value[1] != '/')
//        {//here check if the path has '/' in the end or not
//          if (data->built_cmd->value[len] == '/')
//          {
//            no_slash = malloc(sizeof(char) * len);
//            while (i < len)
//            {
//              no_slash[i] = data->built_cmd->value[i];
//              i++;
//            }
//            no_slash[i] = 0;
//            //data->cd_path = data->built_cmd->value;
//            data->cd_path = no_slash;
//            if (chdir(data->cd_path) != 0)
//            {
//              error("error this path is not exist", 1);
//              return ;
//            }
//          }
//          else if (data->built_cmd->value[len] != '/')
//          {
//            data->cd_path = data->built_cmd->value;
//            if (chdir(data->cd_path) != 0)
//            {
//              error("error this path is not exist", 1);
//              return ;
//            }
//          }
//        }
//        else
//        {
//          data->cd_path = "/";
//          if (chdir(data->cd_path) != 0)
//          {
//            error("error this path is not exist", 1);
//            return ;
//          }
//        }
//        //data->cd_path = "/";
//        //trav->value = "/";
//        //chdir(trav->value);
//        //chdir(data->cd_path);
//        //if (chdir(data->cd_path) != 0)
//      }
//      else if (!ft_strncmp(data->built_cmd->value, "~", 1))
//      {
//        if (data->built_cmd->value[0] == '~' && (data->built_cmd->value[1] == '/' || data->built_cmd->value[1] == 0))
//        {
//          //while (ft_strncmp(trav->sec, "HOME", 4))
//          //  trav = trav->next;
//          data->cd_path = home->value;
//          if (chdir(home->value) != 0)
//          {
//            error("minishell: no command found", 1);
//            return ;
//          }
//          reinit_env(data);
//          return ;
//          //if (data->built_cmd->value[1] == '/' || data->built_cmd->cmd->value[1] == 0)
//        }
//        else
//        {
//          error("error this derectory not exist :v", 1);
//          return ;
//        }
//      }
//      else
//      {
//        int   i;
//        int   j;
//        int   len;
//        char  *no_slash;
//
//        j = 0;
//        i = ft_strlen(trav->value) - 1;
//        len = ft_strlen(data->built_cmd->value) - 1;
//        //if (data->built_cmd->value[i] == '/')
//        if (data->built_cmd->value[len] == '/')
//        {
//          no_slash = malloc(sizeof(char) * len);
//          //len--;
//          while (j < len)
//          {
//            no_slash[j] = data->built_cmd->value[j];
//            j++;
//          }
//          no_slash[j] = 0;
//          //data->cd_path = ft_strjoin(trav->value, no_slash);
//          if (trav->value[i] == '/')
//            data->cd_path = ft_strjoin(trav->value, no_slash);
//          else
//            data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), no_slash);
//        }
//        else if (data->built_cmd->value[len] != '/')
//        {//here if we are in pwd / and we want to cd home for example it adds //home
//          if (ft_strlen(trav->value) == 1)
//            data->cd_path = ft_strjoin(trav->value, data->built_cmd->value);
//          else
//            data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//        }
//        //else
//        //{
//
//        //}
//
//        //if (trav->value[i] == '/')
//        //if (data->built_cmd->value[i] == '/')
//        //  data->cd_path = ft_strjoin(trav->value, data->built_cmd->value);
//        //else
//        //  data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//
//        //if (data->built_cmd->value[i] == '/' && trav->value[i] != '/')
//        //  data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//        //  //data->cd_path = ft_strjoin(trav->value, data->built_cmd->value);
//        //else if (data->built_cmd->value[i] != '/' && trav->value[i] == '/')
//        //  data->cd_path = ft_strjoin(trav->value, data->built_cmd->value);
//          //data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//
//
//        //if (i == 1)
//        //  data->cd_path = ft_strjoin(trav->value, data->built_cmd->value);
//        //else
//        //  data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), data->built_cmd->value);
//
//        //printf("%s\n", data->cd_path);
//        //chdir(path);
//        //check error of chdir
//        //chdir(data->cd_path);
//        if (chdir(data->cd_path) != 0)
//        {
//          error("minishell: no directory matched :v", 1);
//          return ;
//        }
//        //if (chdir(path) != 0)
//        //  error("minishell: no command found", 1);
//      }
//    }
//    else if (data->built_cmd->type == D_QUOT || data->built_cmd->type == S_QUOT)
//    {
//      int   len;
//      char  *pipi;
//
//      if (data->built_cmd->type == D_QUOT)
//        pipi = ft_strtrim(data->built_cmd->value, "\"");
//      //else if (data->built_cmd->type == S_QUOT)
//      else
//        pipi = ft_strtrim(data->built_cmd->value, "\'");
//      len = ft_strlen(pipi) - 1;
//      //if (data->built_cmd->value[len] == '/')
//      if (pipi[1] != 0 && pipi[1] != '/')
//      {
//        if (pipi[0] == '/')
//        {
//          if (pipi[len] == '/')
//          {
//            int   i;
//            char  *str;
//
//            i = 0;
//            str = malloc(sizeof(char) * len);
//            while (i < len)
//            {
//              str[i] = pipi[i];
//              i++;
//            }
//            str[i] = 0;
//            data->cd_path = str;
//            if (chdir(data->cd_path) != 0)
//            {
//              error("The path is not correct", 1);
//              return ;
//            }
//          }
//          else
//          {
//            data->cd_path = pipi;
//            if (chdir(data->cd_path) != 0)
//            {
//              error("The path is not correct", 1);
//              return ;
//            }
//          }
//        }
//        else
//        {
//          if (pipi[len] == '/')
//          {
//            int   i;
//            char  *str;
//
//            i = 0;
//            str = malloc(sizeof(char) * len);
//            while (i < len)
//            {
//              str[i] = pipi[i];
//              i++;
//            }
//            str[i] = 0;
//            data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), str);
//            if (chdir(data->cd_path) != 0)
//            {
//              error("The path is not correct", 1);
//              return ;
//            }
//          }
//          else
//          {
//            if (trav->value[0] == '/' && trav->value[1] == 0)
//              data->cd_path = ft_strjoin(trav->value, pipi);
//            else
//              data->cd_path = ft_strjoin(ft_strjoin(trav->value, "/"), pipi);
//            if (chdir(data->cd_path) != 0)
//            {
//              error("The path is not correct", 1);
//              return ;
//            }
//          }
//        }
//        //if (pipi[len] == '/')
//        //{
//        //  int   i;
//        //  char  *str;
//
//        //  i = 0;
//        //  str = malloc(sizeof(char) * len);
//        //  while (i < len)
//        //  {
//        //    str[i] = pipi[i];
//        //    i++;
//        //  }
//        //  str[i] = 0;
//        //  data->cd_path = str;
//        //  if (chdir(data->cd_path) != 0)
//        //    error("The path is not correct", 1);
//        //  //{
//        //  //  error("The path is not correct", 1);
//        //  //  return ;
//        //  //}
//        //  //else
//        //  //{
//        //  //  reinit_env(data);
//        //  //  return ;
//        //  //}
//        //}
//        //else
//        //{
//        //  data->cd_path = pipi;
//        //  if (chdir(data->cd_path) != 0)
//        //    error("The path is not correct", 1);
//        //  //{
//        //  //  error("The path is not correct", 1);
//        //  //  return ;
//        //  //}
//        //  //else
//        //  //{
//        //  //  reinit_env(data);
//        //  //  return ;
//        //  //}
//        //}
//      }
//      else if (!ft_strncmp(pipi, "~", 1))
//      {
//
//      }
//      else
//      {
//        data->cd_path = "/";
//        if (chdir(data->cd_path) != 0)
//          error("The path is not correct", 1);
//      }
//    }
//    //chdir("/Users");
//    //printf("ok");
//    //here change the PWD in the env and add the old PWD
//    //here reinit the env
//    //here free all env i open
//    reinit_env(data);
//    //setenv("PWD", "/Users/hkaddour", 1);
//    //printf("%s\n", trav->value);
//  }
//  //printf("done");
//  //printf("%s\n", data->built_cmd->next->next->value);
//  //path = ft_strjoin("/Users/hkaddour/", data->built_cmd->next->next->value);
//  //printf("%s\n", path);
//  //get_env(data);
//  //printf("%s\n", data->l_env->sec);
//  //chdir(path);
//  //chdir(data->built_cmd->next->value);
//  //chdir("~/");
//  //chdir("/Users/hkaddour/");
//}

//void  exec_buil_cmd(t_data *data)
//{ //char ll[] = "cd";
//  if (!ft_strncmp(data->built_cmd->value, "cd", 2))
//    cd_cmd(data);
//  //cd only with a space error check
//  else if (!ft_strncmp(data->built_cmd->value, "echo", 4))
//    echo_cmd(data);
//  else if (!ft_strncmp(data->built_cmd->value, "pwd", 3))
//    pwd_cmd(data);
//  else if (!ft_strncmp(data->built_cmd->value, "export", 6))
//    export_cmd(data);
//  else if (!ft_strncmp(data->built_cmd->value, "unset", 5))
//    unset_cmd(data);
//  else if (!ft_strncmp(data->built_cmd->value, "env", 3))
//    env_cmd(data);
//  else if (!ft_strncmp(data->built_cmd->value, "exit", 4))
//    exit_cmd(data);
//}

void  nl(void)
{
  //here do a check
  //printf("\n");
  rl_on_new_line();
  rl_replace_line("", 0);
}

//this for the prompt
//had fucntion is named leaks cuz it got alot of them
void  prompt_changer(t_data *data)
{
  t_env *pwd;
  //t_env *home;
  char  *path_h; //this is for ~
  int   len;
  int   i;
  //char  *tmp = "~/";
  //char  *clr_err = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m";
  //char  *clr_err = "\e[103m \e[91m \e[40m\e[93m \e[97m \e[44m\e[30m\e[44m \e[30m";
  //char  *clr1 = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m";
  char  *clr1;
  char  *clr2 = " \e[0m\e[34m \e[0m";

  if (data->chk_dolla == 0)
    clr1 = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30m";
  else
    clr1 = "\e[103m \e[91m \e[40m\e[93m \e[97m \e[44m\e[30m\e[44m \e[30m";
  pwd = data->l_env;
  //home = data->l_env;
  while (ft_strcmp(pwd->sec, "PWD") && pwd->next)
    pwd = pwd->next;
  //while (ft_strcmp(home->sec, "HOME") && home->next)
  //  home = home->next;
  path_h = getenv("HOME");
  if (!ft_strncmp(pwd->value, path_h, ft_strlen(path_h)))
  {
    if (ft_strlen(pwd->value) > ft_strlen(path_h))
    {
      //len = ft_strlen(pwd->value) - ft_strlen(home->value);
      len = ft_strlen(path_h);
      data->prompt = malloc(sizeof(char) * len + 3);
      i = 0;
      //while (i < 2)
      //{
      //  data->prompt[i] = tmp[i];
      //  i++;
      //}
      data->prompt[i++] = '~';
      while (pwd->value[len])
        data->prompt[i++] = pwd->value[len++];
      data->prompt[i] = 0;
      data->prompt = ft_strjoin(clr1, ft_strjoin(data->prompt, clr2));
    }
    else if (ft_strlen(pwd->value) == ft_strlen(path_h))
    {
      data->prompt = "~";
      data->prompt = ft_strjoin(clr1, ft_strjoin(data->prompt, clr2));
    }
  }
  else
  {
    data->prompt = ft_strjoin(clr1, ft_strjoin(pwd->value, clr2));
    //just join the color with path
  }
  //if (!ft_strcmp(pwd->sec, "PWD") && !ft_strcmp(home->sec, "HOME"))
  //{

  //}
}

void  make_myown_env(t_data *data)
{
  t_env *head;
  t_env *node;
  int   i;
  char  **sp1;
  char  **sp2;
  char  *sec = "PATH SHLVL";
  char  *val = "/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin 1";

  i = 0;
  sp1 = ft_split(sec, ' ');
  sp2 = ft_split(val, ' ');
  head = node_allocate();
  head->sec = "PWD";
  head->value = malloc(1024);
  getcwd(head->value, 1024);
  data->l_env = head;
  while (i < 2)
  {
    node = node_allocate();
    node->sec = sp1[i];
    node->value = sp2[i];
    head->next = node;
    head = node;
    i++;
  }
  //head = data->l_env;
  //while (head)
  //{
  //  printf("%s = %s\n", head->sec, head->value);
  //  head = head->next;
  //}
  //while(1);
}

int main(int ac, char **av, char **envp)
{
  t_data  data;
  int     i;
  int     j;
  //char    prompt[] = "\e[44m\033[4;37m$Minishell>";
  //char    prompt[] = "\e[43m\e[44mMinishell\033[4;37mMinishell>";
  //the Minishell in the prompt will be change by cd changing to file name and at first it get the path of in env to print
  //that file name
  //char    prompt[] = "\e[40m \e[97m \e[44m\e[30m\e[44m \e[30mMinishell \e[0m\e[34m \e[0m";

  i = 0;
  //use an if here only if ac == 1
  (void)ac;
  data.args = av;
  //data.env = envp;
  //write(0, &prompt, sizeof(prompt));
  //make a function that init all var that u work with
  j = 0;
  data.old_pwd_make = 0;
  data.chk_redct_exist = 0;
	data.chk_dolla = 0;
  data.old_pwd_value = ft_strdup("");
  if (!envp[0])
  {
    make_myown_env(&data);
  }
  else
  {
    data.env = envp;
    get_env(&data);
  }
  //**prompt_changer(&data);
  //maybe here i will print date and time and user name
  //also make a last login file to print in first 
  while (1)
  {
    //line = grab_line(0);
    signal(SIGINT, sig_c);
    signal(SIGQUIT, sig_c);
    //printf("%d\n", getpid());
    prompt_changer(&data);
    data.line = readline(data.prompt);
    if (!data.line)
      return (0);
    //if (!ft_strncmp(data.line, "exit", 4))
    //{
    //  free(data.line);
    //  exit(0);
    //}
    //if (!ft_strncmp(data.line, "cd", 2))
    //  chdir("/Users/hkaddour/");
    //if (!ft_strncmp(data.line, "$", 1))
    //tokenizer(&data);
    //execute_cmd(&data);
    //if (!data.env)

    //**j = 0;
    //**while (envp[j])
    //**{
    //**  printf("%s\n", envp[j]);
    //**  j++;
    //**}

    //old initialize for env
    //**if (j == 0)
    //**{
    //**  data.env = envp;
    //**  get_env(&data);
    //**  j++;
    //**}

    //data.env = envp;
    //get_env(&data);
    //also do it for lexer and exextion
    if (data.line[0] == 0)
      nl();
    else
    {
      tokenizer(&data);
      //printf("in = %d || out %d\n", data.hrdoc_fd[0], data.hrdoc_fd[1]);
      //here fucntion of execution
      //if an error happen in tokenizer don't execute ****
      execution(&data);
    }
    //here if up was error should not entre here i should do a var boolean
    //execution(&data);
      //token_s_quote(&data);
      //**tokenizer(&data);
    //lexer problem exit not working in the first time two times machi lexer tokenizer of something else $
    //*lexer(&data);
    //builtin cmd
    //env
    //unset
    //export for variables
    //maybe this should be in loop to see all the list element
    //still have to fix if there are for example cd cd cd alot of cammand

    //lexer should be here so if there is a error the program will not continue to exec the cmd

    //**if (check_builtin(&data))
    //**  exec_buil_cmd(&data);
      //printf("%s\n", data.built_cmd->value);
      //printf("yes\n");

    //to fix exit just check if the cmd it's a valid cmd in the first and then run it

    //**else
    //**  execute_cmd(&data);

    //**this one for shlvl when u run ./minishell in readline
    //**data.built_cmd->value = av[0];
    //**if (!ft_strncmp(data.built_cmd->value, av[0], ft_strlen(av[0])))
    //**{
    //**  int shlvl;
    //**  //data.shlvl_ptr = trav;
    //**  shlvl = ft_atoi(data.shlvl_ptr->value);
    //**  shlvl++;
    //**  data.shlvl_ptr->value = ft_itoa(shlvl);
    //**}

      //here exec 3adi
      //printf("nah\n");

    //**Before exuting the command check if it builtin or not
    //execute_cmd(&data);
    //excute(&data);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //excute(&data);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //data.split = ft_split(data.w_path, ':');
    //while (data.split[i])
    //{
    //  printf("%s\n", data.split[i]);
    //  i++;
    //}
    //printf("%s\n", data.line);
    //get_path(&data);
    //printf("%s\n", data.w_path);
    //while (data.w_path[i])
    //  printf("%d\n", data.w_path[i++]);
    if (data.line[0])
    {
      i = 0;
      while (data.line[i] == ' ' || (data.line[i] >= 9 && data.line[i] <= 13))
        i++;
      if (data.line[i])
        add_history(data.line);
    }
    free(data.line);
    //**here should free tokenizer in case of error or normal and parsing nodes
    //this func free all token nodes
    //***here make a condition to free the tokenizer node
		//***free_token_node(&data);
    //if (!ft_strncmp(data.built_cmd->value, "exit", 4))
    //{
    //  break ;
    //  //return (0);
    //}
    //write(0, &prompt, sizeof(prompt));
  }
  return (0);
}
//pseudo code:
//recursive descent paser algo:
//first read line
//make a scanner that generate tokens for each cmd and error
//handle the Ctrl-C ... just in the minishel prompt.










//examples for lldb:
//"'$d' $n"$lo
//"'$d' $n"'$lo'
//"'$VIM' $PWD '$co'"$SHLVL'$SU'
//"ls"-la > file | grep a
//"ls"-la
