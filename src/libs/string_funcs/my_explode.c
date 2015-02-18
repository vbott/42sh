/*
** my_explode.c for 42sh in /u/all/bereng_p/cu/public/42group/current/libs/string_funcs
** 
** Made by philippe berenguel
** Login   <bereng_p@epitech.net>
** 
** Started on  Sun Mar 14 11:21:17 2010 philippe berenguel
** Last update Fri Apr  2 13:46:28 2010 philippe berenguel
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"

static int	my_isalphanumeric(char c, char s)
{
  if (c == '\0' || c == s || (s == ' ' && c == '\t'))
    return (0);
  else
    return (1);
}

static char	**my_write_tab(char *str, int taille, int lenmalloc, char c)
{
  int		i;
  int		e;
  int		a;
  char		**tab;

  i = 0;
  e = 1;
  a = 0;
  if (!(tab = xmalloc((lenmalloc + 1) * sizeof(char*))))
    return (0);
  while (i < taille)
    {
      if (e == 1 && my_isalphanumeric(str[i], c))
        {
          tab[a] = &str[i];
          a++;
          e = 0;
        }
      if (str[i] == '\0')
        e = 1;
      i++;
    }
  tab[a] = 0;
  return (tab);
}

static int	add_null(int *u, char *str, char c, char s)
{
  int		mem;

  mem = 0;
   if (!s && !my_isalphanumeric(*str, c))
     {
       if (!(*u))
	 {
	   *str = '\0';
	   mem = 1;
	 }
       *u = 1;
     }
   else
     *u = 0;
   return (mem);
}

char		**my_explode(char *str, char c)
{
  int		i;
  int		e;
  int		u;
  char		s;

  if (str == NULL)
    return (NULL);
  i = 0;
  e = 1;
  u = 0;
  s = '\0';
  while (str[i] != '\0')
    {
      if (str[i] == '\\')
	i += (str[i + 1] != '\0') ? 1 : 0;
      else if (s == '\0' && (str[i] == '"' || str[i] == '\'' || str[i] == '`'))
	s = str[i];
      else if (s == str[i])
	s = 0;
      else
	e += add_null(&u, &str[i], c, s);
      i++;
    }
  return (my_write_tab(str, i, e, c));
}
