/*
** xwrite.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:40:13 2010 cerisier mickael
** Last update Wed Apr 28 11:40:14 2010 cerisier mickael
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

ssize_t			xwrite(int fd, const void *buf, size_t count)
{
  int			i;

  i = write(fd, buf, count);
  if (i == -1)
    perror("write");
  return (i);
}
