/*
** my_strdup.c for 42sh in /u/all/bereng_p/cu/public/42group/current/headers/lib_headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:16:57 2010 philippe berenguel
** Last update Sun Mar 14 18:24:39 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

char		*my_strdup(const char *s)
{
  char		*res;
  int		i;

  i = 0;
  if (s == NULL)
    return (NULL);
  res = xmalloc(sizeof(*res) * (my_strlen(s) + 1));
  while (s[i] != '\0')
    {
      res[i] = s[i];
      i++;
    }
  res[i] = '\0';
  return (res);
}
