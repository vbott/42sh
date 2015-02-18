/*
** xopen.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:51:21 2010 philippe berenguel
** Last update Wed Apr 28 11:43:58 2010 cerisier mickael
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int			xopen(const char *pathname, int flags, mode_t mode)
{
  int			i;

  i = open(pathname, flags, mode);
  if (i == -1)
    perror("open");
  return (i);
}
