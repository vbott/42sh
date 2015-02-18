/*
** init_bindkey.c for 42sh in /u/all/castel_a/cu/42sh/current/headers
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Wed Mar 31 12:11:15 2010 gianni castellani
** Last update Tue May 11 12:03:56 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/strings.h"
#include "termcaps.h"
#include "parser.h"
#include "jobs.h"
#include "gl_vars.h"

void			init_bindkey(void)
{
  t_bindkey		*current;
  extern t_global	gl_global;

  current = NULL;
  current = load_cursor_left(current);
  current = load_cursor_right(current);
  current = load_cursor_backspace(current);
  current = load_cursor_delete(current);
  current = load_cursor_home(current);
  current = load_cursor_end(current);
  current = load_cursor_clear(current);
  current = load_cursor_completion(current);
  current = load_cursor_history_up(current);
  current = load_cursor_history_down(current);
  current = load_cursor_eof(current);
  current = load_cursor_interrupt(current);
  gl_global.gl_bindkey = current;
}
