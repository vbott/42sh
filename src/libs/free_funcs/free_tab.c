/*
** free_tab.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/free_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 19:14:38 2010 philippe berenguel
** Last update Sun Mar 14 19:15:11 2010 philippe berenguel
*/

#include <stdlib.h>

void		free_tab(char **tab)
{
  int		i;

  if (!tab)
    return ;
  i = 0;
  while (tab[i])
    {
      free(tab[i]);
      i++;
    }
  free(tab);
}
