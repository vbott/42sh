/*
** xdup.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:49:22 2010 philippe berenguel
** Last update Sat Apr 17 15:54:17 2010 gianni castellani
*/

#include <unistd.h>
#include <stdio.h>

int		xdup(int oldfd)
{
  int		i;

  i = dup(oldfd);
  if (i == -1)
    perror("dup");
  return (i);
}
