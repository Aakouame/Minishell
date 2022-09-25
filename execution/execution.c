/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkaddour <hkaddour@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 10:01:19 by hkaddour          #+#    #+#             */
/*   Updated: 2022/09/25 12:21:01 by hkaddour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void  size_cmd(t_data *data)
{
  data->size_cmd = 0;
  data->trav_cmd = data->v_cmd;
  while (data->trav_cmd)
  {
    data->size_cmd++;
    data->trav_cmd = data->trav_cmd->next;
  }
}

int find_slash(char *cmd)
{
  int i;

  i = 0;
  while (cmd[i])
  {
    if (cmd[i] == '/')
      return (1);
    i++;
  }
  return (0);
}

void  get_path(t_data *data)
{
  int i;
  char **sp;
  t_env *trav;
  char *cmd;

  i = 0;
  trav = data->l_env;
  //still need to fix this chick over here
  if (find_slash(*data->v_cmd->cmd))
  {
    cmd = *data->v_cmd->cmd;
    if (access(cmd, F_OK) == 0)
    {
      if (access(cmd, X_OK) == 0)
      {
        //execve(cmd, data->v_cmd->cmd, data->env);
        execve(cmd, data->v_cmd->cmd, env_double_ptr(data));
        return ;
      }
      else
      {
         //data->chk_dolla = 126;
         printf("minishell: %s: Permission denied\n", cmd);
         exit(126);
         //return ;
      }
    }
    printf("minishell: command not found: %s\n", data->v_cmd->cmd[0]);
    exit(127);
    //return ;
  }
  while (ft_strcmp("PATH", trav->sec) && trav->next)
    trav = trav->next;
  if (!trav)
    return ;
  sp = ft_split(trav->value, ':');
  while (sp[i])
  {
    cmd = ft_strjoin(ft_strjoin(sp[i], "/"), data->v_cmd->cmd[0]);
    //if (access(ft_strjoin(ft_strjoin(sp[i], "/"), data->v_cmd->cmd[0]), F_OK) == 0)
    if (access(cmd, F_OK) == 0)
    {
      if (access(cmd, X_OK) == 0)
      {
        //execve(cmd, data->v_cmd->cmd, env_double_ptr(data));
        execve(cmd, data->v_cmd->cmd, data->env);
        //if (data->v_cmd->f_in == 3)
        //  close(data->v_cmd->f_in);
          //printf("retrun process execve failded\n");
        free(cmd);
        //exit(0);
      }
      else
      {
         //data->chk_dolla = 126;
         printf("minishell: %s: Permission denied\n", cmd);
         exit(126);
         //return ;
      }
    }
    free(cmd);
    i++;
  }
  //here an error
  printf("minishell: command not found: %s\n", data->v_cmd->cmd[0]);
  exit(127);
}

void  run_one_cmd(t_data *data)
{
  int pid; 
  int status;

  pid = fork();
  //error here
  if (pid < 0)
  {
    printf("retrun process execve failded\n");
    return ;
  }
  //pid = 0;
  if (pid == 0)
  {
    if (data->v_cmd->cmd[0])
    {
      if (check_builtin(&data->v_cmd->cmd[0]))
        exit(0);
      //while (1);
      if (data->chk_redct_exist == 1)
      {
        printf("in = %d || out = %d\n", data->v_cmd->f_in, data->v_cmd->f_out);
        dup2(data->v_cmd->f_in, STDIN_FILENO);
        dup2(data->v_cmd->f_out, STDOUT_FILENO);
      }
      get_path(data);
      //close(data->v_cmd->f_in);
    }
    //exit(0);
  }
  if (pid >= 1)
  {
    //wait(0);
    //waitpid(pid, &status, 0);
    //if (status <= -1)
    //if (status == 1)
    //  printf("err in execve \n");
    //else
    //  printf("all good \n");

		signal(SIGINT, SIG_IGN);
    waitpid(pid, &status, 0);
    //printf("%d\n", status);
    //printf("cmd + garbage\n");
    //printf("exit with %d\n", status);
    if (status == 256)
      data->chk_dolla = 1;
    //printf("no cmd existence\n");
    else if (status == 32256)
      data->chk_dolla = 126;
    else if (status == 32512)
      data->chk_dolla = 127;
    else
      data->chk_dolla = 0;
    //i should change the value for builtin tooo

    //if (waitpid(pid, &status, 0) == 0)
    //  printf("all good %d\n", status);
    //else if (waitpid(pid, &status, 0) == 127)
    //  printf("err no cmd %d\n", status);
    //else
    //  printf("err cmd + fleabag %d\n", status);
    //if (data->v_cmd->f_in == 3)
    //  close(data->v_cmd->f_in);
    if (data->v_cmd->cmd[0])
    {
      if (check_builtin(&data->v_cmd->cmd[0]))
        builtin_cmd(data, data->v_cmd->cmd[0]);
    }
    //check no need for 
    //and here if chk was 1 there's a error here cd or other cmd error
    //here check redirection
    return ;
  }
}

int check_redirection(t_data *data)
{
  t_cmd *trav;
  int i;
  int fd;
  int hrdoc_exist;

  i = 0;
  hrdoc_exist = 0;
  trav = data->v_cmd;
  //> this one delete the file if exist and make a new one
  //>> this one not
  if (trav->redirect)
  {
    data->chk_redct_exist = 1;
    while (trav->redirect)
    {
      //I have to find a way to close fds
      if (i > 0)
      {
        if (trav->redirect->typ == O_TRNC || trav->redirect->typ == O_APEND)
        {
          if (data->v_cmd->f_out > 1)
            close(data->v_cmd->f_out);
        }
        else if (trav->redirect->typ == I_TRNC)
        {
          if (data->v_cmd->f_in > 0)
            close(data->v_cmd->f_in);
        }
      }
      if (trav->redirect->typ == O_TRNC)
      {
        if (access(trav->redirect->file, F_OK) == 0)
        {
          if (access(trav->redirect->file, W_OK) == 0)
            fd = open(trav->redirect->file, O_WRONLY | O_TRUNC);
          else
          {
            data->chk_dolla = 126;
            printf("minishell: %s: Permission denied\n", trav->redirect->file);
            return (1);
          }
        }
        fd = open(trav->redirect->file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
        trav->f_out = fd;
      }
      else if (trav->redirect->typ == O_APEND)
      {
        //this one not working well
        //here check if there's permission
        //if (access(trav->redirect->file, W_OK) == 0)
        //if (access(trav->redirect->file, R_OK) == 0)
        //if (access(trav->redirect->file, W_OK) == 0)
        //  fd = open(trav->redirect->file, O_WRONLY | O_APPEND);
        //{
        //  fd = open(trav->redirect->file, O_RDWR | O_APPEND);
        //  if (fd < 0)
        //  {
        //    if (access(trav->redirect->file, R_OK) == 0)
        //      fd = open(trav->redirect->file, O_RDONLY | O_APPEND);
        //    else if (access(trav->redirect->file, W_OK) == 0)
        //      fd = open(trav->redirect->file, O_WRONLY | O_APPEND);
        //    if (fd < 0)
        //    {
        //      data->chk_dolla = 1;
        //      printf("minishell: %s: Permission denied\n", trav->redirect->file);
        //      return (1);
        //    }
        //  }
        //}
        //else if (access(trav->redirect->file, R_OK) == 0)
        //  fd = open(trav->redirect->file, O_RDWR | O_APPEND);
        if (access(trav->redirect->file, F_OK) == 0)
        {
          if (access(trav->redirect->file, W_OK) == 0)
            fd = open(trav->redirect->file, O_WRONLY | O_APPEND);
          else
          {
            data->chk_dolla = 126;
            printf("minishell: %s: Permission denied\n", trav->redirect->file);
            return (1);
          }
        }
        else
          fd = open(trav->redirect->file, O_RDWR | O_APPEND | O_CREAT, 0644);
        trav->f_out = fd;
      }
      else if (trav->redirect->typ == I_APEND)
        hrdoc_exist = 1;
      //{
      //  trav->f_in = data->hrdoc_fd[0];
      //  //printf("f_in == %d\n", trav->f_in);
      //}
      else if (trav->redirect->typ == I_TRNC)
      {
        if (access(trav->redirect->file, F_OK) == 0)
        {
          if (access(trav->redirect->file, R_OK) == 0)
            fd = open(trav->redirect->file, O_RDONLY);
          else
          {
            data->chk_dolla = 126;
            printf("minishell: %s: Permission denied\n", trav->redirect->file);
            return (1);
          }
        }
        else
        {
          data->chk_dolla = 1;
          printf("minishell: %s: No such file or directory\n", trav->redirect->file);
          return (1);
        }
        trav->f_in = fd;
      }
      //trav->f_out = fd;
      //**trav->redirect = trav->redirect->next;
      //machi db
      //hena 7ta nesali
      //if (trav->redirect->next && trav->redirect->typ != I_APEND)
      //if (trav->redirect->next)
      //{
      //  if (trav->redirect->typ == O_TRNC || trav->redirect->typ == O_APEND)
      //    close(data->v_cmd->f_out);
      //  else if (trav->redirect->typ == I_TRNC)
      //    close(data->v_cmd->f_in);
      //  //if (data->v_cmd->f_in > 0)
      //  //  close(data->v_cmd->f_in);
      //  //if (data->v_cmd->f_out > 1)
      //  //  close(data->v_cmd->f_out);
      //}
      trav->redirect = trav->redirect->next;
      i++;
    }
    if (hrdoc_exist == 1)
      trav->f_in = data->hrdoc_fd[0];

    //trav->f_out = fd;
  }
  //else
  //  return (0);
  return (0);
}

void  execution(t_data *data)
{
  //char  ptr[10] = {0};
  //here loop for the parsing nodes and do four function one for single cmd and multiple cmd and redirection
  size_cmd(data);
  if (data->size_cmd == 1)
  {
    //read(data->hrdoc_fd[0], ptr, 9);
    //printf("%s\n", ptr);
    //i have to return an error code to exit to not entre run cmd in case of error
    //cat > l < file  this file not exist

    //**if (check_redirection(data))
    //**  return ;
    if (!check_redirection(data))
      run_one_cmd(data);
    //maybe >> not working well
    //also i should close fd >> > > > a lot in the above func
    if (data->chk_redct_exist == 1)
    {
      if (data->v_cmd->f_in > 0)
      {
        //printf("h\n");
        close(data->v_cmd->f_in);
      }
      if (data->v_cmd->f_out > 1)
      {
        //printf("d\n");
        close(data->v_cmd->f_out);
      }
      //close here file
      //data->v_cmd->f_in = 0;
      //data->v_cmd->f_out = 1;
    }
    //printf("in = %d || out = %d\n", data->v_cmd->f_in, data->v_cmd->f_out);
    //ft_putstr_fd("okay", data->v_cmd->f_out);
    //here a fucntion to execute one cmd and check if it have redirection
      //execution normal
    //if (!data->v_cmd->redirect)
    //{
    //  //merge the cmd and redirection
    //  //printf("hey\n");
    //  //cat show alot of prompt
    //  run_one_cmd(data);
    //  printf("%d\n", data->chk_dolla);
    //}
    //else
    //  return ;
    //  //execution with redirection
  }
  else
  {

  }
  //printf("%d\n", data->size_cmd);
}
