/*
** unset.c for 42sh in /home/snap/projects/42sh/current/src/builtins
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Tue May 11 18:30:13 2010 botton vivien
** Last update Wed May 12 10:24:47 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "parser.h"
#include "builtins.h"
#include "termcaps.h"
#include "execution.h"
#include "builtins.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"

extern t_global	gl_global;

void		free_local(void)
{
  t_local	*cpy;
  t_local	*next;

  cpy = gl_global.gl_local;
  while (cpy)
    {
      next = cpy->next;
      free(cpy->name);
      free(cpy->value);
      free(cpy);
      cpy = next;
    }
}

static void	free_node(t_local *cpy, t_local *old, t_local *next)
{
  free(cpy->name);
  free(cpy->value);
  free(cpy);
  if (old)
    old->next = next;
  else
    gl_global.gl_local = next;
}

int		unset(char **cmd)
{
  int		i;
  t_local	*cpy;
  t_local	*old;
  t_local	*next;

  my_unsetenv(cmd);
  cpy = gl_global.gl_local;
  old = NULL;
  while (cpy)
    {
      next = cpy->next;
      i = 1;
      while (cmd[i] && my_strcmp(cmd[i], cpy->name))
	i++;
      if (cmd[i])
	free_node(cpy, old, next);
      else
	old = cpy;
      cpy = next;
    }
  return (EXIT_SUCCESS);
}
