/*
** xclose.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:48:22 2010 philippe berenguel
** Last update Sun Mar 14 11:42:59 2010 philippe berenguel
*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int		xclose(int fd)
{
  int		i;

  i = close(fd);
  if (i == -1)
    perror("close");
  return (i);
}
