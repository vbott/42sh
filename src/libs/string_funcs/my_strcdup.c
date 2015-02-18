/*
** my_strcdup.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/libs/string_funcs
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Mar 14 14:36:39 2010 gianni castellani
** Last update Sun Mar 14 18:07:48 2010 gianni castellani
*/

#include "lib_includes/xfunctions.h"

char		*my_strcdup(char *str, char c)
{
  char		*res;
  int		i;
  int		len;

  i = 0;
  len = 0;
  while (str[len] != c && str[len] != '\0')
    len++;
  res = xmalloc((len + 1) * sizeof(*res));
  while (i < len)
    {
      res[i] = str[i];
      i++;
    }
  res[i] = '\0';
  return (res);
}
