/*
** handle_star_env.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:44:25 2010 cerisier mickael
** Last update Wed Apr 28 11:44:25 2010 cerisier mickael
*/

#include <stdlib.h>
#include "globbing.h"
#include "builtins.h"
#include "lib_includes/strings.h"

extern char	**gl_env;

char		*before_chara(char *str, char c)
{
  int		i;

  i = 0;
  while (str[i])
    {
      if (str[i] == c)
	{
	  str[i] = '\0';
	  return (str);
	}
      i++;
    }
  return (NULL);
}

void		check_star_unsetenv(char *var_env, char *str, int *have_unset)
{
  char		*tab[3];
  char		stock;
  int		j;

  tab[0] = "unsetenv";
  tab[2] = 0;
  j = 0;
  while (var_env[j] && var_env[j] != '=')
    j++;
  if (var_env[j] && var_env[j] == '=')
    {
      stock = var_env[j];
      var_env[j] = '\0';
    }
  if (match(var_env, str))
    {
      tab[1] = var_env;
      if (tab[1])
	{
	  *have_unset = 1;
	  my_unsetenv(tab);
	}
    }
  free(var_env);
}

int	       	star_unsetenv(char *str)
{
  int  		i;
  int		have_unset;
  int		match_once;

  i = 0;
  have_unset = 0;
  match_once = 0;
  while (gl_env[i])
    {
      check_star_unsetenv(my_strdup(gl_env[i]), str, &have_unset);
      i++;
      if (have_unset)
	{
	  i = 0;
	  have_unset = 0;
	  match_once = 1;
	}
    }
  return (match_once);
}
