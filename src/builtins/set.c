/*
** local.c for 42sh in /home/snap/projects/42sh/current
** 
** Made by botton vivien
** Login   <botton_v@epitech.net>
** 
** Started on  Tue May 11 15:35:53 2010 botton vivien
** Last update Wed May 12 10:25:03 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/aff.h"
#include "parser.h"
#include "builtins.h"
#include "termcaps.h"
#include "execution.h"
#include "builtins.h"
#include "jobs.h"
#include "gl_vars.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

extern t_global	gl_global;

void		aff_local(void)
{
  t_local	*cpy;

  cpy = gl_global.gl_local;
  while (cpy)
    {
      my_putstr(cpy->name);
      my_putstr(" ");
      my_putstr(cpy->value);
      my_putstr("\n");
      cpy = cpy->next;
    }
}

char		*my_getlocal(const char *name)
{
  t_local	*cpy;

  cpy = gl_global.gl_local;
  while (cpy)
    {
      if (!my_strcmp(name, cpy->name))
	return (cpy->value);
      cpy = cpy->next;
    }
  return (NULL);
}

void		add_local(const char *name, const char *value)
{
  t_local	*cpy;
  t_local	*new;

  cpy = gl_global.gl_local;
  while (cpy && cpy->next && my_strcmp(name, cpy->name))
    cpy = cpy->next;
  if (cpy && !my_strcmp(name, cpy->name))
    {
      free(cpy->value);
      cpy->value = my_strdup(value);
    }
  else
    {
      new = xmalloc(sizeof(*new));
      new->name = my_strdup(name);
      new->value = my_strdup(value);
      new->next = 0;
      if (cpy)
	cpy->next = new;
      else
	gl_global.gl_local = new;
    }
}

void		set_multi(char **cmd)
{
  int		i;
  int		pos;
  char		*name;
  char		*value;

  i = 1;
  while (cmd[i])
    {
      pos = char_find(cmd[i], '=');
      if (pos == -1)
	value = NULL;
      else
	{
	  cmd[i][pos] = '\0';
	  value = &(cmd[i][pos + 1]);
	}
      name = cmd[i];
      add_local(name, value);
      i++;
    }
}

int		set(char **cmd)
{
  if (!cmd[1])
    {
      aff_local();
      return (aff_env(cmd));
    }
  else
    set_multi(cmd);
  return (EXIT_SUCCESS);
}
