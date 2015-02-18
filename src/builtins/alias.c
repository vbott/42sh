/*
** alias.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 11:31:43 2010 cerisier mickael
** Last update Wed Apr 28 11:31:43 2010 cerisier mickael
*/

#include <unistd.h>
#include <stdlib.h>
#include "parser.h"
#include "builtins.h"
#include "globbing.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "lib_includes/aff.h"
#include "lib_includes/free.h"
#include "gl_vars.h"

extern t_global	gl_global;

int		exist(char *assign, char *completevalue)
{
  t_alias	*cpy;

  cpy = gl_global.gl_alias;
  while (cpy)
    {
      if (!my_strcmp(cpy->assign, assign))
	{
	  free(cpy->assign);
	  free(cpy->value);
	  cpy->assign = my_strdup(assign);
	  cpy->value = my_strdup(completevalue);
	  cpy->modify = 0;
	  return (1);
	}
      cpy = cpy->next;
    }
  return (0);
}

void		set_alias(char *value, int i)
{
  t_alias	*cpy;
  t_alias	*alias;

  value[i] = '\0';
  if (exist(value, &value[i + 1]))
    return ;
  cpy = gl_global.gl_alias;
  alias = xmalloc(sizeof(*alias));
  alias->assign = my_strdup(value);
  alias->value = my_strdup(&value[i + 1]);
  alias->modify = 0;
  alias->next = NULL;
  if (!gl_global.gl_alias)
    gl_global.gl_alias = alias;
  else
    {
      while (cpy->next)
	cpy = cpy->next;
      cpy->next = alias;
    }
}

void		aff_all_aliases(void)
{
  t_alias	*cpy;

  cpy = gl_global.gl_alias;
  while (cpy)
    {
      my_putstr(cpy->assign);
      my_putstr("='");
      my_putstr(cpy->value);
      my_putstr("'\n");
      cpy = cpy->next;
    }
}

void		aff_alias(char *name, int *return_val)
{
  t_alias	*cpy;

  cpy = gl_global.gl_alias;
  while (cpy && my_strcmp(cpy->assign, name))
    cpy = cpy->next;
  if (cpy && !my_strcmp(cpy->assign, name))
    {
      my_putstr(cpy->assign);
      my_putstr("='");
      my_putstr(cpy->value);
      my_putstr("'\n");
    }
  else
    {
      my_putstr("alias: ");
      my_putstr(name);
      my_putstr(": not found.\n");
      *return_val = EXIT_FAILURE;
    }
}

int		my_alias(char **cmd)
{
  int		i;
  int		pos;
  int		return_val;

  i = 1;
  return_val = EXIT_SUCCESS;
  if (cmd[1] == NULL)
    aff_all_aliases();
  while (cmd[i])
    {
      if ((pos = char_find(cmd[i], '=')) != -1)
	set_alias(cmd[i], pos);
      else
	aff_alias(cmd[i], &return_val);
      i++;
    }
  return (return_val);
}
