/*
** move_red.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue May  4 12:24:21 2010 gianni castellani
** Last update Sun May 23 16:03:01 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/strings.h"
#include "lib_includes/xfunctions.h"

t_token		*create_command(t_token *token, int i)
{
  t_token	*ret;
  t_token	*next;

  next = token->next;
  ret = xmalloc(sizeof(*ret));
  ret->type = T_COMMAND;
  ret->data = NULL;
  if (i)
    ret->next = token;
  else
    {
      token->next = ret;
      ret->next = next;
    }
  return (ret);
}

void		concate_command(t_token **token, t_token **prev_cmd,
				t_token *prev, t_token **cur)
{
  t_token	*temp;
  int		i;

  i = (*prev_cmd == *token  && is_redir((*prev_cmd)->type)) ? 1 : 0;
  if ((*prev_cmd)->type != T_COMMAND)
    *prev_cmd = create_command(*prev_cmd, i);
  if (i)
    *token = *prev_cmd;
  if (!(*prev_cmd)->data)
    (*prev_cmd)->data = my_strdup((*cur)->data);
  else
    (*prev_cmd)->data = my_strcat(((*prev_cmd)->free) ? FIRST_FREE : NO_FREE,
				  (*prev_cmd)->data, " ", (*cur)->data, NULL);
  (*prev_cmd)->free = 1;
  temp = *cur;
  prev->next = (*cur)->next;
  *cur = (*cur)->next;
  if (temp->free)
    free(temp->data);
  free(temp);
}

void		move_red(t_token **token)
{
  t_token	*cur;
  t_token	*prev_cmd;
  t_token	*prev;

  cur = *token;
  prev = cur;
  prev_cmd = prev;
  while (cur)
    {
      if (cur->type == T_COMMAND && is_redir(prev->type))
	concate_command(token, &prev_cmd, prev, &cur);
      else
	{
	  if (!is_redir(cur->type))
	    prev_cmd = cur;
	  prev = cur;
	  cur = cur->next;
	}
    }
}
