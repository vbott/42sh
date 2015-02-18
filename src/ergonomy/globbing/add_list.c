/*
** add_list.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:36:11 2010 cerisier mickael
** Last update Sat May  1 13:38:10 2010 mickael cerisier
*/

#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "globbing.h"

void		decal_one(char *str)
{
  int		i;

  i = 0;
  while (str[i] != '\0')
    {
      str[i] = str[i + 1];
      i++;
    }
}

t_list		*add_list(char *str, t_list *list)
{
  int		i;
  char		s;
  t_list	*newlist;

  i = 0;
  s = '\0';
  while (str[i] != '\0')
    if (s == '\0' && (str[i] == '"' || str[i] == '\''))
      {
	s = str[i];
	decal_one(&str[i]);
      }
    else if (str[i] == '\\' && s == '\0')
      decal_one(&str[i++]);
    else if (str[i] == s)
      {
	s = '\0';
	decal_one(&str[i]);
      }
    else
      i++;
  newlist = xmalloc(sizeof(*newlist));
  newlist->data = str;
  newlist->next = list;
  return (newlist);
}

static t_list	*add_list_star2(t_list *list, char *str, char *path, DIR *dir)
{
  int		i;
  char		*tmp;
  char		*strm;
  struct dirent	*dp;

  i = char_find(str, '/');
  if (i == -1)
    i = my_strlen(str);
  strm = my_strndup(str, i);
  while ((dp = xreaddir(dir)))
    {
      if ((dp->d_name[0] != '.' || strm[0] == '.')
	  && match(dp->d_name, strm) > 0)
	{
	  tmp = get_temp(dp->d_name, path);
	  tmp = my_strcat(FIRST_FREE, tmp, &str[i], 0);
	  if (char_find_str(&str[i], "*[?") != -1)
	    list = add_list_star(tmp, list, 1);
	  else if (!access(tmp, F_OK))
	    list = add_list(tmp, list);
	}
    }
  free(strm);
  return (list);
}

t_list		*add_list_star(char *str, t_list *list, int mode)
{
  char		*path;
  int		i;
  t_list	*begin;
  DIR		*dir;

  path = get_path(str, &i);
  dir = xopendir(path);
  begin = list;
  if (dir != NULL)
    {
      list = add_list_star2(list, &str[i], path, dir);
      xclosedir(dir);
    }
  if (mode)
    free(str);
  free(path);
  my_sort_list_end(&list, begin);
  return (list);
}
