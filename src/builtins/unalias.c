/*
** unalias.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 19 19:14:00 2010 cerisier mickael
** Last update Wed May 19 19:14:00 2010 cerisier mickael
*/

#include <stdlib.h>
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "builtins.h"
#include "gl_vars.h"

extern t_global	gl_global;

static void	delete_alias(t_alias *current, t_alias *previous)
{
  if (previous)
    {
      previous->next = current->next;
      free(current->assign);
      free(current->value);
      free(current);
    }
  else
    {
      gl_global.gl_alias = gl_global.gl_alias->next;
      free(current->assign);
      free(current->value);
      free(current);
    }
}

static void	not_found(char *assign, int *return_val)
{
  my_putstr("unalias: ");
  my_putstr(assign);
  my_putstr(": not found.\n");
  *return_val = EXIT_FAILURE;
}

int		unalias_usage(char **args)
{
  t_alias	*cpy;
  t_alias	*save;

  cpy = gl_global.gl_alias;
  if (!args[1])
    {
      my_putstr("unalias: usage: unalias [-a] name [name ...]\n");
      return (1);
    }
  else if (!my_strcmp(args[1], "-a"))
    {
      while (cpy)
	{
	  save = cpy->next;
	  delete_alias(cpy, NULL);
	  cpy = save;
	}
      return (1);
    }
  return (0);
}

int		unalias(char **args)
{
  t_alias	*cpy;
  t_alias	*previous;
  int		i;
  int		return_val;

  return_val = EXIT_SUCCESS;
  if (unalias_usage(args))
    return (EXIT_FAILURE);
  i = 1;
  while (args[i])
    {
      previous = NULL;
      cpy = gl_global.gl_alias;
      while (cpy && my_strcmp(cpy->assign, args[i]))
	{
	  previous = cpy;
	  cpy = cpy->next;
	}
      if (cpy)
	delete_alias(cpy, previous);
      else
	not_found(args[i], &return_val);
      i++;
    }
  return (return_val);
}
