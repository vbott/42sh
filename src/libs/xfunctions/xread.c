/*
** xread.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:53:06 2010 philippe berenguel
** Last update Wed May 19 21:30:57 2010 gianni castellani
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>

ssize_t			xread(int fd, void *buf, size_t count)
{
  int			i;

  i = read(fd, buf, count);
  if (i == -1 && errno != EINTR)
    perror("read");
  return (i);
}
