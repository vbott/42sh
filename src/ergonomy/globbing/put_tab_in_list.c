/*
** tab_in_list.c for 42sh in /u/all/cerisi_m/cu/rendu/svn/42sh/current
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sat May  1 17:38:42 2010 mickael cerisier
** Last update Sat May  1 17:40:51 2010 mickael cerisier
*/

#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

t_list		*put_tab_in_list(char **tab, t_list *list)
{
  int		i;
  t_list	*new;

  if (tab == NULL)
    {
      new = xmalloc(sizeof(*new));
      new->next = list;
      new->data = NULL;
      return (new);
    }
  i = 0;
  while (tab[i] != 0)
    {
      new = xmalloc(sizeof(*new));
      new->next = list;
      new->data = tab[i];
      list = new;
      i++;
    }
  free(tab);
  return (list);
}
