/*
** create_parenth_node.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Fri May 14 15:28:18 2010 gianni castellani
** Last update Fri May 14 16:52:10 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"

t_tree		*create_parenth_node(t_tree *ret, t_token *token)
{
  t_token	*cur;
  t_token	*prev;
  t_token	*tok;
  int		nb;

  nb = 0;
  cur = token->next;
  tok = cur;
  prev = cur;
  free(token);
  while (cur && (nb != 0 || cur->type != T_RPARENTH))
    {
      nb += (cur->type == T_LPARENTH) ? 1 : (cur->type == T_RPARENTH) ? -1 : 0;
      prev = cur;
      cur = cur->next;
    }
  free(cur);
  prev->next = NULL;
  ret->type = T_LPARENTH;
  ret->data = NULL;
  ret->free = 0;
  ret->right = NULL;
  ret->left = create_tree(tok);
  return (ret);
}
