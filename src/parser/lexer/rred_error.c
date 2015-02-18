/*
** rred_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:46:51 2010 gianni castellani
** Last update Wed May  5 16:05:14 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "lib_includes/aff.h"

int			rred_error(t_token *cur_token, int *mask)
{
  if (cur_token->data == NULL)
    {
      my_puterror("Missing name for redirect.\n");
      return (0);
    }
  if (*mask & T_RRED)
    {
      my_puterror("Ambiguous output redirect.\n");
      return (0);
    }
  *mask |= T_RRED;
  return (1);
}
