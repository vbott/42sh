/*
** cpy_env.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:19:43 2010 gianni castellani
** Last update Thu Apr  1 15:19:44 2010 gianni castellani
*/

#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"

char		**cpy_env(void)
{
  char		**cpy;
  int		i;
  extern char	**environ;

  i = 0;
  cpy = xmalloc(sizeof(*cpy) * (len_tab(environ) + 1));
  while (environ[i])
    {
      cpy[i] = my_strdup(environ[i]);
      i++;
    }
  cpy[i] = 0;
  return (cpy);
}
