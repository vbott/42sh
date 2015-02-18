/*
** create_tree.c for 42sh in /u/epitech_2014/bereng_p/public/42group/test_backup/parser
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun Mar 14 11:01:58 2010 gianni castellani
** Last update Sun May 23 21:23:14 2010 vivien botton
*/

#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "parser.h"
#include "lib_includes/aff.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

const t_prioop	gl_prio[] =
  {
    {1, ";", T_SEMICOLON, 1, semicolon_error},
    {2, "&&", T_AND, 2, and_or_error},
    {1, "&", T_BACKGROUND, 1, background_error},
    {2, "||", T_OR, 2, and_or_error},
    {2, "<<", T_DLRED, 3, lred_error},
    {1, "<", T_LRED, 3, lred_error},
    {1, "|", T_PIPE, 4, pipe_error},
    {3, ">>&", T_ANDDRED, 3, rred_error},
    {2, ">>", T_DRRED, 5, rred_error},
    {2, ">&", T_ANDRED, 5, rred_error},
    {1, ">", T_RRED, 5, rred_error},
    {1, "(", T_LPARENTH, 6, lparenth_error},
    {1, ")", T_RPARENTH, 7, rparenth_error},
    {0, 0, 0, 0, 0}
  };

void		put_priority(t_token *retmp[2], t_token *prev,
			     t_token *token, int priority[2], int prio_parenth)
{
  int		cpt2;

  cpt2 = 0;
  while (gl_prio[cpt2].type != 0 && token->type != gl_prio[cpt2].type)
    cpt2++;
  if (gl_prio[cpt2].type != 0
      && (priority[0] == -1 || priority[1] > prio_parenth ||
	  ((priority[0] > gl_prio[cpt2].prio ||
	    ((gl_prio[cpt2].type == T_AND || gl_prio[cpt2].type == T_OR)
	     && priority[0] >= gl_prio[cpt2].prio))
	   && priority[1] == prio_parenth)))
    {
      retmp[1] = prev;
      retmp[0] = token;
      priority[0] = gl_prio[cpt2].prio;
      priority[1] = prio_parenth;
    }
}

t_token		*find_priority(t_token *token)
{
  int		priority[2];
  int		prio_parenth;
  t_token	*prev;
  t_token	*retmp[2];

  prev = NULL;
  retmp[0] = NULL;
  retmp[1] = NULL;
  priority[0] = -1;
  prio_parenth = 0;
  while (token)
    {
      put_priority(retmp, prev, token, priority, prio_parenth);
      if (token->type == T_LPARENTH)
	prio_parenth++;
      else if (token->type == T_RPARENTH)
	prio_parenth--;
      prev = token;
      token = token->next;
    }
  if (retmp[1])
    retmp[1]->next = NULL;
  return (retmp[0]);
}

static t_tree	*create_command_node(t_tree *ret, t_token *token)
{
  ret->type = T_COMMAND;
  ret->free = token->free;
  ret->data = token->data;
  ret->right = NULL;
  ret->left = NULL;
  free(token);
  return (ret);
}

t_tree		*create_tree(t_token *token)
{
  t_tree	*ret;
  t_token	*node;

  if (!token)
    return (NULL);
  node = find_priority(token);
  ret = xmalloc(sizeof(*ret));
  if (!node)
    return (create_command_node(ret, token));
  if (node->type == T_LPARENTH)
    return (create_parenth_node(ret, token));
  ret->free = node->free;
  ret->type = node->type;
  ret->data = node->data;
  if (node != token)
    ret->left = create_tree(token);
  else
    ret->left = NULL;
  token = node->next;
  free(node);
  ret->right = create_tree(token);
  return (ret);
}
