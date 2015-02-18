/*
** xpipe.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:53:26 2010 philippe berenguel
** Last update Mon Apr 26 15:19:11 2010 cerisier mickael
*/

#include <unistd.h>
#include <errno.h>
#include <stdio.h>

int		xpipe(int pipefd[2])
{
  int		i;

  i = pipe(pipefd);
  if (i == -1)
    perror("pipe");
  return (i);
}
