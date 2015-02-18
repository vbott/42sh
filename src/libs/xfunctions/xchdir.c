/*
** xchdir.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:29:56 2010 philippe berenguel
** Last update Fri Apr  2 13:29:57 2010 philippe berenguel
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			xchdir(const char *path)
{
  int			i;

  i = chdir(path);
  if (i == -1)
    perror("cd");
  return (i);
}
