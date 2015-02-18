/*
** replace_aliases.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Thu May  6 00:37:31 2010 cerisier mickael
** Last update Sun May 23 23:00:58 2010 vivien botton
*/

#include <stdlib.h>
#include "builtins.h"
#include "ergonomy.h"
#include "parser.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "gl_vars.h"

extern t_global	gl_global;

static void		free_lock(t_loop *loop)
{
  t_loop	*cpy;
  t_loop	*savenext;

  cpy = loop;
  while (cpy)
    {
      savenext = cpy->next;
      cpy->alias->modify = 0;
      free(cpy);
      cpy = savenext;
    }
}

static void		replace_to_end(int *do_loop,
			t_token **cpy_tok, t_loop **loop)
{
  t_alias	*cpy_alias;

  cpy_alias = gl_global.gl_alias;
  while (cpy_alias)
    {
      if (cpy_alias->value[0])
	{
	  *do_loop = 0;
	  if (modify_list(cpy_tok, cpy_alias, loop))
	    {
	      *do_loop = 1;
	      cpy_alias = gl_global.gl_alias;
	    }
	  else
	    cpy_alias = cpy_alias->next;
	}
      else
	cpy_alias = cpy_alias->next;
    }
}

void		add_option_alias(char *option, t_token **pos)
{
  t_token	*new;
  char		*res;

  if ((*pos)->type == T_COMMAND)
    {
      res = my_strcat(NO_FREE, (*pos)->data, " ", option, NULL);
      if ((*pos)->free)
	free((*pos)->data);
      (*pos)->data = res;
      (*pos)->free = 1;
      free(option);
    }
  else
    {
      new = xmalloc(sizeof(*new));
      new->type = T_COMMAND;
      new->data = option;
      new->next = (*pos)->next;
      new->free = 1;
      (*pos)->next = new;
    }
}

void		replace_aliases(t_token **tokens)
{
  t_token	*cpy_tok;
  int		do_loop;
  t_loop	*loop;

  loop = NULL;
  do_loop = 1;
  if (do_loop)
    {
      cpy_tok = *tokens;
      do_loop = 0;
      while (cpy_tok)
	{
	  replace_to_end(&do_loop, &cpy_tok, &loop);
	  cpy_tok = cpy_tok->next;
	}
    }
  free_lock(loop);
}
