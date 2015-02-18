/*
** my_strcmp.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/libs/string_funcs
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 13 19:38:24 2010 gianni castellani
** Last update Wed Mar 31 16:47:21 2010 gianni castellani
*/

#include <stdlib.h>

int		my_strcmp(const char *s1, const char *s2)
{
  int		cpt;

  if (s1 == NULL || s2 == NULL)
    return ((s1 == s2) ? 0 : -1);
  cpt = 0;
  while (s1[cpt] != '\0' && s2[cpt] != '\0' && s1[cpt] == s2[cpt])
    cpt++;
  return (s1[cpt] - s2[cpt]);
}
