/*
** xmalloc.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/xfunctions
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 10:50:37 2010 philippe berenguel
** Last update Sun Mar 14 11:43:36 2010 philippe berenguel
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void		*xmalloc(size_t size)
{
  void		*new;

  new = malloc(size);
  if (new == NULL)
    {
      perror("malloc");
      exit(EXIT_FAILURE);
    }
  return (new);
}
