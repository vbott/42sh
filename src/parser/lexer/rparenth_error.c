/*
** rparenth_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu May 13 16:31:21 2010 gianni castellani
** Last update Thu May 13 17:38:56 2010 gianni castellani
*/

#include "parser.h"

int			rparenth_error(UNUSED t_token *cur_token, int *mask)
{
  *mask |= T_RPARENTH;
  return (1);
}
