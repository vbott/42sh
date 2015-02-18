/*
** my_implode.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 14:20:21 2010 philippe berenguel
** Last update Fri Apr  2 14:20:46 2010 philippe berenguel
*/

#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

char		*my_implode(char **args)
{
  int		i;
  int		e;
  int		len;
  char		*res;

  len = 0;
  i = 0;
  e = 0;
  while (args[i])
    len += my_strlen(args[i++]);
  res = xmalloc((len + i + 1) * sizeof(*res));
  i = 0;
  while (args[i])
    {
      len = 0;
      while (args[i][len])
	res[e++] = args[i][len++];
      if (args[i + 1])
	res[e++] = ' ';
      i++;
    }
  res[e] = '\0';
  return (res);
}
