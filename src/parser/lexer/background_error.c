/*
** background_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:48:21 2010 gianni castellani
** Last update Wed May  5 18:07:45 2010 gianni castellani
*/

#include "parser.h"
#include "lib_includes/aff.h"

int		background_error(UNUSED t_token *cur_token,
				 int *mask)
{
  if (!(*mask & T_COMMAND))
    {
      my_puterror("Invalid null command.\n");
      return (0);
    }
  *mask = T_BACKGROUND;
  return (1);
}
