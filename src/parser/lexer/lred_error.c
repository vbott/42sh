/*
** lred_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:47:22 2010 gianni castellani
** Last update Thu May 13 16:26:43 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/aff.h"

int			lred_error(t_token *cur_token, int *mask)
{
  if (cur_token->data == NULL)
    {
      my_puterror("Missing name for redirect.\n");
      return (0);
    }
  if ((*mask & T_PIPE) || (*mask & T_LRED))
    {
      my_puterror("Ambiguous input redirect.\n");
      return (0);
    }
  *mask |= T_LRED;
  return (1);
}
