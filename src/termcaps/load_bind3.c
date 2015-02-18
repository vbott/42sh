/*
** load_bind3.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue May 11 10:58:29 2010 gianni castellani
** Last update Wed May 19 16:12:49 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "termcaps.h"
#include "parser.h"
#include "history.h"
#include "builtins.h"
#include "ergonomy.h"

extern t_termcap	gl_cap;

t_bindkey		*load_cursor_eof(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = NULL;
  current->ch = EOF;
  current->exec = my_strdup("exit");
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_interrupt(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_interrupt;
  current->ch = CTRLC;
  current->exec = NULL;
  current->next = temp;
  return (current);
}
