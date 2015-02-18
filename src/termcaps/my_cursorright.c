/*
** my_cursorright.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:39:15 2010 gianni castellani
** Last update Wed May 19 19:23:17 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "gl_vars.h"

void			my_cursor_right(__attribute__((unused))
				char *buf, size_t i[2])
{
  extern t_global	gl_global;
  extern t_termcap	gl_cap;

  if (i[0] < i[1])
    {
      (i[0])++;
      if ((i[0] + gl_global.prompt_len) % gl_cap.co)
	xtputs(gl_cap.krstr, 1, my_outc);
      else
	my_putchar('\n');
    }
}
