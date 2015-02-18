/*
** my_cursorclear.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:41:43 2010 gianni castellani
** Last update Fri May 21 12:31:26 2010 gianni castellani
*/

#include <stdlib.h>
#include <unistd.h>
#include "parser.h"
#include "builtins.h"
#include "ergonomy.h"
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"

void			my_cursor_clear(char *buf, size_t i[2])
{
  extern t_termcap	gl_cap;

  xtputs(gl_cap.clstr, 1, my_outc);
  aff_prompt();
  xwrite(STDOUT_FILENO, buf, i[1]);
  begin_cursor(i);
}
