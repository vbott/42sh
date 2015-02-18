/*
** source.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 10 14:02:23 2010 cerisier mickael
** Last update Mon May 10 14:02:23 2010 cerisier mickael
*/

#include <stdlib.h>
#include "parser.h"
#include "execution.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"

int		source(char **cmd)
{
  int		fd;

  if (cmd[1] == NULL)
    {
      my_puterror("source: usage: source filename.\n");
      return (EXIT_FAILURE);
    }
  else if ((fd = xopen(cmd[1], O_RDONLY, 0)) != -1)
    {
      exec_conf(fd, 0);
      xclose(fd);
    }
  return (EXIT_SUCCESS);
}
