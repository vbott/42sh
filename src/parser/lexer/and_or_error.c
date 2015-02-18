/*
** and_or_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:47:56 2010 gianni castellani
** Last update Wed May  5 15:11:42 2010 gianni castellani
*/

#include "parser.h"
#include "lib_includes/aff.h"

int		and_or_error(UNUSED t_token *cur_token,
			     int *mask)
{
  if (!(*mask & T_COMMAND))
    {
      my_puterror("Invalid null command.\n");
      return (0);
    }
  *mask = 0;
  return (1);
}
