/*
** switch_red.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Wed May  5 17:45:58 2010 gianni castellani
** Last update Wed May 19 20:22:36 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"

static int	count_parenth(t_token *token, int i, int *mem, int mode)
{
  if (token->type == T_RPARENTH)
    {
      if (*mem == i)
	return (1);
      (*mem)--;
    }
  else if (token->type == T_LPARENTH)
    {
      if (*mem == i)
	{
	  if (mode == T_LRED)
	    swap_lred(&(token->next), 0);
	  else
	    swap_rred(&(token->next), 0);
	}
      (*mem)++;
    }
  return (0);
}

static void	swap_lred_token(t_token **token, t_token *cur,
				t_token *prev, t_token *prev_cur)
{
  if (prev == NULL && prev_cur != prev)
    {
      prev_cur->next = cur->next;
      cur->next = *token;
      *token = cur;
    }
  else if (prev != NULL)
    {
      prev_cur->next = cur->next;
      cur->next = prev->next;
      prev->next = cur;
    }
}

void		swap_lred(t_token **token, int i)
{
  int		mem;
  t_token	*cur;
  t_token	*prev;
  t_token	*prev_cur;

  prev = NULL;
  prev_cur = NULL;
  cur = *token;
  mem = 0;
  while (cur)
    {
      if (count_parenth(cur, i, &mem, T_LRED))
	return ;
      if (is_token_separ(cur->type))
	prev = cur;
      else if (mem == i && (cur->type == T_DLRED || cur->type == T_LRED))
	swap_lred_token(token, cur, prev, prev_cur);
      prev_cur = cur;
      cur = cur->next;
    }
}

static void	swap_rred_token(t_token **token, t_token *cur,
				t_token **prev, t_token *prev_cur)
{
  t_token	*mem;

  if (*prev == *token && ((*prev)->type == T_DRRED || (*prev)->type == T_RRED
			  || (*prev)->type == T_ANDRED
			  || (*prev)->type == T_ANDDRED))
    {
      *token = (*prev)->next;
      (*prev)->next = cur;
      prev_cur->next = *prev;
    }
  else if ((*prev)->next && (*prev)->next != prev_cur)
    {
      mem = (*prev)->next->next;
      (*prev)->next->next = cur;
      prev_cur->next = (*prev)->next;
      (*prev)->next = mem;
    }
  *prev = NULL;

}

void		swap_rred(t_token **token, int i)
{
  int		mem;
  t_token	*cur;
  t_token	*prev;
  t_token	*prev_cur;

  cur = *token;
  mem = 0;
  prev = NULL;
  prev_cur = NULL;
  while (cur)
    {
      if (count_parenth(cur, i, &mem, T_RRED))
  	return ;
      if (i == mem && (cur->type == T_DRRED || cur->type == T_RRED
  		       || cur->type == T_ANDRED || cur->type == T_ANDDRED))
  	prev = (prev_cur) ? prev_cur : cur;
      else if (prev && i == mem && is_token_separ(cur->type))
	swap_rred_token(token, cur, &prev, prev_cur);
      else if (prev && i == mem && cur->type == T_RPARENTH)
	swap_rred_token(token, cur->next, &prev, cur);
      prev_cur = cur;
      cur = cur->next;
    }
}
