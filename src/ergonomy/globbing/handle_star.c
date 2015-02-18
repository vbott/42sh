/*
** handle_star.c for 42sh in /u/all/bereng_p/cu/rendu/c/proj/42sh/ergonomy
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Fri Apr  2 14:04:32 2010 philippe berenguel
** Last update Sat May  1 12:44:55 2010 mickael cerisier
*/

#include <sys/types.h>
#include <stdlib.h>
#include <dirent.h>
#include "globbing.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

int		char_find_str(char *str, char *c)
{
  int		i;
  char		s;

  i = 0;
  s = '\0';
  while (str[i] != '\0')
    {
      if (str[i] == '\\' && s != '\'')
        i++;
      else if (s == '\0' && (str[i] == '"' || str[i] == '\'' || str[i] == '`'))
        s = str[i];
      else if (s == str[i])
        s = '\0';
      else if (s == '\0' && char_find(c, str[i]) != -1)
	return (i);
      if (str[i] != '\0')
	i++;
    }
  return (-1);
}

static t_list	*handle_globbing(char *str, t_list *list, int env, int mode)
{
  int		tilde;
  t_list	*mem;

  tilde = handle_tilde(&str, mode);
  if (!tilde && !mode)
    str = my_strdup(str);
  if (char_find_str(str, "*[?") != -1)
    {
      mem = list;
      if (env == WITHOUT_ENV)
	list = add_list_star(str, list, 0);
      else
	list = add_list_env(str, list);
      if (mem == list)
	list = add_list(str, list);
      else
	free(str);
    }
  else
    list = add_list(str, list);
  return (list);
}

static t_list	*handle_braces(char *str, t_list *list, int *nb, int env)
{
  int		i;
  char		*mem;
  char		*begin;
  char		*middle;
  char		**tab;

  begin = my_strcdup(str, '{');
  middle = my_strcdup(&str[nb[0] + 1], '}');
  tab = my_explode(middle, ',');
  i = 0;
  while (tab[i])
    {
      mem = my_strcat(NO_FREE, begin, tab[i], &str[nb[1] + 1], 0);
      list = handle_globbing(mem, list, env, 1);
      i++;
    }
  free(begin);
  free(middle);
  free(tab);
  return (list);
}

t_list		*handle_star_list(char *str, t_list *list, int env)
{
  int		nb[2];

  nb[0] = char_find_str(str, "{");
  nb[1] = char_find_str(str, "}");
  if (nb[0] != -1 && nb[1] != -1)
    list = handle_braces(str, list, nb, env);
  else
    list = handle_globbing(str, list, env, 0);
  return (list);
}

char		**handle_star(char **args, int env)
{
  int		i;
  t_list	*list;

  if (!args)
    return (NULL);
  i = 0;
  list = 0;
  while (args[i])
    {
      if (char_find(args[i], '`') != -1)
	list = handle_backquote(args[i], list, env);
      else
	list = handle_star_list(args[i], list, env);
      i++;
    }
  return (put_list_in_tab(list));
}
