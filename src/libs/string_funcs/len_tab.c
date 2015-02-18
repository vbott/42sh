/*
** len_tab.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:45:58 2010 philippe berenguel
** Last update Fri Apr  2 13:45:59 2010 philippe berenguel
*/

#include <stdlib.h>

int		len_tab(char **tab)
{
  int		i;

  i = 0;
  if (tab != NULL)
    while (tab[i])
      i++;
  return (i);
}
