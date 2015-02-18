/*
** load_bind2.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 14:59:10 2010 gianni castellani
** Last update Wed May 19 16:18:56 2010 gianni castellani
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

t_bindkey		*load_cursor_end(t_bindkey *temp)
{
  t_bindkey		*current;
  t_bindkey		*current2;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_end;
  current->ch = gl_cap.kestr;
  current->exec = NULL;
  current->next = temp;
  current2 = xmalloc(sizeof(*current));
  current2->function = my_cursor_end;
  current2->ch = "\05";
  current2->exec = NULL;
  current2->next = current;
  return (current2);
}

t_bindkey		*load_cursor_clear(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_clear;
  current->ch = "\014";
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_history_up(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = hist_up;
  current->ch = gl_cap.kustr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_history_down(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = hist_down;
  current->ch = gl_cap.kdstr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_completion(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = completion;
  current->ch = "\t";
  current->exec = NULL;
  current->next = temp;
  return (current);
}
