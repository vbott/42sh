/*
** my_strndup.c for 42sh in /u/all/bereng_p/cu/public/42group/current/headers/lib_headers
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:16:57 2010 philippe berenguel
** Last update Tue May 11 17:06:32 2010 gianni castellani
*/

#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

char		*my_strndup(const char *s, int size)
{
  char		*res;
  int		i;

  i = my_strlen(s);
  res = xmalloc(sizeof(*res) * (((i < size) ? i : size) + 1));
  i = 0;
  while (s[i] != '\0' && i < size)
    {
      res[i] = s[i];
      i++;
    }
  res[i] = '\0';
  return (res);
}
