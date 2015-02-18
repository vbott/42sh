/*
** my_sort_list.c for minishell in /u/all/cerisi_m/cu/rendu/c/minishell
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Sun Jan 10 14:20:18 2010 mickael cerisier
** Last update Sun Jan 10 18:27:44 2010 mickael cerisier
*/

#include "globbing.h"
#include "lib_includes/strings.h"

void		my_sort_list_end(t_list **begin, t_list *end)
{
  t_list	*tri;
  t_list	*mem;

  mem = *begin;
  while (mem && mem != end)
    {
      tri = mem->next;
      while (tri != end)
        {
	  if (my_strcmp(mem->data, tri->data) < 0)
	    my_swap((int**)&(mem->data), (int**)&(tri->data));
          tri = tri->next;
        }
      mem = mem->next;
    }
}
