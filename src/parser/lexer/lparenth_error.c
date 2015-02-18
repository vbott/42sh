/*
** lparenth_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu May 13 16:24:45 2010 gianni castellani
** Last update Fri May 21 15:58:03 2010 gianni castellani
*/

#include "parser.h"
#include "lib_includes/aff.h"

int			lparenth_error(UNUSED t_token *cur_token, int *mask)
{
  if (*mask & T_COMMAND)
    {
      my_puterror("Badly placed ()'s.\n");
      return (0);
    }
  *mask |= T_LPARENTH;
  return (1);
}
