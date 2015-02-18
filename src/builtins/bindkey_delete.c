/*
** bindkey_delete.c for 42sh in /home/shotgun/svn/42sh/current/src/builtins
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed Apr 28 12:23:07 2010 cerisier mickael
** Last update Mon May 17 18:24:32 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

static void		free_bind_node(t_bindkey *current)
{
  if (current->exec)
    free(current->exec);
  free(current->ch);
  free(current);
}

void			bk_handledelete(char *str)
{
  extern t_global	gl_global;
  t_bindkey		*current;
  t_bindkey		*prev;

  current = gl_global.gl_bindkey;
  prev = current;
  while (current && my_strcmp(str, current->ch))
    {
      prev = current;
      current = current->next;
    }
  if (current && current == prev)
    {
      gl_global.gl_bindkey = gl_global.gl_bindkey->next;
      free_bind_node(current);
    }
  else if (current)
    {
      prev->next = current->next;
      free_bind_node(current);
    }
}
