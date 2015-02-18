/*
** my_sort_list.c for my_sort_list in /u/all/cerisi_m/cu/rendu/piscine/Jour_11
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Tue Oct 20 18:49:08 2009 mickael cerisier
** Last update Wed Oct 21 16:45:50 2009 mickael cerisier
*/

#include "global.h"
#include "lib_includes/strings.h"

int		my_sort_list(t_list **begin)
{
  t_list	*tri;
  t_list	*mem;

  mem = *begin;
  while (mem != 0)
    {
      tri = mem->next;
      while (tri != 0)
        {
	  if (my_strcmp(mem->data, tri->data) > 0)
	    my_swap((int**)&(mem->data), (int**)&(tri->data));
          tri = tri->next;
        }
      mem = mem->next;
    }
  return (0);
}
