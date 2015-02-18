/*
** command_error.c for 42sh in /u/all/castel_a/cu/42sh/current/src/parser/lexer
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Sun May  2 11:48:44 2010 gianni castellani
** Last update Fri May 14 15:21:32 2010 gianni castellani
*/

#include <unistd.h>
#include "parser.h"
#include "lib_includes/aff.h"
#include "lib_includes/xfunctions.h"

static int	handle_unmatched(int c)
{
  my_puterror("Unmatched ");
  xwrite(STDERR_FILENO, &c, 1);
  my_puterror(".\n");
  return (0);
}

int		error_par(void)
{
  my_puterror("Badly placed ()'s.\n");
  return (0);
}

int		command_error(t_token *cur_token, int *mask)
{
  int		cpt;
  int		c;

  if (*mask & T_RPARENTH)
    return (error_par());
  *mask |= T_COMMAND;
  c = 0;
  cpt = 0;
  while (cur_token->data[cpt] != '\0')
    {
      if (cur_token->data[cpt] == '\\')
	cpt++;
      else if (!c && (cur_token->data[cpt] == '"'
		      || cur_token->data[cpt] == '\''
		      || cur_token->data[cpt] == '`'))
	c = cur_token->data[cpt];
      else if (c == cur_token->data[cpt])
	c = 0;
      if (cur_token->data[cpt] != '\0')
	cpt++;
    }
  if (c != 0)
    return (handle_unmatched(c));
  return (1);
}
