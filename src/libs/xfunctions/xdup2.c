/*
** xdup2.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:49:58 2010 philippe berenguel
** Last update Sun Mar 14 11:43:19 2010 philippe berenguel
*/

#include <unistd.h>
#include <stdio.h>

int		xdup2(int oldfd, int newfd)
{
  int		i;

  i = dup2(oldfd, newfd);
  if (i == -1)
    perror("dup2");
  return (i);
}
