/*
** pipe_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:46:04 2010 gianni castellani
** Last update Fri May 14 15:22:33 2010 gianni castellani
*/

#include "parser.h"
#include "lib_includes/aff.h"

int			pipe_error(UNUSED t_token *cur_token, int *mask)
{
  if (!(*mask & T_COMMAND))
    {
      my_puterror("Invalid null command.\n");
      return (0);
    }
  if (*mask & T_RRED)
    {
      my_puterror("Ambiguous output redirect.\n");
      return (0);
    }
  *mask |= T_PIPE;
  *mask &= ~(T_COMMAND | T_RPARENTH | T_LPARENTH);
  return (1);
}
