/*
** modify_list.c for 42sh in /home/shotgun/svn/42sh/current
** 
** Made by cerisier mickael
** Login   <cerisi_m@epitech.net>
** 
** Started on  Wed May 19 19:13:42 2010 cerisier mickael
** Last update Wed May 19 19:13:42 2010 cerisier mickael
*/

#include <stdlib.h>
#include "builtins.h"
#include "ergonomy.h"
#include "parser.h"
#include "builtins.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"
#include "gl_vars.h"

extern t_global	gl_global;

static void	dup_values(t_token **token, t_token *pos)
{
  t_token	*cpy;

  cpy = *token;
  while (cpy->next)
    {
      if (cpy->data && cpy->free == 0)
        {
          cpy->data = my_strdup(cpy->data);
          cpy->free = 1;
        }
      cpy = cpy->next;
    }
  if (cpy->free == 0)
    {
      cpy->data = my_strdup(cpy->data);
      cpy->free = 1;
    }
  cpy->next = pos->next;
}

static void		add_link_alias(char *value, t_token **pos, char *args)
{
  t_token	*token;
  t_token	*add_args;
  char		*dup_value;

  dup_value = my_strdup(value);
  token = create_token_list(dup_value);
  add_args = token;
  while (add_args->next)
    add_args = add_args->next;
  if (args)
    add_option_alias(args, &add_args);
  dup_values(&token, *pos);
  if ((*pos)->free == 1)
    free((*pos)->data);
  (*pos)->next = token->next;
  (*pos)->data = token->data;
  (*pos)->type = token->type;
  (*pos)->free = 1;
  free(token);
  free(dup_value);
}

void		lock_alias(t_loop **loop, t_alias *alias, t_token *token)
{
  t_loop	*cpy_loop;
  t_loop	*new;

  cpy_loop = *loop;
  new = xmalloc(sizeof(*new));
  new->alias = alias;
  if (token->next)
    new->token = token->next;
  else
    new->token = 0;
  new->next = NULL;
  alias->modify = 1;
  if (!cpy_loop)
    *loop = new;
  else
    {
      while (cpy_loop->next)
        cpy_loop = cpy_loop->next;
      cpy_loop->next = new;
    }
}

static void	unlock_alias(t_loop *loop, t_token *token)
{
  t_loop	*cpy;
  t_loop	*savenext;
  t_loop	*prev;

  cpy = loop;
  prev = NULL;
  while (cpy)
    {
      savenext = cpy->next;
      if (cpy->token == token)
        cpy->alias->modify = 0;
      prev = cpy;
      cpy = savenext;
    }
}

int		modify_list(t_token **cpy_tok,
			    t_alias *alias, t_loop **loop)
{
  int		len;
  char		*options;

  options = NULL;
  len = my_strlen(alias->assign);
  unlock_alias(*loop, *cpy_tok);
  if (my_strncmp(alias->assign, (*cpy_tok)->data, len)
      && (*cpy_tok)->type == T_COMMAND && alias->modify == 0
      && (!(*cpy_tok)->data[len] || (*cpy_tok)->data[len] == ' '))
    {
      if ((*cpy_tok)->data[len] && (*cpy_tok)->data[len] == ' '
	  && (*cpy_tok)->data[len + 1])
	options = my_strdup(&(*cpy_tok)->data[len]);
      if (*cpy_tok && (*cpy_tok)->type == T_COMMAND)
	lock_alias(loop, alias, *cpy_tok);
      add_link_alias(alias->value, cpy_tok, options);
      return (1);
    }
  return (0);
}
