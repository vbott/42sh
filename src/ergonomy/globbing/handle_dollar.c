/*
** handle_dollar.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 15:16:20 2010 gianni castellani
** Last update Sat May  1 16:15:39 2010 mickael cerisier
*/

#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"
#include "lib_includes/env.h"

static int	is_legal(char c)
{
  if (c >= 'a' && c <= 'z')
    return (1);
  if (c >= 'A' && c <= 'Z')
    return (1);
  if (c >= '0' && c <= '9')
    return (1);
  if (c == '_' || c == '?')
    return (1);
  return (0);
}

static void	no_var(char save, char **var, int i, int begin)
{
  char		*name;

  (*var)[i] = save;
  (*var)[begin] = '\0';
  if ((*var)[0] != '\0')
    {
      name = my_strdup(*var);
      *var = my_strcat(FIRST_FREE, name, &((*var)[i]), NULL);
    }
  else
    *var = my_strdup(&((*var)[i]));
}

static void	insert_var(char **var, int begin, int value)
{
  int		i;
  char		save;
  char		*name;
  char		*mem;

  i = begin + 1;
  mem = *var;
  while ((*var)[i] && is_legal((*var)[i]))
    i++;
  save = (*var)[i];
  (*var)[i] = '\0';
  name = my_getenv(&(*var)[begin + 1]);
  if (name == NULL)
    {
      no_var(save, var, i, begin);
      if (value)
	free(mem);
      return ;
    }
  (*var)[begin] = '\0';
  (*var)[i] = save;
  *var = my_strcat(NO_FREE, *var, name, &((*var)[i]), NULL);
  if (value)
    free(mem);
}

static int	globbing_dollar(int *i, int *value, char *c, char **buff)
{
  if ((*buff)[*i] == '\\')
    (*i)++;
  else if (*c == '\0' && ((*buff)[*i] == '\'' || (*buff)[*i] == '`'))
    *c = (*buff)[*i];
  else if (*c == (*buff)[*i])
    *c = '\0';
  else if (*c == '\0' && (*buff)[*i] == '$')
    {
      insert_var(buff, *i, *value);
      *value = 1;
    }
  return (0);
}

int		handle_dollar(char **buff)
{
  int		i;
  int		value;
  char		c;

  i = 0;
  value = 0;
  c = '\0';
  if (*buff == NULL)
    return (-1);
  while ((*buff)[i] != '\0')
    {
      if (globbing_dollar(&i, &value, &c, buff) == -1)
	return (-1);
      if ((*buff)[i] != '\0')
	i++;
    }
  return (value);
}
