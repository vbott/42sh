/*
** function_star.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:16:07 2010 gianni castellani
** Last update Thu Apr  1 15:16:08 2010 gianni castellani
*/

#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "globbing.h"

char		*get_path(char *str, int *size)
{
  int		i;

  i = char_find_str(str, "*[?") - 1;
  while (i >= 0 && str[i] != '/')
    i--;
  if (i == -2)
    *size = 0;
  else
    *size = i + 1;
  if (i < 0)
    return (my_strdup("."));
  else
    return (my_strndup(str, i + 1));
}

char		*get_temp(char *name, char *path)
{
  if (path[0] == '.' && path[1] == '\0')
    return (my_strdup(name));
  else
    return (my_strcat(NO_FREE, path, name, 0));
}

char		**put_list_in_tab(t_list *list)
{
  int		i;
  char		**tab;
  t_list	*mem;

  i = my_size_list(list);
  tab = xmalloc((i + 1) * sizeof(*tab));
  tab[i--] = 0;
  while (list)
    {
      mem = list;
      tab[i] = list->data;
      list = list->next;
      free(mem);
      i--;
    }
  return (tab);
}
