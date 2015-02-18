/*
** my_cursorinterrupt.c for 42sh in /u/all/castel_a/cu/42sh/current
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Tue May 11 12:05:50 2010 gianni castellani
** Last update Tue May 11 12:25:10 2010 gianni castellani
*/

#include <stdlib.h>
#include "parser.h"
#include "builtins.h"
#include "ergonomy.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "jobs.h"
#include "gl_vars.h"

void			my_cursor_interrupt(__attribute__((unused)) char *buf,
					    size_t i[2])
{
  extern t_global	gl_global;

  while (gl_global.history->prev)
    gl_global.history = gl_global.history->prev;
  my_putstr("\n");
  aff_prompt();
  i[0] = 0;
  i[1] = 0;
}
