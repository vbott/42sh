/*
** my_strlen.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:25:42 2010 philippe berenguel
** Last update Sun Mar 14 11:30:19 2010 philippe berenguel
*/

#include <stdlib.h>

size_t		my_strlen(const char *s)
{
  size_t	i;

  if (s == NULL)
    return (0);
  i = 0;
  while (s[i] != '\0')
    i++;
  return (i);
}
