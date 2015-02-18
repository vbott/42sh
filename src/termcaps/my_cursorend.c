/*
** my_cursorend.c for 42sh in /u/all/castel_a/cu/42sh/current/termcaps
** 
** Made by gianni castellani
** Login   <castel_a@epitech.net>
** 
** Started on  Thu Apr  1 11:40:10 2010 gianni castellani
** Last update Wed May 19 16:27:02 2010 gianni castellani
*/

#include <stdlib.h>
#include "lib_includes/xfunctions.h"
#include "lib_includes/aff.h"
#include "termcaps.h"
#include "gl_vars.h"

void			my_cursor_end(char *buf, size_t i[2])
{
  extern t_global	gl_global;
  extern t_termcap	gl_cap;

  while (buf != NULL && i[0] < i[1])
    {
      xtputs(gl_cap.krstr, 1, my_outc);
      i[0]++;
      if (!((i[0] + gl_global.prompt_len) % gl_cap.co))
	my_putchar('\n');
    }
}
