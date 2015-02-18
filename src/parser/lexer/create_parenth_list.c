/*
** create_parenth_list.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Fri May 21 16:02:56 2010 gianni castellani
** Last update Sat May 22 17:16:31 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/aff.h"

t_token			*handle_return(t_token *prev,
				       t_token *cur, t_token *list)
{
  int			ret;

  if (!cur)
    {
      my_puterror("Too many ('s.\n");
      return (NULL);
    }
  prev->next = NULL;
  ret = handle_error(list->next);
  prev->next = cur;
  return ((ret == EXIT_SUCCESS) ? (cur) : (NULL));
}

t_token			*create_parenth_list(t_token *list)
{
  int			nb_parenth;
  t_token		*cur;
  t_token		*prev;

  cur = list;
  prev = cur;
  nb_parenth = 1;
  cur = cur->next;
  while (cur && nb_parenth)
    {
      if (cur->type == T_LPARENTH)
	nb_parenth++;
      else if (cur->type == T_RPARENTH)
	nb_parenth--;
      if (nb_parenth)
	{
	  prev = cur;
	  cur = cur->next;
	}
    }
  return (handle_return(prev, cur, list));
}

int			check_between_parenthesis(t_token **token, int *mask)
{
  if (*mask & T_COMMAND)
    {
      my_puterror("Badly placed ()'s.\n");
      return (EXIT_FAILURE);
    }
  *mask |= T_COMMAND;
  *mask |= T_RPARENTH;
  *token = create_parenth_list(*token);
  if (*token == NULL)
    return (EXIT_FAILURE);
  return (EXIT_SUCCESS);
}
