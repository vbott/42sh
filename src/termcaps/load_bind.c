/*
** load_bind.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 14:57:56 2010 gianni castellani
** Last update Wed May 19 16:15:06 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "termcaps.h"

extern t_termcap	gl_cap;

t_bindkey		*load_cursor_left(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_left;
  current->ch = gl_cap.klstr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_right(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_right;
  current->ch = gl_cap.krstr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_backspace(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_backspace;
  current->ch = gl_cap.kbstr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_delete(t_bindkey *temp)
{
  t_bindkey		*current;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_delete;
  current->ch = gl_cap.kDstr;
  current->exec = NULL;
  current->next = temp;
  return (current);
}

t_bindkey		*load_cursor_home(t_bindkey *temp)
{
  t_bindkey		*current;
  t_bindkey		*current2;

  current = xmalloc(sizeof(*current));
  current->function = my_cursor_home;
  current->ch = gl_cap.khstr;
  current->exec = NULL;
  current->next = temp;
  current2 = xmalloc(sizeof(*current2));
  current2->function = my_cursor_home;
  current2->ch = "\01";
  current2->exec = NULL;
  current2->next = current;
  return (current2);
}
