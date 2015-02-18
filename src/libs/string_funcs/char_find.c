/*
** find_char.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/libs/string_funcs
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat Mar 13 19:17:00 2010 gianni castellani
** Last update Sat May  1 14:50:52 2010 mickael cerisier
*/

#include <stdlib.h>

int		char_find(char *str, char c)
{
  int		cpt;

  if (str == NULL)
    return (-1);
  cpt = 0;
  while (str[cpt] != '\0' && str[cpt] != c)
    cpt++;
  if (str[cpt] == c)
    return (cpt);
  return (-1);
}
