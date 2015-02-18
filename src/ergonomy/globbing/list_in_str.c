/*
** list_in_str.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:36:24 2010 cerisier mickael
** Last update Wed Apr 28 11:36:25 2010 cerisier mickael
*/

#include <stdlib.h>
#include "globbing.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static void	cpy_list_in_str(char *str, t_list *list)
{
  int		i;
  int		e;
  t_list	*mem;

  i = 0;
  while (list)
    {
      e = 0;
      if (i != 0)
        str[i++] = ' ';
      while (list->data[e] != '\0')
        str[i++] = list->data[e++];
      mem = list;
      list = list->next;
      free(mem->data);
      free(mem);
    }
  str[i] = '\0';
}

char		*list_in_str(t_list *list)
{
  int		size;
  char		*str;
  t_list	*mem;

  if (!list)
    return (NULL);
  size = 0;
  mem = list;
  while (mem)
    {
      size += my_strlen(mem->data) + 1;
      mem = mem->next;
    }
  str = xmalloc(size * sizeof(*str));
  cpy_list_in_str(str, list);
  return (str);
}
