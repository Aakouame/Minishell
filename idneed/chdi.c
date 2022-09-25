#include "minishell.h"

int main(int ac, char **av, char **env)
{
  //int i;
  char  *buf;

  //i = 0;
  //while (ft_strncmp(env[i], "PWD", 3))
  //  i++;
  buf = getenv("PWD");
  //getcwd(buf, sizeof(buf));
  //printf("%s\n", env[i]);
  printf("%s\n", buf);
  chdir("/Users");
  //setenv("PWD", "/Users", 1);
  buf = getenv("PWD");
  printf("%s\n", buf);
  //i = 0;
  //while (ft_strncmp(env[i], "PWD", 3))
  //  i++;
  //printf("%s\n", env[i]);
}
