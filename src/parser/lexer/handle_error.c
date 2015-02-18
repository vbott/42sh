/*
** handle_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sat May  1 15:17:59 2010 gianni castellani
** Last update Sat May 22 17:44:24 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/aff.h"

extern t_prioop		gl_prio[];

int			return_failure(void)
{
  my_puterror("Invalid null command.\n");
  return (EXIT_FAILURE);
}

static t_prioop		search_token(t_token *token)
{
  int			cpt;

  cpt = 0;
  while (gl_prio[cpt].type && token->type != gl_prio[cpt].type)
    cpt++;
  return (gl_prio[cpt]);
}

int			handle_end_error(int mask)
{
  if (!(mask & T_COMMAND) && mask != T_BACKGROUND && mask != T_SEMICOLON)
    return (return_failure());
  return (EXIT_SUCCESS);
}

int			call_of_token_error(t_token *token, int *mask)
{
  t_prioop		prio;

  if (token->type == T_RPARENTH)
    {
      my_puterror("Too many )'s.\n");
      return (EXIT_FAILURE);
    }
  prio = search_token(token);
  if ((prio.type && !prio.func(token, mask)) ||
      (!prio.type && !command_error(token, mask)))
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}

int			handle_error(t_token *token)
{
  int			mask;
  int			prev_type;

  prev_type = -1;
  mask = 0;
  while (token)
    {
      if (token->type == T_LPARENTH)
	{
	  if (check_between_parenthesis(&token, &mask) == EXIT_FAILURE)
	    return (EXIT_FAILURE);
	}
      else if (call_of_token_error(token, &mask) == EXIT_FAILURE)
	return (EXIT_FAILURE);
      prev_type = token->type;
      token = token->next;
    }
  return (handle_end_error(mask));
}
