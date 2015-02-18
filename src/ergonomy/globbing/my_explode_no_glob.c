/*
** my_explode.c for colle-s3-2 in /u/epitech_2014/danino_n/public/colle
** 
** Made by mickael cerisier
** Login   <cerisi_m@epitech.net>
** 
** Started on  Mon May 10 20:14:53 2010 mickael cerisier
** Last update Mon May 10 21:46:21 2010 mickael cerisier
*/

#include <sys/types.h>
#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

static int	my_isalphanumeric(char c)
{
  if (c == '\0' || c == '\t' || c == ' ' || c == '\n')
    return (0);
  else
    return (1);
}

static char	**my_write_tab(char *str, int taille, int lenmalloc)
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
      if (e == 1 && my_isalphanumeric(str[i]))
        {
          tab[a] = my_strdup(&str[i]);
          a++;
          e = 0;
        }
      if (str[i] == '\0')
        e = 1;
      i++;
    }
  tab[a] = NULL;
  return (tab);
}

char		**my_explode_no_glob(char *str)
{
  int		i;
  int		e;
  int		u;

  if (str == NULL)
    return (NULL);
  i = 0;
  e = 1;
  u = 0;
  while (str[i] != '\0')
    {
      if (!my_isalphanumeric(str[i]))
	{
	  if (!u)
	    {
	      str[i] = '\0';
	      e++;
	    }
	  u = 1;
	}
      else
	u = 0;
      i++;
    }
  return (my_write_tab(str, i, e));
}
