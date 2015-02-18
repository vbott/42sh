/*
** my_size_list.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 13:35:28 2010 philippe berenguel
** Last update Fri Apr  2 13:35:29 2010 philippe berenguel
*/

#include "globbing.h"

int		my_size_list(t_list *list)
{
  int		i;

  i = 0;
  while (list)
    {
      list = list->next;
      i++;
    }
  return (i);
}
